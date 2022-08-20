#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pll.h"


#define rosc_div_addr ((io_rw_32 *const) 0x40060010u)
#define rosc_ctl_addr ((io_rw_32 *const) 0x40060000u)
#define rosc_freqa_addr ((io_rw_32 *const) 0x40060004u)
#define rosc_freqb_addr ((io_rw_32 *const) 0x40060008u)


void clk_config_rosc() {
    // sys_clk set to run off the ROSC
    clock_configure(clk_sys,
                    CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX,
                    CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_ROSC_CLKSRC,
                    6 * MHZ,
                    6 * MHZ);

    // pll_sys disabled
    pll_deinit(pll_sys);
	
    // ROSC settings
    hw_write_masked(rosc_div_addr, 0xaa1, 0x00000fff);  // Divider set to 1
    hw_write_masked(rosc_ctl_addr, 0xfa6, 0x00000fff);  // Drive stages reduced to 2
    hw_set_bits(rosc_freqa_addr, 0x96967777);  // Drive strength to maximum (freq a register)
    hw_set_bits(rosc_freqb_addr, 0x96967777);  // Drive strength to maximum (freq b register)

    // Set clk_peri to use the XOSC
    clock_configure(clk_peri,
                    0,
                    CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_XOSC_CLKSRC,
                    12 * MHZ,
                    12 * MHZ);

    // Set clk_usb to use the XOSC (USB requires a precise signal)
    clock_configure(clk_usb,
                    0,
                    CLOCKS_CLK_USB_CTRL_AUXSRC_VALUE_XOSC_CLKSRC,
                    12 * MHZ,
                    48 * MHZ);
}


int main() {
    stdio_init_all();  // Allows for USB comms
    clk_config_rosc();  // Configure ROSC

    // Variables for the printf statement
    double freq;
    int msg_count;
    msg_count = 1;

    while (true) {
        freq = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_SYS);  // Frequency counter
        printf("RP2040_SYS_CLK_MHz:%.3f:MSG_COUNT:%i:\n\r", freq / 1000, msg_count);
        msg_count += 1;
        sleep_ms(500);
    }
}
