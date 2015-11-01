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

#ifndef QK_UART_P_H
#define QK_UART_P_H

#ifndef QK_UART_RX_BUFSIZE
#define QK_UART_RX_BUFSIZE 64
#endif

#ifndef QK_UART_COUNT
#error "QK_UART_COUNT not defined"
#endif

typedef volatile struct
{
	uint32_t flags;
	uint16_t size;
	uint16_t i_wr;
	uint16_t i_rd;
	uint16_t count;
	uint8_t rx_buf[QK_UART_RX_BUFSIZE];
} _qk_uart_struct;


extern _qk_uart_struct _qk_uart[QK_UART_COUNT];

void _qk_uart_init(void);
void _qk_uart_startup(void);
void _qk_uart_handle_rx(qk_uart id, uint8_t data);

#endif
