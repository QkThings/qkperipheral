#include "system.h"
#include "em_usart.h"
#include "em_leuart.h"
#include "em_cmu.h"

_qk_uart_ctrl _qk_uart[QK_UART_COUNT];

#define USART_OVS_MASK  USART_CTRL_OVS_X4 //FIXME this shouldn't be constant

#define USART1_LOC	0
#define LEUART0_LOC	0


#if defined( USART_INPUT_RXPRS ) && defined( USART_CTRL_MVDIS )
#define USART_INITASYNC                                                              \
  { usartEnable,      /* Enable RX/TX when init completed. */                                \
    0,                /* Use current configured reference clock for configuring baudrate. */ \
    38400,            /* 38400 bits/s. */                                                   \
    usartOVS16,       /* 16x oversampling. */                                                \
    usartDatabits8,   /* 8 databits. */                                                      \
    usartNoParity,    /* No parity. */                                                       \
    usartStopbits1,   /* 1 stopbit. */                                                       \
    false,            /* Do not disable majority vote. */                                    \
    false,            /* Not USART PRS input mode. */                                        \
    usartPrsRxCh0     /* PRS channel 0. */                                                   \
  }
#else
#define USART_INITASYNC                                                              \
  { usartEnable,      /* Enable RX/TX when init completed. */                                \
    0,                /* Use current configured reference clock for configuring baudrate. */ \
    38400,            /* 38400 bits/s. */                                                   \
    usartOVS16,       /* 16x oversampling. */                                                \
    usartDatabits8,   /* 8 databits. */                                                      \
    usartNoParity,    /* No parity. */                                                       \
    usartStopbits1    /* 1 stopbit. */                                                       \
  }
#endif

#define LEUART_INIT                                                                   \
  { leuartEnable,      /* Enable RX/TX when init completed. */                                \
    0,                 /* Use current configured reference clock for configuring baudrate. */ \
    9600,              /* 9600 bits/s. */                                                     \
    leuartDatabits8,   /* 8 databits. */                                                      \
    leuartNoParity,    /* No parity. */                                                       \
    leuartStopbits1    /* 1 stopbit. */                                                       \
  }


typedef enum UART_Type
{
	UART_TYPE_UNKNOWN,
	UART_TYPE_USART,
	UART_TYPE_LEUART
} UART_Type;

static USART_TypeDef *get_usart_typedef(qk_uart uart)
{
#ifdef EFM32_USART1
	if(uart == 1)
		return USART1;
#endif
	return 0;
}

static LEUART_TypeDef *get_leuart_typedef(qk_uart uart)
{
#ifdef EFM32_LEUART0
	if(uart == EFM32_USART_HIGHEST+1)
		return LEUART0;
#endif
	return 0;
}

static UART_Type get_uart_type(qk_uart uart)
{
	if(uart >= 0 && uart <= EFM32_USART_HIGHEST)
		return UART_TYPE_USART;
	else if(uart <= (EFM32_USART_HIGHEST + EFM32_LEUART_HIGHEST + 1))
		return UART_TYPE_LEUART;
	return UART_TYPE_UNKNOWN;
}


static void usart_write_byte(USART_TypeDef *uart, uint8_t b);
static void leuart_write_byte(LEUART_TypeDef *uart, uint8_t b);
static void handle_rx_interrupt(_qk_uart_ctrl *uartCtrl, uint8_t rxData);



#ifdef EFM32_USART1
void USART1_RX_IRQHandler()
{
	uint8_t max = 2;
	uint32_t rxData;

	while((USART1->STATUS & USART_STATUS_RXDATAV) && max--)
	{
		rxData = USART1->RXDATA;
		handle_rx_interrupt(&_qk_uart[1], rxData);
	}
	USART1->IFC = USART_IF_RXDATAV;
}
#endif

#ifdef EFM32_LEUART0
void LEUART0_IRQHandler()
{
	uint8_t max = 2;
	uint32_t rxData;

	while((LEUART0->STATUS & LEUART_STATUS_RXDATAV) && max--)
	{
		rxData = LEUART0->RXDATA;
		handle_rx_interrupt(&_qk_uart[EFM32_USART_HIGHEST+1], rxData);
	}
	LEUART0->IFC = LEUART_IF_RXDATAV;
}
#endif


void _qk_uart_startup()
{
	USART_InitAsync_TypeDef usartInitAsync = USART_INITASYNC;
	LEUART_Init_TypeDef leuartInit = LEUART_INIT;

#ifdef EFM32_USART1
	CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_USART1;
	USART_InitAsync(USART1, &usartInitAsync);
	NVIC_ClearPendingIRQ(USART1_RX_IRQn);
	NVIC_EnableIRQ(USART1_RX_IRQn);
	USART1->IEN |= USART_IF_RXDATAV;
#endif

#ifdef EFM32_LEUART0
	CMU_ClockSelectSet(cmuClock_LEUART0, cmuSelect_CORELEDIV2);
	CMU->LFBCLKEN0 |= CMU_LFBCLKEN0_LEUART0;
	LEUART_Init(LEUART0, &leuartInit);
	NVIC_ClearPendingIRQ(LEUART0_IRQn);
	NVIC_EnableIRQ(LEUART0_IRQn);
	LEUART0->IEN |= LEUART_IF_RXDATAV;
#endif
}

void qk_uart_set_baudrate(qk_uart uart, uint32_t baud)
{
	UART_Type uartType = get_uart_type(uart);
	if(uartType == UART_TYPE_USART)
	{
		USART_TypeDef *usart = get_usart_typedef(uart);
		USART_BaudrateAsyncSet(usart, 0, baud, USART_OVS_MASK);
	}
	else if(uartType == UART_TYPE_LEUART)
	{
		LEUART_TypeDef *leuart = get_leuart_typedef(uart);
		LEUART_BaudrateSet(leuart, 0, baud);
	}
}

void qk_uart_enable(qk_uart uart, bool enable)
{
	if(get_uart_type(uart) == UART_TYPE_USART)
	{
		USART_TypeDef *usart = get_usart_typedef(uart);
		USART_Enable_TypeDef usart_en = (enable ? usartEnable : usartDisable);
		USART_Enable(usart, usart_en);
	}
	else
	{
		LEUART_TypeDef *leuart = get_leuart_typedef(uart);
		LEUART_Enable_TypeDef leauart_en = (enable ? leuartEnable : leuartDisable);
		LEUART_Enable(leuart, leauart_en);
	}
}

void qk_uart_write(qk_uart uart, uint8_t *buf, uint16_t count)
{
	if(get_uart_type(uart) == UART_TYPE_USART)
	{
		USART_TypeDef *usart = get_usart_typedef(uart);
		while(count--)
			usart_write_byte(usart, *buf++);
	}
	else
	{
		LEUART_TypeDef *leuart = get_leuart_typedef(uart);
		while(count--)
			leuart_write_byte(leuart, *buf++);
	}
}
uint16_t qk_uart_bytes_available(qk_uart uart)
{
	return _qk_uart[uart].count;
}
uint16_t qk_uart_read(qk_uart uart, uint8_t *buf, uint16_t count)
{
	int i;
	uint8_t bytes_to_read = count;
	if(bytes_to_read > qk_uart_bytes_available(uart))
		bytes_to_read = qk_uart_bytes_available(uart);

	for(i = 0; i < bytes_to_read; i++)
	{
		buf[i] = _qk_uart[uart].rx_buf[_qk_uart[uart].i_rd];
		_qk_uart[uart].i_rd = (_qk_uart[uart].i_rd + 1) % QK_UART_RX_BUFSIZE;
	}
	return bytes_to_read;
}


static void usart_write_byte(USART_TypeDef *uart, uint8_t b)
{
  uart->TXDATA = (uint32_t)b;
  while (!(uart->STATUS & USART_STATUS_TXBL));
}

static inline void LEUART_Sync(LEUART_TypeDef *leuart, uint32_t mask)
{
  /* Avoid deadlock if modifying the same register twice when freeze mode is */
  /* activated. */
  if (leuart->FREEZE & LEUART_FREEZE_REGFREEZE)
  {
    return;
  }

  /* Wait for any pending previous write operation to have been completed */
  /* in low frequency domain */
  while (leuart->SYNCBUSY & mask)
    ;
}


static void leuart_write_byte(LEUART_TypeDef *leuart, uint8_t b)
{
	LEUART_Sync(leuart, LEUART_SYNCBUSY_TXDATA);
	leuart->TXDATA = (uint32_t)b;
	while (!(leuart->STATUS & LEUART_STATUS_TXBL));
}

static void handle_rx_interrupt(_qk_uart_ctrl *uart_ctrl, uint8_t rxData)
{
  uint32_t i_wr;

  i_wr = uart_ctrl->i_wr;
  uart_ctrl->rx_buf[i_wr] = rxData;
  uart_ctrl->i_wr = (i_wr + 1) % QK_UART_RX_BUFSIZE;
  uart_ctrl->count++;
}



