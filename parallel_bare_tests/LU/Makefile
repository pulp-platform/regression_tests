PULP_APP = test
PULP_APP_SRCS = LU.c

PULP_CFLAGS = -O3

include $(PULP_SDK_HOME)/install/rules/pulp.mk

#pulp-bench-reg --name=LU.cycles --module=pulp_rtl_testset --pipeline=$(PIPELINE) --artefact=pulp_rtl_testset --cmd="make run -f Makefile.sdk" --probe-regexp='LU application complete!  Errors: 0, Time: (\d+)' --params="platform($(platformName)),compiler($(OR1K_TOOLCHAIN_TYPE)),nbCores(4)"
