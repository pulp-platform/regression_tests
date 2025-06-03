PULP_APP = test
TEST_SRCS ?= idma_multi_core.c
PULP_APP_SRCS = $(TEST_SRCS)

ifdef VERBOSE
PULP_CFLAGS += -DVERBOSE
endif

ifdef MULTI_CORE_P
PULP_CFLAGS += -DMULTI_CORE_P
endif

ifdef MULTI_CORE_S
PULP_CFLAGS += -DMULTI_CORE_S
endif

ifdef SINGLE_CORE
PULP_CFLAGS += -DSINGLE_CORE
endif

PULP_CFLAGS += -O3
stackSize = 4096

include $(PULP_SDK_HOME)/install/rules/pulp.mk

stimuli:
	python gen_stimuli_idma.py
