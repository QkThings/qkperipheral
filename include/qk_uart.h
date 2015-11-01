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

/** \addtogroup QkUART
 * @brief Universal Asynchronous Receive Transmit (UART)
 *  @{
 */

#ifndef QK_UART_H
#define QK_UART_H

/**
 * UART ID
 */
typedef enum
{
	_QK_PROGRAM_UART, //!< UART used by QkProgram
	QK_UART_0, //!< QK_UART_0
	QK_UART_1, //!< QK_UART_1
	QK_UART_2, //!< QK_UART_2
	QK_UART_3 //!< QK_UART_3
} qk_uart;


typedef enum
{
	QK_UART_FLAG_OVERFLOW = (1<<0)
} qk_uart_flag;

/**
 * @brief .
 */
void qk_uart_enable(qk_uart id);

/**
 * @brief .
 */
void qk_uart_disable(qk_uart id);

/**
 * @brief .
 */
void qk_uart_set_baudrate(qk_uart id, uint32_t baud);

/**
 * @brief .
 */
void qk_uart_write(qk_uart id, uint8_t *buf, uint16_t count);

/**
 * @brief .
 */
int qk_uart_bytes_available(qk_uart id);

/**
 * @brief .
 */
int qk_uart_read(qk_uart id, uint8_t *buf, uint16_t count);


uint32_t qk_uart_flags(qk_uart id);
void qk_uart_flags_clear(qk_uart id, uint32_t flags);

#endif

/** @}*/
