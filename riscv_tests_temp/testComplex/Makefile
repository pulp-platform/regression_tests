PULP_APP = test
PULP_APP_SRCS = testComplex.c

PULP_CFLAGS = -DOR10N_TESTS_PRINTF
PULP_FC_ARCH_CFLAGS = -march=rv32imcxgap9 -D__riscv__
PULP_CFLAGS += -O3

ifeq '$(cluster)' '1'
PULP_CFLAGS += -DUSE_CLUSTER
endif

include $(PULP_SDK_HOME)/install/rules/pulp.mk
