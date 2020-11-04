PULP_OMP_APP = main
PULP_APP_OMP_SRCS = main.c libSVM_load_model.c libSVM_predict.c pca_.c wavelet_.c math_fns.c

# default number of cores is 4
CORE ?= 4

PULP_CFLAGS += -DCORE=$(CORE) -O3 -g3

l2Size=262144 #256kB
l1Size= 65536 # 64kB
#l1Size= 131072 #128kB

stackSize ?= 2048 #2kB


include $(PULP_SDK_HOME)/install/rules/pulp.mk

