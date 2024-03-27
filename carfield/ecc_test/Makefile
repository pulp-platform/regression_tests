PULP_APP = test
PULP_APP_SRCS = ecc_test.c

PULP_CFLAGS = -O3

ifeq ($(fault_inject),1)
	export FI_ENABLE = 1
	export FI_SCRIPT = $(CURDIR)/pulp_inject_fault.tcl
	export FI_CLUSTER_INSTANCE = pulp_cluster_tb/cluster_i
endif

ifeq ($(multi_bit_upset),1)
	export FI_MULTI_BIT_UPSET=1
endif

include $(PULP_SDK_HOME)/install/rules/pulp.mk
