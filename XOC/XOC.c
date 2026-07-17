/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pll.h"
#include "hardware/structs/rosc.h"
#include "hardware/rosc.h"


void clk_config_rosc() {
	rosc_disable();
	
	// ROSC settings
    hw_write_masked(&rosc_hw->div, 0xaa1, 0x00000fff);  // Divider set to 1
    hw_write_masked(&rosc_hw->ctrl, 0xfa6, 0x00000fff);  // Drive stages reduced to 2
    hw_set_bits(&rosc_hw->freqa, 0x96967777);  // Drive strength to maximum (freq a register)
    hw_set_bits(&rosc_hw->freqb, 0x96967777);  // Drive strength to maximum (freq b register)

    rosc_restart();
	
	//clk_ref set to run off the XOSC
	clock_configure(clk_ref,
                        CLOCKS_CLK_REF_CTRL_SRC_VALUE_XOSC_CLKSRC,
                        0,
                        12 * MHZ,
                        12 * MHZ);
   

    // Set clk_peri to use the XOSC
    clock_configure(clk_peri,
                    0,
                    CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_XOSC_CLKSRC,
                    12 * MHZ,
                    12 * MHZ);

    // Set clk_usb to use the XOSC (USB requires a precise signal)
    clock_configure(clk_usb,
                        0,
                        CLOCKS_CLK_USB_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB,
                        48 * MHZ,
                        48 * MHZ);

	// clk_sys set to run off the ROSC
	clock_configure(clk_sys,
                        CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX,
                        CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_ROSC_CLKSRC,
                        40 * MHZ,
                        40 * MHZ);

	// pll_sys disabled
    pll_deinit(pll_sys);
	
}


int main() {
    clk_config_rosc();  // Configure ROSC
    stdio_init_all();  // Allows for USB comms

    // Variables for the printf statement
    double freq;
    int msg_count;
    msg_count = 1;
    
    bool led_on = false;
   	gpio_init(25);
	gpio_set_dir(25, GPIO_OUT);
    while (true) {
        freq = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_SYS);  // Frequency counter
        printf("RP2040_SYS_CLK_MHz:%.3f:MSG_COUNT:%i:\n\r", freq / 1000, msg_count);
        msg_count += 1;
        
        gpio_put(25, led_on);
        led_on = !led_on;
        sleep_ms(500);
    }
}
