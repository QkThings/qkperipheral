###############################################################################
# qkthings
###############################################################################


PROJECT_NAME = qkperipheral

INCLUDE_DIRS += \
qkperipheral/src/efm32 \
$(ENERGYMICRO)/emlib/inc

C_SRC_DIRS += \
qkperipheral/src/efm32

C_SRC_FILES += \
$(ENERGYMICRO)/emlib/src/em_assert.c \
$(ENERGYMICRO)/emlib/src/em_system.c \
$(ENERGYMICRO)/emlib/src/em_cmu.c \
$(ENERGYMICRO)/emlib/src/em_emu.c \
$(ENERGYMICRO)/emlib/src/em_timer.c \
$(ENERGYMICRO)/emlib/src/em_gpio.c \
$(ENERGYMICRO)/emlib/src/em_usart.c \
$(ENERGYMICRO)/emlib/src/em_leuart.c \
$(ENERGYMICRO)/emlib/src/em_int.c

ifeq ($(INIT_CLKFREQ),)
$(error INIT_CLKFREQ is not defined)
endif

DEFINES += INIT_CLKFREQ=$(INIT_CLKFREQ)
