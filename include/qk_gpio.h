#ifndef QK_GPIO_H
#define QK_GPIO_H


/** \addtogroup QkGPIO
 * @brief General Purpose Input Output (GPIO)
 *  @{
 */


/**
 * GPIO Port
 */
typedef enum
{
	QK_GPIO_PORT_A = 0, //!< QK_GPIO_PORT_A
	QK_GPIO_PORT_B = 1, //!< QK_GPIO_PORT_B
	QK_GPIO_PORT_C = 2, //!< QK_GPIO_PORT_C
	QK_GPIO_PORT_D = 3, //!< QK_GPIO_PORT_F
	QK_GPIO_PORT_E = 4, //!< QK_GPIO_PORT_E
	QK_GPIO_PORT_F = 5, //!< QK_GPIO_PORT_F
	QK_GPIO_PORT_G = 6, //!< QK_GPIO_PORT_G
	QK_GPIO_PORT_H = 7, //!< QK_GPIO_PORT_H
} qk_gpio_port;


/**
 * GPIO Pin
 */
typedef uint32_t qk_gpio_pin;

/**
 * GPIO Mode
 */
typedef enum
{
	QK_GPIO_MODE_ANALOG, //!< QK_GPIO_MODE_ANALOG
	QK_GPIO_MODE_OUTPUT, //!< QK_GPIO_MODE_OUTPUT
	QK_GPIO_MODE_INPUT,  //!< QK_GPIO_MODE_INPUT
	QK_GPIO_MODE_OUTPUT_OPEN_DRAIN, //!< QK_GPIO_MODE_OUTPUT_OPEN_DRAIN
	QK_GPIO_MODE_INPUT_PULL_UP, //!< QK_GPIO_MODE_INPUT_PULL_UP
	QK_GPIO_MODE_INPUT_PULL_DOWN //!< QK_GPIO_MODE_INPUT_PULL_DOWN
} qk_gpio_mode;

/**
 * GPIO Interrupt ID
 */
typedef enum
{
	QK_GPIO_INTERRUPT_FALL, //!< QK_GPIO_INTERRUPT_FALL
	QK_GPIO_INTERRUPT_RISE, //!< QK_GPIO_INTERRUPT_RISE
	QK_GPIO_INTERRUPT_TOGGLE //!< QK_GPIO_INTERRUPT_TOGGLE
} qk_gpio_interrupt;

/**
 * @brief .
 */
void qk_gpio_set_mode(qk_gpio_pin pin, qk_gpio_mode mode);

/**
 * @brief .
 */
void qk_gpio_set_pin(qk_gpio_pin pin, bool state);

/**
 * @brief .
 */
bool qk_gpio_get_pin(qk_gpio_pin pin);

/**
 * @brief .
 */
void qk_gpio_set_port(qk_gpio_port port, int value);

/**
 * @brief .
 */
int  qk_gpio_get_port(qk_gpio_port port);

/**
 * @brief .
 */
void qk_gpio_toggle_pin(qk_gpio_pin pin);

/**
 * @brief .
 */
void qk_gpio_toggle_port(qk_gpio_port port);

/**
 * @brief .
 */
void qk_gpio_enable_interrupt();

/**
 * @brief .
 */
void qk_gpio_disable_interrupt();

/**
 * @brief .
 */
void qk_gpio_set_interrupt(qk_gpio_pin pin, qk_gpio_interrupt id, void (*cb)(void));

/** @}*/

#endif

