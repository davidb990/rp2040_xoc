# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.3.0)
set(toolchainVersion 15_2_Rel1)
set(picotoolVersion 2.3.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

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

target_link_libraries(dhry1 pico_stdlib hardware_clocks hardware_rosc)
pico_set_binary_type(dhry1 copy_to_ram)
