###############################################################################
# qkthings
###############################################################################

# QkProgram:
# USART0
# TIMER0, TIMER1

# User:
# UART: USART1, LEUART0

HWSPECS += QK_POWER QK_GPIO 
HWSPECS += QK_UART QK_UART_COUNT=3 
HWSPECS += QK_TIMER QK_TIMER_COUNT=3

DEFINES += QK_VTIMER_CLKFREQ=32768

DEFINES += $(HWSPECS)

DEFINES += EFM32_USART_HIGHEST=1 EFM32_LEUART_HIGHEST=0
DEFINES += EFM32_TIMER_HIGHEST=1 EFM32_LETIMER_HIGHEST=0
