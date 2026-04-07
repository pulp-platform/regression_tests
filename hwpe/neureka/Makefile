ACCELERATOR ?= neureka

LIBDIR := $(abspath ./pulp-nnx)
ACC_DIR := $(LIBDIR)/$(ACCELERATOR)

## Test
INC_DIRS += inc
PULP_APP_SRCS += $(wildcard src/*.c)
SRC_DIRS += src

## Library
INC_DIRS += $(LIBDIR)/inc $(LIBDIR)/util
PULP_APP_SRCS += $(LIBDIR)/src/pulp_nnx_$(ACCELERATOR).c $(wildcard $(LIBDIR)/util/*.c)
SRC_DIRS += $(LIBDIR)/src $(LIBDIR)/util

## Accelerator
INC_DIRS += $(ACC_DIR)/hal $(ACC_DIR)/bsp $(ACC_DIR)/bsp/astral
PULP_APP_SRCS += $(wildcard $(ACC_DIR)/hal/*.c) $(wildcard $(ACC_DIR)/bsp/astral/*.c)
SRC_DIRS += $(ACC_DIR)/hal $(ACC_DIR)/bsp/astral

## Generated
INC_DIRS += app/gen/inc
PULP_APP_SRCS += $(wildcard app/gen/src/*.c)
SRC_DIRS += app/gen/src

INC_FLAGS += $(addprefix -I,$(INC_DIRS))

 # Flags
PE_H ?= 4
PE_W ?= 4
ACCELERATOR_UPPERCASE := $(shell echo $(ACCELERATOR) | tr [:lower:] [:upper:])
PULP_CFLAGS += -DNNX_ACCELERATOR=\"$(ACCELERATOR)\" -DNNX_$(ACCELERATOR_UPPERCASE) -DNNX_NEUREKA_ASTRAL -DNNX_NEUREKA_PE_H=$(PE_H) -DNNX_NEUREKA_PE_W=$(PE_W)

PULP_CFLAGS += $(INC_FLAGS) -O3

PULP_APP = test

ifeq ($(loop),1)
  LOOP_SIZE ?= 256
  PULP_CFLAGS += -DLOOP
  PULP_CFLAGS += -DLOOP_SIZE=$(LOOP_SIZE)
endif

FS ?= 1
ifeq ($(FS), 3)
  H_IN ?= 6
  W_IN ?= 6
else
  H_IN ?= 4
  W_IN ?= 4
endif
QW ?= 8
ifeq ($(QW), 8)
  QW_BUILD=
else
  QW_BUILD=_q$(QW)
endif
K_IN ?= 64
K_OUT ?= 32
DW ?= 0
ifeq ($(DW), 1)
  DW_ARG=--depthwise
  K_OUT=$(K_IN)
else
  DW_ARG=
endif
PADDING_TOP ?= 0
PADDING_RIGHT ?= 0
PADDING_BOTTOM ?= 0
PADDING_LEFT ?= 0
SYNTH_WEIGHTS ?= 0
ifeq ($(SYNTH_WEIGHTS), 1)
  SYNTH_WEIGHTS_ARG=--synthetic_weights
else
  SYNTH_WEIGHTS_ARG=
endif
SYNTH_INPUTS ?= 0
ifeq ($(SYNTH_INPUTS), 1)
  SYNTH_INPUTS_ARG=--synthetic_inputs
else
  SYNTH_INPUTS_ARG=
endif

STIMULI=app/gen
$(STIMULI):
	mkdir -p app/gen && \
	python ./gen_toml.py --in_height=$(H_IN) --in_width=$(W_IN) --in_channel=$(K_IN) --out_channel=$(K_OUT) $(DW_ARG) \
	                                --kernel_height=$(FS) --kernel_width=$(FS) --stride_height=1 --stride_width=1 \
	                                --padding_top=$(PADDING_TOP) --padding_right=$(PADDING_RIGHT) --padding_bottom=$(PADDING_BOTTOM) --padding_left=$(PADDING_LEFT) \
									--weight_type=int$(QW) \
									$(SYNTH_WEIGHTS_ARG) $(SYNTH_INPUTS_ARG) && \
	python ./pulp-nnx/test/testgen.py test -t test -a neureka --headers -c conf.toml --skip-save --print-tensors > stimuli.log

stimuli: $(STIMULI)

ifeq ($(no_ecc),1)
 PULP_CFLAGS += -DNO_ECC
endif

ifeq ($(fault_inject),1)
  export FAULT_INJECTION=1
  export FAULT_INJECTION_SCRIPT=$(CURDIR)/pulp_inject_fault.tcl
endif

ifeq ($(multi_bit_upset),1)
  export MULTI_BIT_UPSET=1
else
  export MULTI_BIT_UPSET=0
endif

include $(PULP_SDK_HOME)/install/rules/pulp_rt.mk
