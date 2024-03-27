PULP_APP = test
PULP_APP_SRCS = dmr_matmul.c

PULP_CFLAGS = -O3
PULP_LDFLAGS = -lm

ifeq ($(fault_inject),1)
	export FI_ENABLE = 1
	export FI_SCRIPT = $(CURDIR)/pulp_inject_fault.tcl
	export FI_CLUSTER_INSTANCE = pulp_cluster_tb/cluster_i
endif

include $(PULP_SDK_HOME)/install/rules/pulp.mk
