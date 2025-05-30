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
        random_int = random.randint(1, MAX_SIZE)
        f.write('%d, \n' % random_int)
    f.write('};\n\n')
    return

def write_define(f, name,val):
    f.write('#define %s %d\n\n' % (name,val))
    return

# Randomize between 1 and 50 the number of simple iDMA transfers to be performed
# For each transfer we set a size in bytes (the number of 32-bits elements that 
# will be moved is size / sizeof(uint32_t)).

NB_TRANSFERS = random.randint(1, 10)

# Randomize between 1 and 500 the size of each transfer

MAX_SIZE     = 1024
sizes = [None] * NB_TRANSFERS

f_sizes = open('transfer_sizes.h', 'w')
f_defines = open ('idma_defines.h', 'w')

write_transfer_sizes_array(f_sizes, 'sizes', sizes)
write_define(f_defines, 'NB_TRANSFERS', NB_TRANSFERS)