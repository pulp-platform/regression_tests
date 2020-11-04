PULP_APP = test
PULP_APP_SRCS = multicore.c

PULP_CFLAGS = -O3
stackSize = 10000
nbPe=4

PULP_CFLAGS += -Istencil -I../parWorkload -Isudokusolver

include $(PULP_SDK_HOME)/install/rules/pulp.mk

#pulp-bench-reg --name=multicore.cycles --module=pulp_rtl_testset --params="platform($(platformName)),compiler($(OR1K_TOOLCHAIN_TYPE)),nbCores(4),elemSize(32)" --pipeline=$(PIPELINE) --artefact=pulp_rtl_testset --cmd="make run -f Makefile.sdk" --probe-regexp='MonteCarlo application complete! Errors: 0, Time: (\d+)'
