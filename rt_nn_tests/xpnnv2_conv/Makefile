APP = test
PULP_APP = test
PULP_APP_SRCS = test.c
PULP_APP_SRCS += dory_dma.c
PULP_APP_SRCS += xpulp_nn_mix_conv_u4_u8_i2.c
PULP_APP_SRCS += xpulp_nn_mix_matmul_u4_u8_i2.c

CORE=8


PULP_CFLAGS += -DNUM_CORES=$(CORE) -I. -O3
PULP_LDFLAGS += -lc -lm -lgcc -Wl,-print-memory-usage 

PULP_APP_CFLAGS += -DNUM_CORES=$(CORE) -I. -O3
PULP_APP_LDFLAGS += -lc -lm -lgcc -Wl,-print-memory-usage 

PULP_CFLAGS += -DPULP_RUNTIME -DSINGLE_CORE_DMA -DALWAYS_BLOCK_DMA_TRANSFERS


include $(PULP_SDK_HOME)/install/rules/pulp.mk
