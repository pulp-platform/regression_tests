# Copyright (C) 2022-2023 ETH Zurich and University of Bologna
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# SPDX-License-Identifier: Apache-2.0
#
# Author: Yvan Tortorella (yvan.tortorella@unibo.it)
#         Francesco Conti (f.conti@unibo.it)
#		  Arpan Suravi Prasad (prasadar@iis.ee.ethz.ch)
#


LIBDIR := ../app
ACCELERATOR := neureka
STIM_DIR := ./

INC_DIRS += $(LIBDIR)/inc
APP_SRCS += $(wildcard $(LIBDIR)/src/*.c) $(wildcard $(LIBDIR)/*.c)

## Library
INC_DIRS += $(LIBDIR) $(LIBDIR)/util
APP_SRCS += $(wildcard $(LIBDIR)/util/*.c)

## Accelerator
INC_DIRS += $(LIBDIR)/hal $(LIBDIR)/gvsoc $(LIBDIR)/bsp $(LIBDIR)/bsp/testbench
APP_SRCS += $(wildcard $(LIBDIR)/hal/*.c) $(wildcard $(LIBDIR)/gvsoc/*.c) $(wildcard $(LIBDIR)/bsp/testbench/*.c)


## Generated 
INC_DIRS += inc
APP_SRCS += $(wildcard src/*.c)

INC_FLAGS += $(addprefix -I,$(INC_DIRS))

# Flags
ACCELERATOR_UPPERCASE := $(shell echo $(ACCELERATOR) | tr [:lower:] [:upper:])
APP_CFLAGS += -DNNX_ACCELERATOR=\"$(ACCELERATOR)\" -DNNX_$(ACCELERATOR_UPPERCASE) -DNNX_NEUREKA_TESTBENCH -DNNX_NEUREKA_PE_H=4 -DNNX_NEUREKA_PE_W=4
APP_CFLAGS += $(INC_FLAGS)

PULP_CFLAGS = $(APP_CFLAGS)

PULP_APP = test
PULP_APP_FC_SRCS = $(APP_SRCS)
PULP_APP_HOST_SRCS = $(APP_SRCS)

include $(PULP_SDK_HOME)/install/rules/pulp_rt.mk