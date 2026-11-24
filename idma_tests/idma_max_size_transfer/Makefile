PULP_APP = test
TEST_SRCS ?= idma_max_size_transfer.c
PULP_APP_SRCS = $(TEST_SRCS)

PULP_CFLAGS += -O3
stackSize = 4096

include $(PULP_SDK_HOME)/install/rules/pulp.mk

stimuli:
	python gen_stimuli_idma.py
