####################################################################
# qkthings                                                      
####################################################################


####################################################################
# DIRS AND FLAGS                     
####################################################################

QKPERIPHERAL_DIR = qkperipheral

INCLUDE_DIR += \
$(QKPERIPHERAL_DIR)/include \
$(QKPERIPHERAL_DIR)/lib/include

C_SRC_DIR += \
$(QKPERIPHERAL_DIR)/lib

s_SRC += 
S_SRC += 

include $(QKPERIPHERAL_DIR)/build/target/$(TARGET_NAME)/$(TARGET_NAME).mk

ifeq ($(HWSPECS),)
  $(warning HWSPECS not defined!)
endif

HWSPECS_DEFINES = $(addprefix -D, $(HWSPECS))
CFLAGS += $(HWSPECS_DEFINES) 

