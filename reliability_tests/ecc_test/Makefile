PULP_APP = test
PULP_APP_SRCS = ecc_test.c

PULP_CFLAGS = -O3

ifeq ($(fault_inject),1)
	export FAULT_INJECTION=1
	export FAULT_INJECTION_SCRIPT=$(CURDIR)/pulp_inject_fault.tcl
endif

ifeq ($(multi_bit_upset),1)
	export MULTI_BIT_UPSET=1
endif

include $(PULP_SDK_HOME)/install/rules/pulp.mk
