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

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define _BAUD 38400
#define _UBRR ((F_CPU / (_BAUD * 16UL)) - 1)

ISR(USART_RX_vect)
{
	_qk_uart_handle_rx( _QK_PROGRAM_UART , UDR0);
}

int _write_byte(char data, FILE *stream)
{
  qk_uart_write(_QK_PROGRAM_UART, (uint8_t*)&data, 1);
  if(data == '\n')
  {
	  data = '\r';
	  qk_uart_write(_QK_PROGRAM_UART, (uint8_t*)&data, 1);
  }
  return 0;
}

FILE _usart_stream = FDEV_SETUP_STREAM(_write_byte, NULL, _FDEV_SETUP_RW);

void _qk_uart_startup()
{
	UBRR0H = (uint8_t)(_UBRR>>8); // Set baud rate
	UBRR0L = (uint8_t)_UBRR;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); // Enable receiver and transmitter
	UCSR0C = (1<<USBS0)|(3<<UCSZ00); // Set frame format: 8data, 2stop bit
	UCSR0B |= (1 << RXCIE0); // Enable the USART Recieve Complete interrupt (USART_RXC);

	stdin=stdout=&_usart_stream;
}

void qk_uart_set_baudrate(qk_uart id, uint32_t baud)
{

}

void qk_uart_enable(qk_uart id, bool enable)
{

}

void qk_uart_write(qk_uart id, uint8_t *buf, uint16_t count)
{
	uint8_t *p_buf = buf;
	while(count--)
	{
		UDR0 = *p_buf++; // Put data into buffer, sends the data
		while ( !( UCSR0A & (1<<UDRE0)) ); // Wait for empty transmit buffer
	}
}

