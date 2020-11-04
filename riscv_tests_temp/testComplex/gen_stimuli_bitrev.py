#!/usr/bin/env python

import sys
import random
import argparse
import math
import re

# Copyright 2017 ETH Zurich and University of Bologna.
# Copyright and related rights are licensed under the Solderpad Hardware
# License, Version 0.51 (the License); you may not use this file except in
# compliance with the License.  You may obtain a copy of the License at
# http://solderpad.org/licenses/SHL-0.51. Unless required by applicable law
# or agreed to in writing, software, hardware and materials distributed under
# this License is distributed on an AS IS BASIS, WITHOUT WARRANTIES OR
# CONDITIONS OF ANY KIND, either express or implied. See the License for the
# specific language governing permissions and limitations under the License.

parser = argparse.ArgumentParser(description='Generate stimuli')

parser.add_argument("--riscv", dest="riscv", default=False, action="store_true", help="Generate for riscv")

args = parser.parse_args()

def write_hex8_arr(f, name, arr):
    f.write('unsigned int %s[] = {\n' % name)
    for v in arr:
        f.write('0x%02X%02X%02X%02X,\n' % (v[0] & 0xFF, v[1] & 0xFF, v[2] & 0xFF, v[3] & 0xFF))
    f.write('};\n\n')
    return

def write_hex16_arr(f, name, arr):
    f.write('unsigned int %s[] = {\n' % name)
    for v in arr:
        f.write('0x%04X%04X,\n' % (v[0] & 0xFFFF, v[1] & 0xFFFF))
    f.write('};\n\n')
    return

def write_hex32_arr(f, name, arr):
    f.write('unsigned int %s[] = {\n' % name)
    for v in arr:
        f.write('0x%08X,\n' % (v & 0xFFFFFFFF))
    f.write('};\n\n')
    return

def write_define(f, name,val):
    f.write('#define %s %d\n\n' % (name,val))
    return

def bit_reverse(input, length, radix):
    radix_log = int(math.floor(math.log(radix,2)))
    mask = (1 << radix_log) - 1
    input_reverse = input
    for i in xrange(1,length/radix_log):
        input >>= radix_log
        input_reverse <<= radix_log
        input_reverse |= (input & mask)
    mask = (1 << length) - 1
    input_reverse &= mask

    return input_reverse

def brev_encode(input, length, radix, iteration, instr_str):
    radix = int(math.floor(math.log(radix,2))) - 1
    instr_str += "\nasm volatile (\"p.bitrev %%[c], %%[a], %s, %s\\n\"\n"%(32-length, radix)
    instr_str += "             : [c] \"+r\" (tmp_result[%s])\n"%(i)
    instr_str += "             : [a] \"r\"  (cplxbitrev_opA_radix%s[%s]));\n"%(2**(radix+1), i)
    return instr_str

def write_test_in_file(inst_str, radix):
    file_loc = "testBitReverse_radix%s.c"%(str(2**radix))
    file_lines = []
    file = open(file_loc, "w")

    str_ifndef = '#ifndef CHECK_BIT_REVERSE_RAD%s\n'%(str(2**radix))
    str_define = '#define CHECK_BIT_REVERSE_RAD%s\n'%(str(2**radix))
    file_lines.append(str_ifndef)
    file_lines.append(str_define)
    func_str = inst_str + "\n\n"
    file_lines.append(func_str)
    file_lines.append("#endif\n")
    file.writelines(file_lines)
    file.close()

f = open('cplxbitrev_stimuli.h', 'w')

# Must be larger than 10
NumberOfStimuli = 50

write_define(f, 'NumberOfStimuli',NumberOfStimuli)

upperboundA = 2**32-1
lowerboundA = 0

for radix in range(1,3+1):

    ops_a    = []
    exp_brev_res = []
    inst_str = ""

    for i in range(0,NumberOfStimuli):

        # Bit reverse
        rnd_len = radix*(random.randint(1,32/radix))

        a = random.randint(lowerboundA, 2**rnd_len -1)

        brev = bit_reverse(a, rnd_len, pow(2, radix))

        inst_str_temp = ""
        inst_str += brev_encode(a, rnd_len, pow(2, radix), i, inst_str_temp)
        ops_a.append(a)
        exp_brev_res.append(brev)

    write_test_in_file(inst_str, radix)

    write_hex32_arr(f, 'cplxbitrev_opA_radix%s'%str(2**radix) , ops_a)

    write_hex32_arr(f, 'cplxbitrev_opC_radix%s'%str(2**radix) , exp_brev_res)
