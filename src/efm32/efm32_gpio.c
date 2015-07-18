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

#include "qk_peripheral.h"
#include "qk_peripheral_p.h"

#include "em_cmu.h"
#include "em_gpio.h"

void GPIO_EVEN_IRQHandler(void) // Rise
{
  _qk_gpio_handle_input_changed(QK_GPIO_FLAG_RISE);
  GPIO_IntClear(0xFFFF); // Clear all GPIO IF
}


void GPIO_ODD_IRQHandler(void) // Fall
{
  _qk_gpio_handle_input_changed(QK_GPIO_FLAG_FALL);
  GPIO_IntClear(0xFFFF); // Clear all GPIO IF
}

void _qk_gpio_startup()
{
	CMU_ClockEnable(cmuClock_GPIO, true);

	NVIC_EnableIRQ(GPIO_EVEN_IRQn);
	NVIC_EnableIRQ(GPIO_ODD_IRQn);
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
			        (unsigned int) _QK_GPIO_BIT(pin),
			        efm32_mode,
			        out);

//	GPIO_IntConfig(_QK_GPIO_PORT(pin), _QK_GPIO_PIN(pin), false, false, false);
}

void qk_gpio_set_pin(qk_gpio_pin pin, bool state)
{
	if(state)
	{
		GPIO_PinOutSet((GPIO_Port_TypeDef) _QK_GPIO_PORT(pin),
				       (unsigned int) _QK_GPIO_BIT(pin));
	}
	else
	{
		GPIO_PinOutClear((GPIO_Port_TypeDef) _QK_GPIO_PORT(pin),
				         (unsigned int) _QK_GPIO_BIT(pin));
	}
}

bool qk_gpio_get_pin(qk_gpio_pin pin)
{
	return GPIO_PinInGet((GPIO_Port_TypeDef) _QK_GPIO_PORT(pin),
	                      (unsigned int) _QK_GPIO_BIT(pin));
}


void qk_gpio_set_port(qk_gpio_port port, int value)
{
	GPIO_PortOutSet((GPIO_Port_TypeDef) port, value);
}


int  qk_gpio_get_port(qk_gpio_port port)
{
	return (int)GPIO_PortOutGet((GPIO_Port_TypeDef) port);
}


void qk_gpio_toggle_pin(qk_gpio_pin pin)
{
	GPIO_PinOutToggle((GPIO_Port_TypeDef) _QK_GPIO_PORT(pin),
	                  (unsigned int) _QK_GPIO_BIT(pin));
}


void qk_gpio_toggle_port(qk_gpio_port port, int pins)
{
	GPIO_PortOutToggle((GPIO_Port_TypeDef) port, pins);
}

void qk_gpio_interrupt_set(qk_gpio_pin pin, uint32_t flags)
{
	bool risingEdge = false, fallingEdge = false;
	if(flags & QK_GPIO_FLAG_FALL)
		fallingEdge = true;
	if(flags & QK_GPIO_FLAG_RISE)
		risingEdge = true;

	GPIO_IntConfig((GPIO_Port_TypeDef) _QK_GPIO_PORT(pin),
			       (unsigned int) _QK_GPIO_BIT(pin),
	               risingEdge,
	               fallingEdge,
	               true);
}

void qk_gpio_enable_interrupt()
{
	GPIO_IntEnable(0xFFFF);
}

void qk_gpio_disable_interrupt()
{
	GPIO_IntDisable(0xFFFF);
}



