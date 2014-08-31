#ifndef QK_PERIPHERAL_H
#define QK_PERIPHERAL_H

/**
@mainpage QkPeripheral

Configuring microcontroller's peripherals through registers is always a time consuming task because it requires to understand how a given peripheral works by reading the microcontroller's datasheet and writing low level code to make it work as desired, but it's also a critical aspect of any microcontroller based embedded system. Even though many microcontrollers, from different manufacturers, have peripherals with identical functionality they are set up quite differently. This peripheral library is an abstraction layer to those common peripherals. It provides generic and simple functions that implement the most essential function of a peripheral, greatly increasing code portability. Its use is, however, optional.

*/

/** \addtogroup QkPeripheral
 *  @{
 */

#include "qk_gpio.h"
#include "qk_gpio_hw.h"

#include "qk_adc.h"
#include "qk_uart.h"

void qk_peripheral_setup();
void qk_peripheral_update(int clock_freq);

/** @}*/

#endif

