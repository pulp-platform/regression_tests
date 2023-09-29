PULP_APP = test
PULP_APP_SRCS = redmule.c
PULP_CFLAGS = -O3

ifeq ($(use_dma),1)
 PULP_CFLAGS += -DUSE_DMA
endif

include $(PULP_SDK_HOME)/install/rules/pulp_rt.mk
