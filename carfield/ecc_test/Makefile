PULP_APP = test
PULP_APP_SRCS = ecc_test.c

PULP_CFLAGS = -O3

ifdef fault_inject
	export FAULT_INJECTION=1
	export FAULT_INJECTION_SCRIPT=$(CURDIR)/pulp_inject_fault.tcl
endif

ifdef multi_bit_upset
	export MULTI_BIT_UPSET=1
endif

include $(PULP_SDK_HOME)/install/rules/pulp.mk
