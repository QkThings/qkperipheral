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

/**
@mainpage QkPeripheral

Configuring microcontroller's peripherals through registers is always a time consuming task because it requires to understand how a given peripheral works by reading the microcontroller's datasheet and writing low level code to make it work as desired, but it's also a critical aspect of any microcontroller based embedded system. Even though many microcontrollers, from different manufacturers, have peripherals with identical functionality they are set up quite differently. This peripheral library is an abstraction layer to those common peripherals. It provides generic and simple functions that implement the most essential function of a peripheral, greatly increasing code portability. Its use is, however, optional.

*/

/** \addtogroup QkPeripheral
 *  @{
 */

#ifndef QK_PERIPHERAL_H
#define QK_PERIPHERAL_H

#include <stdint.h>
#include <stdbool.h>

#include "qk_mcu.h"
#include "qk_power.h"
#include "qk_gpio.h"
#include "qk_uart.h"
#include "qk_timer.h"
#include "qk_adc.h"
#include "qk_i2c.h"

void _qk_peripheral_setup(void);
void _qk_peripheral_update(int clock_freq);

#endif

/** @}*/

