#include "IMU.h"
#include "IMU/driver_mpu6500_basic.h"
#include "bleDriver.h"
#include "config.h"

LOG_MODULE_REGISTER(imu_task_mod, LOG_LEVEL_INF);

/* ---- Step Detection Config ---- */
#define STEP_THRESHOLD    0.40f  /* min peak height (tune: raise if false steps) */
#define STEP_MIN_GAP_MS   350   /* min ms between two steps (~2.8 Hz max) */
#define STEP_IDLE_MS      2000  /* no step for 2s → idle */
#define STEP_STARTUP_MS   500   /* ignore first 500ms after init (sensor settling) */
#define WALK_RUN_FREQ_THR 2.2f  /* step freq above this = running */

/* ---- Low-pass filter coefficient ---- */
#define LPF_ALPHA  0.3f  /* 0-1: lower = smoother, higher = faster response */

/* ---- Step Detection State (file-scoped) ---- */
static float s_lpf;                  /* low-pass filtered deviation */
static float s_prev, s_curr, s_next; /* 3-sample sliding window on filtered signal */
static uint32_t s_last_step_ms;
static uint32_t s_init_ms;           /* timestamp when detection started */
static uint16_t s_steps;
static int8_t  s_walk_run;           /* 0 = idle, 1 = walking, 2 = running */
static float   s_avg_freq;           /* smoothed step frequency (Hz) */

static void step_detect(float ax, float ay, float az, uint32_t now_ms)
{
    /* Record init time on first call */
    if (s_init_ms == 0) {
        s_init_ms = now_ms;
    }

    /* Ignore samples during startup (sensor settling) */
    if ((now_ms - s_init_ms) < STEP_STARTUP_MS) {
        return;
    }

    /*
     * Squared magnitude minus gravity (~1g² = 1.0).
     * At rest: ≈ 0.  Step impact: positive peak.
     */
    float dev = ax * ax + ay * ay + az * az - 1.0f;

    /* Low-pass filter to smooth out high-frequency noise */
    s_lpf = LPF_ALPHA * dev + (1.0f - LPF_ALPHA) * s_lpf;

    /* Shift 3-sample sliding window on filtered signal */
    s_prev = s_curr;
    s_curr = s_next;
    s_next = s_lpf;

    /* Idle timeout: if no step for a while, reset activity */
    if (s_last_step_ms > 0 && (now_ms - s_last_step_ms) > STEP_IDLE_MS) {
        s_walk_run = 0;
    }

    /* Peak in middle sample + minimum time gap */
    if (s_curr > s_prev && s_curr > s_next &&
        s_curr > STEP_THRESHOLD &&
        (now_ms - s_last_step_ms) > STEP_MIN_GAP_MS)
    {
        s_steps++;

        /* Classify walking vs running using smoothed step frequency */
        if (s_last_step_ms > 0) {
            uint32_t interval = now_ms - s_last_step_ms;
            float inst_freq = 1000.0f / interval;

            /* Exponential moving average of frequency */
            s_avg_freq = (s_avg_freq > 0.1f)
                ? (LPF_ALPHA * inst_freq + (1.0f - LPF_ALPHA) * s_avg_freq)
                : inst_freq;

            s_walk_run = (s_avg_freq > WALK_RUN_FREQ_THR) ? 2 : 1;
            LOG_INF("Step %u  freq=%.1f Hz  avg=%.1f Hz  %s",
                    s_steps, (double)inst_freq, (double)s_avg_freq,
                    (s_walk_run == 2) ? "Running" : "Walking");
        } else {
            s_walk_run = 1;
            LOG_INF("Step %u  Walking (first)", s_steps);
        }

        s_last_step_ms = now_ms;
    }
}

uint16_t step_get_count(void)
{
    return s_steps;
}

void step_reset(void)
{
    s_steps = 0;
    s_lpf = 0;
    s_prev = s_curr = s_next = 0;
    s_last_step_ms = 0;
    s_init_ms = 0;
    s_walk_run = 0;
    s_avg_freq = 0;
}

/* ---- IMU Driver ---- */

int imu_init(void)
{
    LOG_INF("Initializing MPU6500...");

    uint8_t res = mpu6500_basic_init(MPU6500_INTERFACE_IIC, 0x68);

    if (res != 0) {
        LOG_ERR("MPU6500 Initialization Failed! Error Code: %d", res);
        return res;
    }

    LOG_INF("MPU6500 initialized successfully!");
    return 0;
}

IMU_data_t imu_read(void)
{
    IMU_data_t imu_sample;
    float g[3], dps[3];

    if (mpu6500_basic_read(g, dps) != 0) {
        LOG_WRN("Failed to read sensor data");
        memset(&imu_sample, 0, sizeof(imu_sample));
        return imu_sample;
    }

    /* Run step detection on raw float accel (in g) before converting */
    step_detect(g[0], g[1], g[2], k_uptime_get_32());

    /* Convert float to int16 for BLE transmission */
    for (int i = 0; i < 3; i++) {
        imu_sample.accel[i] = (int16_t)(g[i] * 100);
        imu_sample.gyro[i]  = (int16_t)(dps[i] * 100);
    }

    imu_sample.Step = (int8_t)(s_steps & 0x7F);
    imu_sample.WalkingVsRunning = s_walk_run;
    return imu_sample;
}

void imu_task(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1);
    ARG_UNUSED(p2);
    ARG_UNUSED(p3);

    k_msleep(100); // Let power stabilize
    LOG_INF("Starting IMU Task...");

    if (imu_init() != 0) {
        LOG_ERR("IMU Init Failed! Task exiting...");
        return;
    }

    struct IMUDataPacket packet;

    while (1) {
        IMU_data_t raw_data = imu_read();

        packet.timestamp_ms = (uint32_t)k_uptime_get_32();
        packet.data = raw_data;

        LOG_INF("Ts:%u | Acc:(%d, %d, %d) | Gyro:(%d, %d, %d)",
                packet.timestamp_ms,
                raw_data.accel[0], raw_data.accel[1], raw_data.accel[2],
                raw_data.gyro[0],  raw_data.gyro[1],  raw_data.gyro[2]);

        send_imu_pkt(&packet);

        k_msleep(IMU_SAMPLE_RATE_MS);
    }
}
