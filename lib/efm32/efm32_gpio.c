/*
 * QkThings LICENSE
 * The open source framework and modular platform for smart devices.
 * Copyright (C) 2014 <http://qkthings.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
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


