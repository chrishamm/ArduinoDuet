# Makefile for Arduino Duet libraries
# licensed under the terms of the GPL v3
#
# written by Christian Hammacher, 2016


ARDUINO_VERSION := 1.6.8
GCC_VERSION := 4.8.3-2014q1
OPTIMISATION := -O2


# Get Arduino path
UNAME := $(shell uname -s)
ifeq ($(UNAME),Linux)
  ARDUINO_PATH := $(HOME)/.arduino15
endif
ifeq ($(UNAME),Darwin)
  ARDUINO_PATH := $(HOME)/Library/Arduino15
endif
ifeq (,$(wildcard $(ARDUINO_PATH)/.))
  $(error Arduino directory not found! Are you using Arduino $(ARDUINO_VERSION)?)
endif

# Get GCC path
GCC_PATH := $(ARDUINO_PATH)/packages/arduino/tools/arm-none-eabi-gcc/$(GCC_VERSION)
ifeq (,$(wildcard $(GCC_PATH)/.))
  $(error GCC toolchain not found! Check your installation.)
endif

# Prepare GCC paths
CROSS_COMPILE := arm-none-eabi-
CC := $(GCC_PATH)/bin/$(CROSS_COMPILE)gcc
CXX := $(GCC_PATH)/bin/$(CROSS_COMPILE)g++
AR := $(GCC_PATH)/bin/$(CROSS_COMPILE)ar


.PHONY := all
all: duet duetNG radds

duet:
	@echo "-------------------- Building libDuet --------------------"
	@$(MAKE) --no-print-directory CC=$(CC) CXX=$(CXX) AR=$(AR) OPTIMISATION=$(OPTIMISATION) -f $(PWD)/libDuet.mk

duetNG:
	@echo "------------------- Building libDuetNG -------------------"
	@$(MAKE) --no-print-directory CC=$(CC) CXX=$(CXX) AR=$(AR) OPTIMISATION=$(OPTIMISATION) -f $(PWD)/libDuetNG.mk

radds:
	@echo "------------------- Building libRADDS --------------------"
	@$(MAKE) --no-print-directory CC=$(CC) CXX=$(CXX) AR=$(AR) OPTIMISATION=$(OPTIMISATION) -f $(PWD)/libRADDS.mk

.PHONY += clean
clean:
	@$(MAKE) --no-print-directory -f $(PWD)/libDuet.mk clean
	@$(MAKE) --no-print-directory -f $(PWD)/libDuetNG.mk clean
	@$(MAKE) --no-print-directory -f $(PWD)/libRADDS.mk clean
