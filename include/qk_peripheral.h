#ifndef QK_PERIPHERAL_H
#define QK_PERIPHERAL_H

/**
@mainpage QkPeripheral

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

