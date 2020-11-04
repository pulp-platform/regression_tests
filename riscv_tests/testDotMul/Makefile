PULP_APP = test
PULP_APP_SRCS = testDotMul.c

PULP_CFLAGS = -O3 -DOR10N_TESTS_PRINTF

PULP_CFLAGS += -O3

ifeq '$(cluster)' '1'
PULP_CFLAGS += -DUSE_CLUSTER
endif

include $(PULP_SDK_HOME)/install/rules/pulp.mk
