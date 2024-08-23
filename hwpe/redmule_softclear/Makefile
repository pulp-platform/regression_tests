PULP_APP = test
PULP_APP_SRCS = redmule.c
PULP_CFLAGS = -O3

ifeq ($(use_dma),1)
 PULP_CFLAGS += -DUSE_DMA
endif

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
