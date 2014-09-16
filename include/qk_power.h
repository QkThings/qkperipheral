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

/** \addtogroup QkPower
 * @brief Power Management
 *  @{
 */

#ifndef QK_POWER_H
#define QK_POWER_H

void qk_power_EM1(); // Energy mode 1 (only CPU is inactive)
void qk_power_EM2(); // Energy mode 2 (must wake up from UART RX interrupt)
void qk_power_EM3(); // Energy mode 3 (must wake up from RTC, if available)

#endif

/** @}*/
