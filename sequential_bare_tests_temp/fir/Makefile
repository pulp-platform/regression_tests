PULP_APP = test
PULP_APP_SRCS = fir.c fir_test.c main.c crc32.c

DOTP ?= 1
WORD ?= 16

PULP_CFLAGS = -I.. -O3 -DDOTP=$(DOTP) -DWORD=$(WORD)

include $(PULP_SDK_HOME)/install/rules/pulp.mk
