#ifndef QK_UART_H
#define QK_UART_H

/** \addtogroup QkUART
 * @brief Universal Asynchronous Receive Transmit (UART)
 *  @{
 */

#ifndef QK_UART_COUNT
#error "QK_UART_COUNT not defined"
#endif

#ifndef QK_UART_RX_BUFSIZE
#define QK_UART_RX_BUFSIZE 16
#endif

/**
 * UART ID
 */
typedef enum
{
	QK_UART_0 = 0, //!< QK_UART_0
	QK_UART_1 = 1, //!< QK_UART_1
	QK_UART_2 = 2, //!< QK_UART_2
	QK_UART_3 = 3, //!< QK_UART_3
} qk_uart;

typedef struct
{
	uint8_t rx_buf[QK_UART_RX_BUFSIZE];
	uint16_t size;
	uint16_t i_wr;
	uint16_t i_rd;
	uint16_t count;
} _qk_uart_ctrl;

extern _qk_uart_ctrl _qk_uart[QK_UART_COUNT];

void _qk_uart_startup();

/**
 * @brief .
 */
void qk_uart_set_baudrate(qk_uart uart, uint32_t baud);

/**
 * @brief .
 */
void qk_uart_enable(qk_uart uart, bool enable);

/**
 * @brief .
 */
void qk_uart_write(qk_uart uart, uint8_t *buf, uint16_t count);

/**
 * @brief .
 */
uint16_t qk_uart_bytes_available(qk_uart uart);

/**
 * @brief .
 */
uint16_t qk_uart_read(qk_uart uart, uint8_t *buf, uint16_t count);

/** @}*/

#endif
