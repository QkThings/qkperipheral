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

_qk_uart_struct _qk_uart[QK_UART_COUNT];

#if QK_UART_COUNT == 0
#error QK_UART_COUNT cannot be 0
#endif

void _qk_uart_init(void)
{
	memset((void*) _qk_uart, 0, QK_UART_COUNT*sizeof(_qk_uart_struct));
}

int qk_uart_bytes_available(qk_uart id)
{
	return _qk_uart[id].count;
}

int qk_uart_read(qk_uart id, uint8_t *buf, uint16_t count)
{
	unsigned int i;
	int bytes_to_read = count;

	qk_mcu_interrupt_disable();

	uint16_t bytes_available = _qk_uart[id].count;

	if(bytes_to_read > bytes_available)
		bytes_to_read = bytes_available;

	for(i = 0; i < bytes_to_read; i++)
	{
		buf[i] = _qk_uart[id].rx_buf[_qk_uart[id].i_rd];
		_qk_uart[id].i_rd = (_qk_uart[id].i_rd + 1) % QK_UART_RX_BUFSIZE;
	}
	_qk_uart[id].count -= bytes_to_read;

	qk_mcu_interrupt_enable();

	return bytes_to_read;
}

void _qk_uart_handle_rx(qk_uart id, uint8_t data)
{
	uint32_t i_wr;
	_qk_uart_struct *uart_struct =&_qk_uart[id];

#ifdef _QK_PERIPHERAL_DEV_UART_LOOPBACK
	qk_uart_write(id, &data, 1);
#endif

	if(uart_struct->count < QK_UART_RX_BUFSIZE)
	{
		i_wr = uart_struct->i_wr;
		uart_struct->rx_buf[i_wr] = data;
		uart_struct->i_wr = (i_wr + 1) % QK_UART_RX_BUFSIZE;
		uart_struct->count++;
	}
	else
		uart_struct->flags |= QK_UART_FLAG_OVERFLOW;
}

uint32_t qk_uart_flags(qk_uart id)
{
	return _qk_uart[id].flags;
}

void qk_uart_flags_clear(qk_uart id,uint32_t flags)
{
	_qk_uart[id].flags &= ~flags;
}
