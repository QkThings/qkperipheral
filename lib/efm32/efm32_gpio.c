#include "system.h"

#include "em_gpio.h"

void _qk_gpio_startup()
{
	CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_GPIO;
}

void qk_gpio_set_mode(qk_gpio_pin pin, qk_gpio_mode mode)
{
	unsigned int out = 0;
	GPIO_Mode_TypeDef efm32_mode;

	switch(mode)
	{
	case QK_GPIO_MODE_ANALOG:
		efm32_mode = gpioModeDisabled;
		break;
	case QK_GPIO_MODE_OUTPUT:
		efm32_mode = gpioModePushPull;
		break;
	case QK_GPIO_MODE_INPUT:
		efm32_mode = gpioModeInput;
		out = 1; break; // with filter
	case QK_GPIO_MODE_OUTPUT_OPEN_DRAIN:
		efm32_mode = gpioModeWiredAnd;
		break;
	case QK_GPIO_MODE_INPUT_PULL_UP:
		efm32_mode = gpioModeInputPull;
		out = 1;
		break;
	case QK_GPIO_MODE_INPUT_PULL_DOWN:
		efm32_mode = gpioModeInputPull;
		break;
	default:
		return;
	}

	GPIO_PinModeSet((GPIO_Port_TypeDef) _QK_GPIO_PORT(pin),
			        (unsigned int) _QK_GPIO_PIN(pin),
			        efm32_mode,
			        out);
}


