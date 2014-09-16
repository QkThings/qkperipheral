###############################################################################
# qkthings
###############################################################################


###############################################################################
# FILES and DIRS
###############################################################################
INCLUDE_DIR += \
$(QKPERIPHERAL_DIR)/lib/efm32 \
$(ENERGYMICRO)/emlib/inc

C_SRC_DIR += \
$(QKPERIPHERAL_DIR)/lib/efm32

C_SRC += \
$(ENERGYMICRO)/emlib/src/em_assert.c \
$(ENERGYMICRO)/emlib/src/em_system.c \
$(ENERGYMICRO)/emlib/src/em_cmu.c \
$(ENERGYMICRO)/emlib/src/em_emu.c \
$(ENERGYMICRO)/emlib/src/em_timer.c \
$(ENERGYMICRO)/emlib/src/em_gpio.c \
$(ENERGYMICRO)/emlib/src/em_usart.c \
$(ENERGYMICRO)/emlib/src/em_leuart.c \
$(ENERGYMICRO)/emlib/src/em_int.c
