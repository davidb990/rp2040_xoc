cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(XOC C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()
add_executable(XOC
        XOC.c
        )
pico_enable_stdio_usb(XOC 1)
pico_add_extra_outputs(XOC)
target_link_libraries(XOC pico_stdlib hardware_clocks hardware_pll hardware_gpio pico_time hardware_vreg)
pico_set_binary_type(XOC copy_to_ram)
