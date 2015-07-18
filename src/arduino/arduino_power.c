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

#include <avr/sleep.h>
#include <avr/interrupt.h>

static void goto_sleep()
{
  sleep_enable();
  sei();
  sleep_cpu();
  sleep_disable();
}

void qk_power_EM1()
{
	set_sleep_mode(SLEEP_MODE_IDLE);
	goto_sleep();
}

void qk_power_EM2()
{
	qk_power_EM1();
}

void qk_power_EM3()
{
	qk_power_EM1();
}
