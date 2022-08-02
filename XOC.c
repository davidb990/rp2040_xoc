#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pll.h"
#include <math.h>

#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1
#define GPOUT_DIV 10
#define rosc_div_addr ((io_rw_32 *const) 0x40060010u)
#define rosc_ctl_addr ((io_rw_32 *const) 0x40060000u)
#define rosc_freqa_addr ((io_rw_32 *const) 0x40060004u)
#define rosc_freqb_addr ((io_rw_32 *const) 0x40060008u)
#define MAX_NUM 200000
#define SOE_LOOPS 25

void SoE(int runs) {
    /* Create an array of values, where '1' indicates that a number is prime.
     * Start by assuming all numbers are prime by setting them to 1.
     */
    for (int i = 0; i < runs; i++){
        char primes[MAX_NUM];
        for (int i = 0; i < MAX_NUM; i++) {
            primes[i] = 1;
        }

        /* Loop through a portion of the array (up to the square root of MAX). If
         * it's a prime, ensure all multiples of it are set to zero (false), as they
         * clearly cannot be prime.
         */
        int limit = sqrt(MAX_NUM) + 1;
        for (int i = 2; i < limit; i++) {
            if (primes[i - 1]) {
                for (int j = i * i; j <= MAX_NUM; j += i) {
                    primes[j - 1] = 0;
                }
            }
        }
    }
}

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
        absolute_time_t t0 = get_absolute_time();
        SoE(SOE_LOOPS);
        absolute_time_t t1 = get_absolute_time();
        int dt = absolute_time_diff_us(t0, t1);
        printf("RP2040_SYS_CLK_MHz:%.3f:MEANTIME_US:%i:MSG_COUNT:%i:\n\r", freq / 1000, dt / SOE_LOOPS, msg_count);
        msg_count += 1;
        sleep_ms(500);
	}
}
