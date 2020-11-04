PULP_APP = test
PULP_APP_SRCS = matrixMul.c

PULP_CFLAGS = -O3

include $(PULP_SDK_HOME)/install/rules/pulp.mk

#pulp-bench-reg --name=parMatrixMul16.cycles --module=pulp_rtl_testset --pipeline=$(PIPELINE) --artefact=pulp_rtl_testset --cmd="make run -f Makefile.sdk" --probe-regexp='matrixMul -> success, nr. of errors: 0, execution time: (\d+)' --params="platform($(platformName)),compiler($(OR1K_TOOLCHAIN_TYPE)),nbCores(4),elemSize(16)" --probe-regexp='matrixMulTranspose -> success, nr. of errors: 0, execution time: (\d+)' --params="platform($(platformName)),compiler($(OR1K_TOOLCHAIN_TYPE)),nbCores(4),elemSize(16),transposed"
