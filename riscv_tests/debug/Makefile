PULP_APP = test
PULP_APP_SRCS = main.c

PULP_CFLAGS += -O3
vsimScript  = run_debug.tcl

ifeq '$(cluster)' '1'
PULP_CFLAGS += -DUSE_CLUSTER
endif

include $(PULP_SDK_HOME)/install/rules/pulp.mk
