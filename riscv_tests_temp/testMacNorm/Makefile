PULP_APP = test
PULP_APP_SRCS = testMacNorm.c

PULP_CFLAGS = -DOR10N_TESTS_PRINTF -I../includes

PULP_CFLAGS += -O3

ifeq '$(cluster)' '1'
PULP_CFLAGS += -DUSE_CLUSTER
endif

include $(PULP_SDK_HOME)/install/rules/pulp.mk
