PULP_APP = test
PULP_APP_SRCS = Dijkstra.c

PULP_CFLAGS = -O3 -DPROFILE

include $(PULP_SDK_HOME)/install/rules/pulp.mk

#pulp-bench-reg --name=Dijkstra.cycles --module=pulp_rtl_testset --pipeline=$(PIPELINE) --artefact=pulp_rtl_testset --cmd="make run -f Makefile.sdk" --probe-regexp='...Dijkstra application complete! Errors: 0, Time: (\d+)' --params="platform($(platformName)),compiler($(OR1K_TOOLCHAIN_TYPE)),nbCores(4)"
