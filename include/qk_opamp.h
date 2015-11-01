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

/** \addtogroup QkOPAMP
 * @brief Operational Amplifiers (OPAMP)
 *  @{
 */

#ifndef QK_OPAMP_H
#define QK_OPAMP_H

typedef uint32_t qk_opamp;

typedef enum qk_opamp_config
{
	QK_OMAMP_CONFIG_UNITY_GAIN,
	QK_OMAMP_CONFIG_NON_INVERTING,
	QK_OMAMP_CONFIG_INVERTING
} qk_opamp_config;

void qk_opamp_enable(qk_opamp opamp, qk_opamp_config config);
void qk_opamp_disable(qk_opamp opamp);

#endif

/** @}*/

