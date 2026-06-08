PULP_APP = test

PULP_APP_FC_SRCS = main.c
PULP_APP_SRCS = support_func.c matmul.c

PULP_CFLAGS += -O3 -g3 
PULP_CFLAGS += -mno-memcpy

ifdef cores
PULP_CFLAGS += -DNUM_CORES=${cores} #-flto -DFABRIC=1
else
PULP_CFLAGS += -DNUM_CORES=1
endif


ifdef FABRIC
PULP_CFLAGS += -DFABRIC
endif

ifdef cores
PULP_CFLAGS += -DUSE_INTRINSICS
endif

ifdef thr
PULP_CFLAGS += -DTHR=${thr}
endif

PULP_CFLAGS += -fno-tree-vectorize


ifdef fmt
PULP_CFLAGS += -D${fmt} -DFIXED

else
# FP FORMAT
#INPUT DATA TYPE
ifdef fmt_A
PULP_CFLAGS += -DMA${fmt_A}
else
PULP_CFLAGS += -DMAFP32
endif

#FILTER DATA TYPE
ifdef fmt_B
PULP_CFLAGS += -DMB${fmt_B}
else
PULP_CFLAGS += -DMBFP32
endif

# OUTPUT DATA TYPE

ifdef fmt_OUT
PULP_CFLAGS += -DOUT${fmt_OUT}
else
PULP_CFLAGS += -DOUTFP32
endif
endif

# VECTORIAL FORMAT for half-precision FP
ifdef vec
PULP_CFLAGS += -DVECTORIAL
endif

# CHECK RESULTS
ifdef check
PULP_CFLAGS += -DCHECK
endif

ifdef PRINT_RESULTS
PULP_CFLAGS += -DPRINT_RESULTS
endif

ifdef verbose
PULP_CFLAGS += -DVERBOSE
endif

# STATISTICS
ifdef stats
PULP_CFLAGS += -DSTATS
endif

include $(PULP_SDK_HOME)/install/rules/pulp.mk
