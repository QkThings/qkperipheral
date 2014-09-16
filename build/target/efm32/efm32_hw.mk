###############################################################################
# qkthings
###############################################################################

# Used by qkprogram:
# USART0
# TIMER0, TIMER1

# GPIO:
# UART: USART1, LEUART0


ifneq ($(filter $(DEVICE), EFM32TG222F32),)


HWSPECS += QK_GPIO 

HWSPECS += QK_UART QK_UART_COUNT=3 
DEFINES += EFM32_USART_HIGHEST=1 EFM32_LEUART_HIGHEST=0

HWSPECS += QK_TIMER QK_TIMER_COUNT=3
DEFINES += EFM32_TIMER_HIGHEST=1 EFM32_LETIMER_HIGHEST=0

else
$(error Device $(DEVICE) not supported)
endif

DEFINES += $(HWSPECS)

