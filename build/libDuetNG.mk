# Makefile for RepRap DuetNG board files
# licensed under the terms of the GPL v3
#
# written by Christian Hammacher, 2016


BASE_PATH := $(PWD)/..
OUTPUT_DIR := $(BASE_PATH)/variants/duetNG
OBJDIR := $(OUTPUT_DIR)/obj


DRIVERS := wdt usart udp uart twi tc supc spi rtt rtc rstc pwm pmc pio pdc matrix hsmci gpbr efc dmac dacc chipid can afec
INCLUDES := -I"$(BASE_PATH)/cores/arduino" -I"$(BASE_PATH)/asf" -I"$(BASE_PATH)/asf/sam/utils" -I"$(BASE_PATH)/asf/sam/utils/header_files" -I"$(BASE_PATH)/asf/sam/utils/preprocessor" -I"$(BASE_PATH)/asf/sam/utils/cmsis/sam4e/include" -I"$(BASE_PATH)/asf/sam/drivers" $(foreach driver,$(DRIVERS),-I"$(BASE_PATH)/asf/sam/drivers/$(driver)") -I"$(BASE_PATH)/asf/common/utils" -I"$(BASE_PATH)/asf/common/services/clock" -I"$(BASE_PATH)/asf/common/services/ioport" -I"$(BASE_PATH)/asf/common/services/sleepmgr" -I"$(BASE_PATH)/asf/common/services/usb" -I"$(BASE_PATH)/asf/common/services/usb/udc" -I"$(BASE_PATH)/asf/common/services/usb/class/cdc" -I"$(BASE_PATH)/asf/common/services/usb/class/cdc/device" -I"$(BASE_PATH)/asf/thirdparty/CMSIS/Include" -I"$(BASE_PATH)/variants/duetNG"


CFLAGS := -D__SAM4E8E__ -Dprintf=iprintf -DUDD_ENABLE -DUDD_NO_SLEEP_MGR
CFLAGS += -Wall -c -std=gnu11 -mcpu=cortex-m4 -mthumb -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -MMD -MP
CPPFLAGS := -D__SAM4E8E__ -Dprintf=iprintf -DUDD_ENABLE -DUDD_NO_SLEEP_MGR
CPPFLAGS += -Wall -c -std=gnu++11 -mcpu=cortex-m4 -mthumb -ffunction-sections -fdata-sections -fno-threadsafe-statics -fno-rtti -fno-exceptions -nostdlib --param max-inline-insns-single=500 -MMD -MP


VPATH := $(BASE_PATH)/cores/arduino $(BASE_PATH)/cores/arduino/USB $(BASE_PATH)/variants/duetNG
VPATH += $(BASE_PATH)/asf/common/services/clock/sam4e $(BASE_PATH)/asf/common/services/sleepmgr/sam $(BASE_PATH)/asf/common/services/usb/class/cdc/device $(BASE_PATH)/asf/common/services/usb/udc $(BASE_PATH)/asf/common/utils/interrupt
VPATH += $(addprefix $(BASE_PATH)/asf/sam/drivers/,$(DRIVERS)) $(BASE_PATH)/asf/sam/services/flash_efc
VPATH += $(BASE_PATH)/libraries/SharedSpi $(BASE_PATH)/libraries/Storage $(BASE_PATH)/libraries/Wire

C_SOURCES += $(foreach dir,$(VPATH),$(wildcard $(dir)/*.c))
CPP_SOURCES := $(foreach dir,$(VPATH),$(wildcard $(dir)/*.cpp))

C_OBJS := $(foreach src,$(C_SOURCES),$(OBJDIR)/$(notdir $(src:.c=.c.o)))
CPP_OBJS := $(foreach src,$(CPP_SOURCES),$(OBJDIR)/$(notdir $(src:.cpp=.cpp.o)))

DEPS := $(C_OBJS:%.o=%.d) $(CPP_OBJS:%.o=%.d)


.PHONY := all
all: $(OUTPUT_DIR)/libDuetNG.a
$(OUTPUT_DIR)/libDuetNG.a: $(OBJDIR) $(C_OBJS) $(CPP_OBJS)
	@echo "  AR      libDuetNG.a"
	@$(AR) -r "$(OUTPUT_DIR)/libDuetNG.a" $(C_OBJS) $(CPP_OBJS)
-include $(DEPS)

$(OBJDIR)/%.c.o : %.c
	@echo "  CC      $(subst $(BASE_PATH)/,,$<)"
	@$(CC) $(CFLAGS) $(OPTIMISATION) $(INCLUDES) $< -o $@

$(OBJDIR)/%.cpp.o : %.cpp
	@echo "  CC      $(subst $(BASE_PATH)/,,$<)"
	@$(CXX) $(CPPFLAGS) $(OPTIMISATION) $(INCLUDES) $< -o $@	

$(OBJDIR):
	@mkdir -p $(OBJDIR)

.PHONY += clean
clean:
	@rm -f $(OUTPUT_DIR)/libDuetNG.a
	@rm -rf $(OBJDIR)
	$(info libDuetNG build directories removed.)
