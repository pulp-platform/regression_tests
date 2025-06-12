#!/usr/bin/env python

import sys
import random
import argparse
import math
import re


parser = argparse.ArgumentParser(description='Generate stimuli for iDMA simple transfer')

args = parser.parse_args()

def write_transfer_parameters_struct(f, name):
    f.write ('typedef struct {\n')
    f.write ('  unsigned int size;\n')
    f.write ('  unsigned int length;\n')
    f.write ('  unsigned int src_stride_2d;\n')
    f.write ('  unsigned int dst_stride_2d;\n')
    f.write ('  unsigned int src_stride_3d;\n')
    f.write ('  unsigned int dst_stride_3d;\n')
    f.write ('  unsigned int num_reps_3d;\n')
    f.write ('} %s;\n\n' % name)
    return

def write_transfer_parameters_array(f, name, arr):
    f.write ('TransferParameters %s[] = {\n' % name)
    for v in arr:
        length          = random.randint(1, MAX_LENGTH)
        size            = random.randint(1, TRANSFER_SIZE)  + length
        src_stride_2d   = random.randint(1, MAX_STRIDE)     + length
        dst_stride_2d   = random.randint(1, MAX_STRIDE)     + length
        src_stride_3d   = random.randint(1, MAX_STRIDE)     + length
        dst_stride_3d   = random.randint(1, MAX_STRIDE)     + length
        num_reps_3d     = random.randint(1, MAX_REPS)

        f.write('{%d, %d, %d, %d, %d, %d, %d},\n' % (size, length, src_stride_2d, dst_stride_2d, src_stride_3d, dst_stride_3d, num_reps_3d))
    f.write('};\n\n')
    return

def write_define(f, name,val):
    f.write('#define %s %d\n\n' % (name,val))
    return

# Randomize between 1 and 10 the number of 3D iDMA transfers to be performed
# For each transfer we set a size in bytes.

NB_TRANSFERS = random.randint(1, 10)

# Randomize between 1 and 128 the size of each transfer
TRANSFER_SIZE = 128
MAX_STRIDE   = 10
MAX_LENGTH   = 10
MAX_REPS     = 5

transfer_params = [None] * NB_TRANSFERS

f_params    = open('idma_parameters.h', 'w')
f_defines   = open('idma_defines.h', 'w')

write_define(f_defines, 'NB_TRANSFERS', NB_TRANSFERS)
write_transfer_parameters_struct(f_params, 'TransferParameters')
write_transfer_parameters_array(f_params, 'transfer_params', transfer_params)

f_params.close()
f_defines.close()