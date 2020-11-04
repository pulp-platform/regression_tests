PULP_APP = test

ifdef DMA_L2
PULP_APP_SRCS = parWorkload_dma_L2_tcdm.c
else
ifdef TCDM
PULP_APP_SRCS = parWorkload_tcdm.c
else
PULP_APP_SRCS = parWorkload_L2_tcdm.c
endif
endif

PULP_CFLAGS = -O3

include $(PULP_SDK_HOME)/install/rules/pulp.mk

#pulp-bench-reg --name=parMatrixMul.cycles --module=pulp_rtl_testset --params="platform($(platformName)),compiler($(OR1K_TOOLCHAIN_TYPE)),nbCores(4),elemSize(32)" --pipeline=$(PIPELINE) --artefact=pulp_rtl_testset --cmd="make run -f Makefile.sdk" --probe-regexp='execution time: (\d+)'
