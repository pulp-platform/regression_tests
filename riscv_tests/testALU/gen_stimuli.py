#!/usr/bin/env python

import os
import sys
import random


# include stimuli gen framework
script_dir = os.path.dirname(os.path.abspath(__file__))
inc_file = os.path.join(script_dir, '../includes/stimuligenerator.py')
execfile(inc_file)


# output file
fn = 'testALU_stimuli.h'
# number of test cases to generate
N = 15


with StimuliGenerator(fn, N) as sg:

    ############################################################################
    # Addition/Subtraction
    ############################################################################

    sg.instr_rr('g_add', lambda a, b: a + b)
    sg.instr_r('g_addi', lambda a: a + 100)

    sg.instr_rr('g_sub', lambda a, b: a - b)

    ############################################################################
    # Bitwise Logic
    ############################################################################

    sg.instr_rr('g_and', lambda a, b: a & b)
    sg.instr_rr('g_or',  lambda a, b: a | b)
    sg.instr_rr('g_xor', lambda a, b: a ^ b)

    sg.instr_r('g_andi', lambda a: a & 0x755)
    sg.instr_r('g_ori',  lambda a: a | 0x755)
    sg.instr_r('g_xori', lambda a: a ^ 0x755)

    ############################################################################
    # Shifting
    ############################################################################

    shift_min = [-2**31,   0 ]
    shift_max = [ 2**31-1, 31]

    sg.instr_base('g_sll', lambda a, b: a << b, 2, shift_min, shift_max)
    sg.instr_base('g_srl', lambda a, b: (a % 0x100000000) >> b, 2, shift_min, shift_max)
    sg.instr_base('g_sra', lambda a, b: a >> b, 2, shift_min, shift_max)

    def ror(a, b):
        a &= 0xFFFFFFFF
        r = a | (a << 32)
        r = r >> b
        return r & 0xFFFFFFFF
        r = a >> b
        r |= a << (32 - b)
        return r & 0xFFFFFFFF

    sg.instr_base('g_ror', ror, 2, shift_min, shift_max)

    sg.instr_r('g_slli', lambda a: a << 10)
    sg.instr_r('g_srli', lambda a: (a % 0x100000000) >> 9)
    sg.instr_r('g_srai', lambda a: a >> 21)

    ############################################################################
    # Set Lower- and Lower-or-Equal Than
    ############################################################################

    sg.instr_rr('g_slt', lambda a, b: 1 if a < b else 0)
    sg.instr_rru('g_sltu', lambda a, b: 1 if a < b else 0)

    sg.instr_r('g_slti', lambda a: 1 if a < 0 else 0)
    sg.instr_base('g_sltiu', lambda a: 1 if a < (2**10) else 0, 1, [0], [2**12])

    sg.instr_rr('g_slet', lambda a, b: 1 if a <= b else 0)
    sg.instr_rru('g_sletu', lambda a, b: 1 if a <= b else 0)


    # ##########################################################################
    # # generate testdata for l.cmov
    # ##########################################################################
    # ops_a    = []
    # ops_b    = []
    # exp_res  = []
    #
    # for i in range(N):
    #     a = random.randint(0, 2**32-1)
    #     b = random.randint(0, 2**32-1)
    #
    #     if(a > b):
    #         r = a
    #     else:
    #         r = b
    #
    #     ops_a.append(a)
    #     ops_b.append(b)
    #     exp_res.append(r)
    #
    # write_hex32_arr(f, 'g_cmov_a', ops_a)
    # write_hex32_arr(f, 'g_cmov_b', ops_b)
    # write_hex32_arr(f, 'g_cmov_act', ops_a)
    # write_hex32_arr(f, 'g_cmov_exp', exp_res)

