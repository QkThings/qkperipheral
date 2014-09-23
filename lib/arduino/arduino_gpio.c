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

#include <avr/io.h>

static volatile uint8_t * get_ddr_reg(qk_gpio_port port)
{
	volatile uint8_t *ddr_reg;

	switch(port)
	{
#ifdef AVR_HAS_PORT_A
	case QK_GPIO_PORT_A: ddr_reg = &DDRA; break;
#endif
#ifdef AVR_HAS_PORT_B
	case QK_GPIO_PORT_B: ddr_reg = &DDRB; break;
#endif
#ifdef AVR_HAS_PORT_C
	case QK_GPIO_PORT_C: ddr_reg = &DDRC; break;
#endif
#ifdef AVR_HAS_PORT_D
	case QK_GPIO_PORT_D: ddr_reg = &DDRD; break;
#endif
	default: return 0;
	}

	return ddr_reg;
}

static volatile uint8_t * get_port_reg(qk_gpio_port port)
{
	volatile uint8_t *port_reg;

	switch(port)
	{
#ifdef AVR_HAS_PORT_A
	case QK_GPIO_PORT_A: port_reg = &PORTA; break;
#endif
#ifdef AVR_HAS_PORT_B
	case QK_GPIO_PORT_B: port_reg = &PORTB; break;
#endif
#ifdef AVR_HAS_PORT_C
	case QK_GPIO_PORT_C: port_reg = &PORTC; break;
#endif
#ifdef AVR_HAS_PORT_D
	case QK_GPIO_PORT_D: port_reg = &PORTD; break;
#endif
	default: return 0;
	}

	return port_reg;
}



void _qk_gpio_startup()
{

}

void qk_gpio_set_mode(qk_gpio_pin pin, qk_gpio_mode mode)
{
	int port = _QK_GPIO_PORT(pin);
	int bit = _QK_GPIO_BIT(pin);
	volatile uint8_t *ddr_reg, *port_reg;

	ddr_reg = get_ddr_reg(port);
	port_reg = get_port_reg(port);

	switch(mode)
	{
	case QK_GPIO_MODE_ANALOG:
	case QK_GPIO_MODE_INPUT:
	case QK_GPIO_MODE_INPUT_PULL_DOWN:
		*ddr_reg &= ~(1 << bit);
		*port_reg &= ~(1 << bit);
		break;
	case QK_GPIO_MODE_INPUT_PULL_UP:
		*ddr_reg &= ~(1 << bit);
		*port_reg |= 1 << bit;
		break;
	case QK_GPIO_MODE_OUTPUT:
	case QK_GPIO_MODE_OUTPUT_OPEN_DRAIN:
		 DDRB = (1<<bit);
//		*ddr_reg |= 1 << bit;
//		*port_reg &= ~(1 << bit);
		break;
	}
}

void qk_gpio_set_pin(qk_gpio_pin pin, bool state)
{
	volatile uint8_t *port_reg = get_port_reg(_QK_GPIO_PORT(pin));
	if(state)
		PORTB |= (1 << _QK_GPIO_BIT(pin));
	else
		PORTB &= ~(1 << _QK_GPIO_BIT(pin));
//	if(state)
//		*port_reg |= (1 << _QK_GPIO_BIT(pin));
//	else
//		*port_reg &= ~(1 << _QK_GPIO_BIT(pin));
}

bool qk_gpio_get_pin(qk_gpio_pin pin)
{
	volatile uint8_t *port_reg = get_port_reg(_QK_GPIO_PORT(pin));
	return (*port_reg & (1 << _QK_GPIO_BIT(pin)) ? true : false);
}


void qk_gpio_set_port(qk_gpio_port port, int value)
{
	volatile uint8_t *port_reg = get_port_reg(port);
	*port_reg = (uint8_t) value;
}


int  qk_gpio_get_port(qk_gpio_port port)
{
	volatile uint8_t *port_reg = get_port_reg(port);
	return (int) *port_reg;
}


void qk_gpio_toggle_pin(qk_gpio_pin pin)
{
	volatile uint8_t *port_reg = get_port_reg(_QK_GPIO_PORT(pin));
	int bit = (1 << _QK_GPIO_BIT(pin));
	if(*port_reg & bit)
		*port_reg &= ~bit;
	else
		*port_reg |= bit;
}


void qk_gpio_toggle_port(qk_gpio_port port, int pins)
{
	volatile uint8_t *port_reg = get_port_reg(port);
	*port_reg ^= pins;
}

void qk_gpio_interrupt_set(qk_gpio_pin pin, uint32_t flags)
{
	//TODO
}

void qk_gpio_enable_interrupt()
{
	//TODO
}

void qk_gpio_disable_interrupt()
{
	//TODO
}



