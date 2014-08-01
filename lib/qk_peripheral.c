#include "system.h"

qk_peripheral _qk_peripheral = QKPERIPHERAL_INIT;

void qk_peripheral_setup()
{
#ifdef QK_GPIO
	_qk_gpio_startup();
#endif
#ifdef QK_ADC
	_qk_adc_startup();
#endif
#ifdef QK_UART
	_qk_uart_startup();
#endif
}

void qk_peripheral_update(int clk_freq)
{
	_qk_peripheral.clk_freq = clk_freq;
}
