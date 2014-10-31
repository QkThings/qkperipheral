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

/** \addtogroup QkI2C
 * @brief Analog-to-Digital Coverter (I2C)
 *  @{
 */

#ifndef QK_I2C_H
#define QK_I2C_H


typedef enum{
	QK_I2C_OK,
	QK_I2C_ERROR,
	QK_I2C_ERROR_START
} qk_i2c_status;

/**
 * @brief .
 */
uint8_t qk_i2c_start();

/**
 * @brief .
 */
uint8_t qk_i2c_write(uint8_t * data, uint8_t num_bytes);

/**
 * @brief .
 */
uint8_t qk_i2c_read(uint8_t * data, uint8_t num_bytes, bool ack);

/**
 * @brief .
 */
uint8_t qk_i2c_stop();

#endif
/** @}*/
