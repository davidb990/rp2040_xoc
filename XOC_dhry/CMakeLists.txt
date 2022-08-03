cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(dhry1_project)

pico_sdk_init()

add_executable(dhry1
        dhry1.c dhry_2.c
)
pico_enable_stdio_usb(dhry1 1)
pico_enable_stdio_uart(dhry1 1)
pico_add_extra_outputs(dhry1)

target_link_libraries(dhry1 pico_stdlib hardware_clocks)
pico_set_binary_type(dhry1 copy_to_ram)
