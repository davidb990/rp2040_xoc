#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pll.h"

#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1
#define GPOUT_DIV 10
#define rosc_div_addr ((io_rw_32 *const) 0x40060010u)
#define rosc_ctl_addr ((io_rw_32 *const) 0x40060000u)
#define rosc_freqa_addr ((io_rw_32 *const) 0x40060004u)
#define rosc_freqb_addr ((io_rw_32 *const) 0x40060008u)

void clk_config_rosc() {
    clock_configure(clk_sys,
                    CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX,
                    CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_ROSC_CLKSRC,
                    6 * MHZ,
                    6 * MHZ);

    pll_deinit(pll_sys);

    hw_write_masked(rosc_div_addr, 0xaa1, 0x00000fff);
    hw_write_masked(rosc_ctl_addr, 0xfa6, 0x00000fff);
    hw_set_bits(rosc_freqa_addr, 0x96967777);
    hw_set_bits(rosc_freqb_addr, 0x96967777);

    clock_configure(clk_peri,
                    0,
                    CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_XOSC_CLKSRC,
                    12 * MHZ,
                    12 * MHZ);

    clock_configure(clk_usb,
                    0,
                    CLOCKS_CLK_USB_CTRL_AUXSRC_VALUE_XOSC_CLKSRC,
                    12 * MHZ,
                    48 * MHZ);
}

int main() {
	stdio_init_all();
	uart_init(UART_ID, BAUD_RATE);
	gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
	gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    clk_config_rosc();
    clock_gpio_init(21, CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_SYS, GPOUT_DIV);
    clock_gpio_init(23, CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_VALUE_ROSC_CLKSRC_PH, GPOUT_DIV);

    double freq;
    int msg_count;

    msg_count = 1;

	while (true) {
        freq = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_SYS);
        printf("RP2040_SYS_CLK_MHz:%.3f:MSG_COUNT:%i:\n\r", freq / 1000, msg_count);
        msg_count += 1;
        sleep_ms(500);
	}
}
