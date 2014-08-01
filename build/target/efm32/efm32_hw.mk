###############################################################################
# qkthings
###############################################################################

# GPIO:
# UART: USART1, LEUART0


ifneq ($(filter $(DEVICE), EFM32TG222F32),)

HWSPECS += \
QK_GPIO \
QK_UART

HWSPECS += QK_UART QK_UART_COUNT=2 
DEFINES += EFM32_USART_HIGHEST=1 EFM32_LEUART_HIGHEST=0
DEFINES += EFM32_USART1 EFM32_LEUART0

else
$(error Device $(DEVICE) not supported)
endif

DEFINES += $(HWSPECS)

