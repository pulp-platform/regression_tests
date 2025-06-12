#!/usr/bin/env python

import sys
import random
import argparse
import math
import re


parser = argparse.ArgumentParser(description='Generate stimuli for iDMA simple transfer')

args = parser.parse_args()

def write_transfer_sizes_array(f, name, arr):
    f.write ('unsigned int %s[] = {\n' % name)
    for v in arr:
        random_int = random.randint(1, TRANSFER_SIZE)
        f.write('%d, \n' % random_int)
    f.write('};\n\n')
    return

def write_define(f, name,val):
    f.write('#define %s %d\n\n' % (name,val))
    return

# Randomize the number of transfers to execute
NB_TRANSFERS = random.randint(1, 10)

# Randomize between 1 and 1024 the size (in bytes) of each transfer (Must be less than CORE_SPACE defined in the C header)
TRANSFER_SIZE = 1024

sizes = [None] * NB_TRANSFERS

f_sizes = open('idma_parameters.h', 'w')
f_defines = open ('idma_defines.h', 'w')

write_transfer_sizes_array(f_sizes, 'sizes', sizes)
write_define(f_defines, 'NB_TRANSFERS', NB_TRANSFERS)
