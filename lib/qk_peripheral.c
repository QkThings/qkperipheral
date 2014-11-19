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

qk_peripheral _qk_peripheral = QKPERIPHERAL_INIT;

void _qk_peripheral_setup(void)
{
	_qk_mcu_startup();
	_qk_gpio_startup();
	_qk_uart_startup();
	_qk_timer_startup();
	_qk_adc_startup();
	//_qk_pwm_startup();
	_qk_i2c_startup();
	//_qk_spi_startup();

	
	_qk_gpio_init();
	_qk_uart_init();
	_qk_timer_init();
	_qk_adc_init();

	_qk_mcu_finalize();
}

void _qk_peripheral_update(int clk_freq)
{
	_qk_peripheral.clk_freq = clk_freq;
}
