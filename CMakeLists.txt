cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(EMG_BETTR_v2)

FILE(GLOB app_sources main/src/*.c)
FILE(GLOB imu_driver_sources main/src/IMU/*.c)

target_sources(app PRIVATE ${app_sources} ${imu_driver_sources})
target_include_directories(app PRIVATE main/inc main/inc/IMU)
