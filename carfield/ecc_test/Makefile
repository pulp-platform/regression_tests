PULP_APP = test
PULP_APP_SRCS = ecc_test.c

PULP_CFLAGS = -O3

ifdef fault_inject
	export FAULT_INJECTION=1
	export FAULT_INJECTION_SCRIPT=pulp_inject_fault.tcl
endif

include $(PULP_SDK_HOME)/install/rules/pulp.mk
