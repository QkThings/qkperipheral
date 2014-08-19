####################################################################
# qkthings                                                      
####################################################################

QKPERIPHERAL_DIR = qkperipheral

####################################################################
# TARGET
####################################################################

include $(TARGET_GLOBAL)
include $(QKPERIPHERAL_DIR)/build/target/$(TARGET_NAME)/$(TARGET_NAME)_hw.mk
include $(QKPERIPHERAL_DIR)/build/target/$(TARGET_NAME)/$(TARGET_NAME).mk


####################################################################
# SOURCE                   
####################################################################

INCLUDE_DIR += \
$(QKPERIPHERAL_DIR)/include \
$(QKPERIPHERAL_DIR)/lib/include \
$(QKPERIPHERAL_DIR)/include/board/$(TARGET_NAME)/$(TARGET_VARIANT)

C_SRC_DIR += \
$(QKPERIPHERAL_DIR)/lib

s_SRC += 
S_SRC += 



