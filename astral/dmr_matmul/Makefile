PULP_APP = test
PULP_APP_SRCS = dmr_matmul.c

PULP_CFLAGS = -O3
PULP_LDFLAGS = -lm

ifeq ($(fault_inject),1)
	export FAULT_INJECTION=1
	export FAULT_INJECTION_SCRIPT=$(CURDIR)/pulp_inject_fault.tcl
endif

include $(PULP_SDK_HOME)/install/rules/pulp.mk
