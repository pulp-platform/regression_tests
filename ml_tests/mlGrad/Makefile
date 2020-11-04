PULP_APP = mlGrad
ifdef pulpFc
PULP_APP_FC_SRCS = mlGrad.c math_fns.c
else
PULP_APP_SRCS = mlGrad.c math_fns.c
endif
PULP_CFLAGS += -O3

stackSize = 4096

include $(PULP_SDK_HOME)/install/rules/pulp.mk
