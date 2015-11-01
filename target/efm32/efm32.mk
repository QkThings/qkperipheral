###############################################################################
# qkthings
###############################################################################

INCLUDE_DIRS += \
$(LIB)/src/efm32 \
$(ENERGYMICRO)/emlib/inc

C_SRC_DIRS += \
$(LIB)/src/efm32

C_SRC_FILES += \
$(ENERGYMICRO)/emlib/src/em_system.c \
$(ENERGYMICRO)/emlib/src/em_cmu.c \
$(ENERGYMICRO)/emlib/src/em_emu.c \
$(ENERGYMICRO)/emlib/src/em_timer.c \
$(ENERGYMICRO)/emlib/src/em_gpio.c \
$(ENERGYMICRO)/emlib/src/em_usart.c \
$(ENERGYMICRO)/emlib/src/em_leuart.c \
$(ENERGYMICRO)/emlib/src/em_int.c \
$(ENERGYMICRO)/emlib/src/em_rtc.c

ifeq ($(MCU_CLKFREQ),)
$(error MCU_CLKFREQ is not defined)
endif

DEFINES += MCU_CLKFREQ=$(MCU_CLKFREQ)
