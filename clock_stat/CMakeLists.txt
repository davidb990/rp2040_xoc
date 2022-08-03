cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(CLOCK_STAT C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()
add_executable(CLOCK_STAT
        CLOCK_STAT.c
        )
pico_enable_stdio_usb(CLOCK_STAT 1)
pico_enable_stdio_uart(CLOCK_STAT 1)
pico_add_extra_outputs(CLOCK_STAT)
target_link_libraries(CLOCK_STAT pico_stdlib hardware_clocks)
pico_set_binary_type(CLOCK_STAT copy_to_ram)
