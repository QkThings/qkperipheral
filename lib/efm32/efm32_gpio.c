#include "system.h"

#include "em_gpio.h"

void qk_gpio_hw_startup()
{
	CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_GPIO;
}


