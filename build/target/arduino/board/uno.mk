###############################################################################
# qkthings
###############################################################################

# QkProgram:
# USART0
# TIMER1

# User:
# QK_TIMER_

HWSPECS += QK_POWER QK_GPIO 
HWSPECS += QK_UART QK_UART_COUNT=1
HWSPECS += QK_TIMER QK_TIMER_COUNT=1
HWSPECS += QK_ADC QK_PWM QK_I2C QK_SPI

DEFINES += $(HWSPECS)

DEFINES += AVR_HAS_PORT_B AVR_HAS_PORT_C AVR_HAS_PORT_D

