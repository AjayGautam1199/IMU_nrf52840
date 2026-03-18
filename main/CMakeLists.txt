file(GLOB SRC_FILES "src/*.c")
file(GLOB IMU_FILES "src/IMU/*.c")

idf_component_register(SRCS "main.c" ${SRC_FILES} ${IMU_FILES}
                      INCLUDE_DIRS "inc" "inc/IMU" "src" "src/IMU")