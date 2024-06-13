APP = test
PULP_APP = test
PULP_APP_SRCS = test.c
PULP_APP_SRCS += dory_dma.c
PULP_APP_SRCS += xpulp_tnn_linear_ternary_i32_signed.c

CORE=8


PULP_CFLAGS += -DNUM_CORES=$(CORE) -I. -O3
PULP_LDFLAGS += -lc -lm -lgcc -Wl,-print-memory-usage 

PULP_APP_CFLAGS += -DNUM_CORES=$(CORE) -I. -O3
PULP_APP_LDFLAGS += -lc -lm -lgcc -Wl,-print-memory-usage 

PULP_CFLAGS += -DPULP_RUNTIME -DSINGLE_CORE_DMA -DALWAYS_BLOCK_DMA_TRANSFERS


include $(PULP_SDK_HOME)/install/rules/pulp.mk
