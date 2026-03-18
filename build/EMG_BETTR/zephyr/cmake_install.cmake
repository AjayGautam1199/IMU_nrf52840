# Install script for directory: /opt/nordic/ncs/v3.2.2/zephyr

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/opt/nordic/ncs/toolchains/e5f4758bcf/opt/zephyr-sdk/arm-zephyr-eabi/bin/arm-zephyr-eabi-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/zephyr/arch/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/zephyr/lib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/zephyr/soc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/zephyr/boards/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/zephyr/subsys/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/zephyr/drivers/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/nrf/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/hostap/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/mcuboot/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/mbedtls/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/trusted-firmware-m/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/cjson/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/azure-sdk-for-c/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/cirrus-logic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/openthread/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/memfault-firmware-sdk/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/canopennode/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/chre/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/lz4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/zscilib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/cmsis/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/cmsis-dsp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/cmsis-nn/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/cmsis_6/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/fatfs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/hal_nordic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/hal_st/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/hal_tdk/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/hal_wurthelektronik/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/liblc3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/libmetal/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/littlefs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/loramac-node/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/lvgl/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/mipi-sys-t/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/nanopb/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/nrf_wifi/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/open-amp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/percepio/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/picolibc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/segger/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/uoscore-uedhoc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/zcbor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/nrfxlib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/nrf_hw_models/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/modules/connectedhomeip/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/zephyr/kernel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/zephyr/cmake/flash/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/zephyr/cmake/usage/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/ajaygautam/Work_folder/Documents/FW_Bettr/EMG_BETTR/build/EMG_BETTR/zephyr/cmake/reports/cmake_install.cmake")
endif()

