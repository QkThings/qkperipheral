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


#ifndef QK_PERIPHERAL_P_H
#define QK_PERIPHERAL_P_H

// Development --------------------------------------------------------
//#define _QK_PERIPHERAL_DEV_UART_LOOPBACK
// --------------------------------------------------------------------

#include <string.h>
#include "qk_mcu_p.h"
#include "qk_gpio_p.h"
#include "qk_uart_p.h"
#include "qk_timer_p.h"
#include "qk_adc_p.h"
#include "qk_pwm_p.h"
#include "qk_i2c_p.h"

#ifndef INIT_CLKFREQ
#error "INIT_CLKFREQ is not defined"
#endif

typedef struct qk_peripheral
{
	long int clk_freq;
} qk_peripheral;

#define QKPERIPHERAL_INIT { .clk_freq = INIT_CLKFREQ }

extern qk_peripheral _qk_peripheral;

#endif
