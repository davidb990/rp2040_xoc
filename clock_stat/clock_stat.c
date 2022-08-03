#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"


#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1


void measure_freqs(int msg_count) {
    uint f_pll_sys = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_PLL_SYS_CLKSRC_PRIMARY);
    uint f_pll_usb = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_PLL_USB_CLKSRC_PRIMARY);
    uint f_rosc = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_ROSC_CLKSRC);
    uint f_clk_sys = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_SYS);
    uint f_clk_peri = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_PERI);
    uint f_clk_usb = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_USB);
    uint f_clk_adc = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_ADC);
    uint f_clk_rtc = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_RTC);

    printf(":PLL_SYS_kHz:%d:MSG_COUNT:%i:\n\r", f_pll_sys, msg_count);
    printf(":PLL_USB_kHz:%d:MSG_COUNT:%i:\n\r", f_pll_usb, msg_count);
    printf(":ROSC_kHz:%d:MSG_COUNT:%i:\n\r", f_rosc, msg_count);
    printf(":CLK_SYS_kHz:%d:MSG_COUNT:%i:\n\r", f_clk_sys, msg_count);
    printf(":CLK_PERI_kHz:%d:MSG_COUNT:%i:\n\r", f_clk_peri, msg_count);
    printf(":CLK_USB_kHz:%d:MSG_COUNT:%i:\n\r", f_clk_usb, msg_count);
    printf(":CLK_ADC_kHz:%d:MSG_COUNT:%i:\n\r", f_clk_adc, msg_count);
    printf(":CLK_RTC_kHz:%d:MSG_COUNT:%i:\n\r", f_clk_rtc, msg_count);

    // Can't measure clk_ref / xosc as it is the ref
}


int main( )
{
    stdio_init_all();
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    int msg_count = 1;

    while (true) {
        measure_freqs(msg_count);
        msg_count += 1;
        sleep_ms(2000);
    }
}
