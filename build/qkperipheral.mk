####################################################################
# qkthings                                                      
####################################################################

QKPERIPHERAL_DIR = qkperipheral


####################################################################
# SOURCE                   
####################################################################

INCLUDE_DIR += \
$(QKPERIPHERAL_DIR)/include \
$(QKPERIPHERAL_DIR)/lib/include

C_SRC_DIR += \
$(QKPERIPHERAL_DIR)/lib

s_SRC += 
S_SRC += 


####################################################################
# TARGET
####################################################################

include $(TARGET_GLOBAL)
include $(QKPERIPHERAL_DIR)/build/target/$(TARGET_NAME)/board/$(TARGET_VARIANT).mk
include $(QKPERIPHERAL_DIR)/build/target/$(TARGET_NAME)/$(TARGET_NAME).mk





