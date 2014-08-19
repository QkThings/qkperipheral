#ifndef QK_GPIO_P_H
#define QK_GPIO_P_H

#define _QK_GPIO_PORT(pin)	((pin >> 16) & 0xFFFF)
#define _QK_GPIO_PIN(pin)	(pin & 0xFFFF)

void _qk_gpio_startup();

#endif

