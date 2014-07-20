#include "system.h"

qk_peripheral _qk_peripheral = QKPERIPHERAL_INIT;

void qk_peripheral_setup()
{
#ifdef HAS_GPIO
	qk_gpio_hw_startup();
#endif
#ifdef HAS_ADC
	qk_adc_hw_startup();
#endif
}

void qk_peripheral_update(int clk_freq)
{
	_qk_peripheral.clk_freq = clk_freq;
#ifdef HAS_ADC
	qk_adc_hw_update();
#endif
}
