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

#include "em_cmu.h"
#include "em_gpio.h"
#include "em_usart.h"
#include "em_leuart.h"

#define USART_OVS_MASK  USART_CTRL_OVS_X4

#define OVS_MASK  USART_CTRL_OVS_X4
#define OVS_VALUE 4

typedef enum UART_Type
{
	UART_TYPE_UNKNOWN = 0,
	UART_TYPE_USART,
	UART_TYPE_LEUART
} UART_Type;


#define EFM32_USART_IRQ(name, id) \
	void name ## _RX_IRQHandler() \
	{ int max = 3;\
		while((name->STATUS & USART_STATUS_RXDATAV) && max--) {\
		_qk_uart_handle_rx( id , USART_Rx( name )); }\
		USART_IntClear( name , USART_IF_RXDATAV); \
	}

#define EFM32_LEUART_IRQ(name, id) \
	void name ## _IRQHandler() \
	{ \
		_qk_uart_handle_rx( id , LEUART_Rx( name )); \
		LEUART_IntClear( name , LEUART_IF_RXDATAV); \
	}


EFM32_USART_IRQ( USART0, _QK_PROGRAM_UART)

EFM32_USART_IRQ( USART1, QK_UART_0)

EFM32_LEUART_IRQ(LEUART0, QK_UART_1)

static uint32_t calculateBaudRateClkDiv(uint32_t baud, uint32_t ovs)
{
  uint32_t clkdiv;
  clkdiv  = 4 * 14000000UL + (ovs * baud) / 2;
  clkdiv /= (ovs * baud);
  clkdiv -= 4;
  clkdiv *= 64;
  return clkdiv;
}

static void setBaudRate(USART_TypeDef *uart, uint32_t baud)
{
  uart->CLKDIV = calculateBaudRateClkDiv(baud, OVS_VALUE);
}

static void enable(USART_TypeDef *uart)
{
  uart->CMD = USART_CMD_RXEN | USART_CMD_TXEN;
}

static void init(USART_TypeDef *uart, uint8_t location)
{
  uart->FRAME &= ~(_USART_FRAME_DATABITS_MASK |
                   _USART_FRAME_PARITY_MASK |
                   _USART_FRAME_STOPBITS_MASK);
  uart->FRAME |= (USART_FRAME_DATABITS_EIGHT |
                  USART_FRAME_PARITY_NONE |
                  USART_FRAME_STOPBITS_ONE);

  uart->CTRL &= ~_USART_CTRL_OVS_MASK;
  uart->CTRL |= OVS_MASK;

  uart->CMD = USART_CMD_CLEARRX | USART_CMD_CLEARTX;

  uart->ROUTE = USART_ROUTE_RXPEN | USART_ROUTE_TXPEN | (location << 8);
}


static USART_TypeDef *get_usart_typedef(qk_uart uart)
{
	switch(uart)
	{
	case _QK_PROGRAM_UART: return USART0;
	case QK_UART_0: return USART1;
	}
	return 0;
}

static LEUART_TypeDef *get_leuart_typedef(qk_uart uart)
{
	if(uart == EFM32_USART_HIGHEST+1)
		return LEUART0;
	return 0;
}

static UART_Type get_uart_type(qk_uart uart)
{
	if(uart == _QK_PROGRAM_UART)
		return UART_TYPE_USART;
	else if(uart >= 0 && uart <= EFM32_USART_HIGHEST)
		return UART_TYPE_USART;
	else if(uart <= (EFM32_USART_HIGHEST + EFM32_LEUART_HIGHEST + 1))
		return UART_TYPE_LEUART;
	return UART_TYPE_UNKNOWN;
}

//----------------------------------------------------------------------------

void _qk_uart_startup()
{
	NVIC_ClearPendingIRQ(USART0_RX_IRQn);
	NVIC_EnableIRQ(USART0_RX_IRQn);
	USART_IntEnable(USART0, USART_IF_RXDATAV);

	NVIC_ClearPendingIRQ(LEUART0_IRQn);
	NVIC_EnableIRQ(LEUART0_IRQn);
	LEUART_IntEnable(LEUART0, LEUART_IF_RXDATAV);

	qk_uart_enable(_QK_PROGRAM_UART);
}


void qk_uart_enable(qk_uart id)
{
	switch(id)
	{
	case _QK_PROGRAM_UART:
		GPIO_PinModeSet(gpioPortE, 10, gpioModePushPull, 1);
		GPIO_PinModeSet(gpioPortE, 11, gpioModeInput, 0);
		CMU_ClockEnable(cmuClock_USART0, true);
		break;
	case QK_UART_1:
		CMU_ClockEnable(cmuClock_CORELE, true);
		CMU_ClockEnable(cmuClock_LEUART0, true);
		CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_CORELEDIV2);
		CMU->LFBPRESC0 = CMU_LFBPRESC0_LEUART0_DIV2;

		GPIO_PinModeSet(gpioPortD, 4, gpioModePushPull, 1);
		GPIO_PinModeSet(gpioPortD, 5, gpioModeInputPull, 1);
		break;
	}

	if(get_uart_type(id) == UART_TYPE_USART)
	{
		USART_TypeDef *usart = get_usart_typedef(id);

		USART_InitAsync_TypeDef usartInitAsync = USART_INITASYNC_DEFAULT;
		usartInitAsync.baudrate = 38400;
		usartInitAsync.oversampling = usartOVS4;
		//usartInitAsync.mvdis = true;
		USART_InitAsync(usart, &usartInitAsync);
		usart->CMD = USART_CMD_CLEARRX | USART_CMD_CLEARTX;
		usart->ROUTE = USART_ROUTE_RXPEN | USART_ROUTE_TXPEN | USART_ROUTE_LOCATION_LOC0;
		USART_IntEnable(usart, USART_IF_RXDATAV);
	}
	else
	{
		LEUART_TypeDef *leuart = get_leuart_typedef(id);

		LEUART_Init_TypeDef leuartInit = LEUART_INIT_DEFAULT;
		LEUART_Reset(leuart);
		leuartInit.baudrate = 38400;
		LEUART_Init(leuart, &leuartInit);
		leuart->CMD = LEUART_CMD_CLEARRX | LEUART_CMD_CLEARTX;
		leuart->ROUTE = LEUART_ROUTE_TXPEN | LEUART_ROUTE_RXPEN | LEUART_ROUTE_LOCATION_LOC0;
		LEUART_IntEnable(leuart, LEUART_IF_RXDATAV);
	}
}

void qk_uart_disable(qk_uart id)
{

}


void qk_uart_set_baudrate(qk_uart id, uint32_t baud)
{
	UART_Type uartType = get_uart_type(id);
	if(uartType == UART_TYPE_USART)
	{
		USART_TypeDef *usart = get_usart_typedef(id);
//		USART_BaudrateAsyncSet(usart, 0, baud, usartOVS4);

		usart->CLKDIV = calculateBaudRateClkDiv(baud, OVS_VALUE);
	}
	else if(uartType == UART_TYPE_LEUART)
	{
		LEUART_TypeDef *leuart = get_leuart_typedef(id);
		LEUART_BaudrateSet(leuart, 0, baud);
	}
}

void qk_uart_write(qk_uart id, uint8_t *buf, uint16_t count)
{
    uint8_t *p_buf = buf;
	if(get_uart_type(id) == UART_TYPE_USART)
	{
		USART_TypeDef *usart = get_usart_typedef(id);
		while(count--)
		{
			usart->TXDATA = (uint32_t)*p_buf++;
			while (!(usart->STATUS & USART_STATUS_TXBL));
//			USART_Tx(usart, *p_buf++);
		}
	}
	else
	{
		LEUART_TypeDef *leuart = get_leuart_typedef(id);
		while(count--)
		{
			/* LF register about to be modified require sync. busy check */
//			LEUART_Sync(leuart, LEUART_SYNCBUSY_TXDATA);
			  if (leuart->FREEZE & LEUART_FREEZE_REGFREEZE)
			  {
			    return;
			  }

			  /* Wait for any pending previous write operation to have been completed */
			  /* in low frequency domain */
			  while (leuart->SYNCBUSY & LEUART_SYNCBUSY_TXDATA)
			    ;

			leuart->TXDATA = (uint32_t)*p_buf++;
			/* Check that transmit buffer is empty */
			while (!(leuart->STATUS & LEUART_STATUS_TXBL));
//			LEUART_Tx(leuart, *p_buf++);
		}
	}
}

