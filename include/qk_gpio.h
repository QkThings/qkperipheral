#ifndef QK_GPIO_H
#define QK_GPIO_H

typedef enum qk_gpio_port
{
	QK_GPIO_PORT_A,
	QK_GPIO_PORT_B,
	QK_GPIO_PORT_C,
	QK_GPIO_PORT_D,
	QK_GPIO_PORT_E,
	QK_GPIO_PORT_F,
	QK_GPIO_PORT_G,
	QK_GPIO_PORT_H,
} qk_gpio_port;

typedef struct qk_gpio_pin
{
	qk_gpio_port port;
	uint32_t 	 bit;
} qk_gpio_pin;

typedef enum qk_gpio_mode
{
	QK_GPIO_MODE_ANALOG,
	QK_GPIO_MODE_OUTPUT,
	QK_GPIO_MODE_INPUT,
	QK_GPIO_MODE_OUTPUT_OPEN_DRAIN,
	QK_GPIO_MODE_INPUT_PULL_UP,
	QK_GPIO_MODE_INPUT_PULL_DOWN
} qk_gpio_mode;

typedef enum qk_gpio_interrupt
{
	QK_GPIO_INTERRUPT_FALL,
	QK_GPIO_INTERRUPT_RISE,
	QK_GPIO_INTERRUPT_TOGGLE
} qk_gpio_interrupt;

void qk_gpio_set_mode(qk_gpio_pin pin, qk_gpio_mode mode);
void qk_gpio_set_pin(qk_gpio_pin pin, bool state);
bool qk_gpio_get_pin(qk_gpio_pin pin);
void qk_gpio_set_port(qk_gpio_port port, int value);
int  qk_gpio_get_port(qk_gpio_port port);
void qk_gpio_toggle_pin(qk_gpio_pin pin);
void qk_gpio_toggle_port(qk_gpio_port port);

void qk_gpio_enable_interrupt();
void qk_gpio_disable_interrupt();
void qk_gpio_set_interrupt(qk_gpio_pin pin, qk_gpio_interrupt id, void (*cb)(void));

#endif

