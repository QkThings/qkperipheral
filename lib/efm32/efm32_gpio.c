#include "system.h"

#include "em_gpio.h"

void qk_gpio_hw_startup()
{
	CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_GPIO;
}

void qk_gpio_set_mode(qk_gpio_port port, qk_gpio_pin pin, qk_gpio_mode mode)
{


}
void qk_gpio_set_pin(qk_gpio_port port, qk_gpio_pin pin, bool state)
{

}
bool qk_gpio_get_pin(qk_gpio_port port, qk_gpio_pin pin)
{
	return true;
}
void qk_gpio_set_port(qk_gpio_port port, int value)
{

}
int  qk_gpio_get_port(qk_gpio_port port)
{
	return 0;
}
void qk_gpio_toggle_pin(qk_gpio_port port, qk_gpio_pin pin)
{

}
void qk_gpio_toggle_port(qk_gpio_port port)
{

}

void qk_gpio_enable_interrupt()
{

}
void qk_gpio_disable_interrupt()
{

}
void qk_gpio_set_interrupt(qk_gpio_interrupt id, qk_gpio_port port, qk_gpio_pin pin, void (*fnc)(void))
{

}
