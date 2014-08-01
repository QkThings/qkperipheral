#ifndef QK_UART_H
#define QK_UART_H

typedef int qk_uart;

#ifndef QK_UART_COUNT
#error "QK_UART_COUNT not defined"
#endif

#ifndef QK_UART_RX_BUFSIZE
#define QK_UART_RX_BUFSIZE 16
#endif

typedef struct _qk_uart_ctrl
{
	uint8_t rx_buf[QK_UART_RX_BUFSIZE];
	uint16_t size;
	uint16_t i_wr;
	uint16_t i_rd;
	uint16_t count;
} _qk_uart_ctrl;

extern _qk_uart_ctrl _qk_uart[QK_UART_COUNT];

void _qk_uart_startup();

void qk_uart_set_baudrate(qk_uart uart, uint32_t baud);
void qk_uart_enable(qk_uart uart, bool enable);
void qk_uart_write(qk_uart uart, uint8_t *buf, uint16_t count);
uint16_t qk_uart_bytes_available(qk_uart uart);
uint16_t qk_uart_read_bytes(qk_uart uart, uint8_t *buf, uint16_t count);

#endif
