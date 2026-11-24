PULP_APP = test
TEST_SRCS ?= test.c
PULP_APP_SRCS = $(TEST_SRCS)

ifdef VERBOSE
PULP_CFLAGS += -DVERBOSE
endif

ifdef TX
PULP_CFLAGS += -DTX
endif

ifdef RX
PULP_CFLAGS += -DRX
endif

ifdef TX_RX
PULP_CFLAGS += -DTX_RX
endif

ifdef IDLE
PULP_CFLAGS += -DIDLE
endif

ifdef DISABLE_ERROR_CHECK
PULP_CFLAGS += -DDISABLE_ERROR_CHECK
endif

ifdef CYCLE_COUNT
PULP_CFLAGS += -DCYCLE_COUNT
PULP_CFLAGS += -DVERBOSE
endif

PULP_CFLAGS += -O3

include $(PULP_SDK_HOME)/install/rules/pulp.mk

stimuli:
	python ../gen_stimuli.py 1D
