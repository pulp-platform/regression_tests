ACCELERATOR ?= neureka

LIBDIR := $(abspath ./pulp-nnx)
ACC_DIR := $(LIBDIR)/$(ACCELERATOR)

## Test
INC_DIRS += inc
PULP_APP_SRCS += $(wildcard src/*.c)
SRC_DIRS += src

## Library
INC_DIRS += $(LIBDIR)/inc $(LIBDIR)/util
PULP_APP_SRCS += $(LIBDIR)/src/pulp_nnx_$(ACCELERATOR).c $(wildcard $(LIBDIR)/util/*.c)
SRC_DIRS += $(LIBDIR)/src $(LIBDIR)/util

## Accelerator
INC_DIRS += $(ACC_DIR)/hal $(ACC_DIR)/bsp $(ACC_DIR)/bsp/astral
PULP_APP_SRCS += $(wildcard $(ACC_DIR)/hal/*.c) $(wildcard $(ACC_DIR)/bsp/astral/*.c)
SRC_DIRS += $(ACC_DIR)/hal $(ACC_DIR)/bsp/astral

## Generated 
INC_DIRS += gen/inc
SRC_DIRS += gen/src

INC_FLAGS += $(addprefix -I,$(INC_DIRS))

# Flags
ACCELERATOR_UPPERCASE := $(shell echo $(ACCELERATOR) | tr [:lower:] [:upper:])
PULP_CFLAGS += -DNNX_ACCELERATOR=\"$(ACCELERATOR)\" -DNNX_$(ACCELERATOR_UPPERCASE) -DNNX_NEUREKA_ASTRAL -DNNX_NEUREKA_PE_H=4 -DNNX_NEUREKA_PE_W=4
PULP_CFLAGS += $(INC_FLAGS) -O3

PULP_APP = test

ifeq ($(fault_inject),1)
  export FAULT_INJECTION=1
  export FAULT_INJECTION_SCRIPT=$(CURDIR)/pulp_inject_fault.tcl
endif

ifeq ($(multi_bit_upset),1)
  export MULTI_BIT_UPSET=1
else
  export MULTI_BIT_UPSET=0
endif

include $(PULP_SDK_HOME)/install/rules/pulp_rt.mk
