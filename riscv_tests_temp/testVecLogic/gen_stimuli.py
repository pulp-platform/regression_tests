#!/usr/bin/env python

import sys
import random
import argparse

# Copyright 2018 ETH Zurich and University of Bologna.
# Copyright and related rights are licensed under the Solderpad Hardware
# License, Version 0.51 (the License); you may not use this file except in
# compliance with the License.  You may obtain a copy of the License at
# http://solderpad.org/licenses/SHL-0.51. Unless required by applicable law
# or agreed to in writing, software, hardware and materials distributed under
# this License is distributed on an AS IS BASIS, WITHOUT WARRANTIES OR
# CONDITIONS OF ANY KIND, either express or implied. See the License for the
# specific language governing permissions and limitations under the License.


parser = argparse.ArgumentParser(description='Generate stimuli')

args = parser.parse_args()

sciImm = 11

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

################################################################################
# instructions with two three registers
################################################################################

def vec_16_rrr_base(f, prefix, func, mina, maxa, minb, maxb, mind, maxd):

    ops_a    = []
    ops_b    = []
    ops_d    = []
    exp_res  = []

    for i in range(0,10):
        op_a  = []
        op_b  = []
        op_d  = []
        res   = []

        for j in range(0,2):
            a = random.randint(mina, maxa)
            b = random.randint(minb, maxb)
            d = random.randint(mind, maxd)

            r = func(a, b, d)

            op_a.append(a)
            op_b.append(b)
            op_d.append(d)
            res.append(r)

        ops_a.append(op_a)
        ops_b.append(op_b)
        ops_d.append(op_d)
        exp_res.append(res)

    write_hex16_arr(f, '%s_a'   % prefix, ops_a)
    write_hex16_arr(f, '%s_b'   % prefix, ops_b)
    write_hex16_arr(f, '%s_d'   % prefix, ops_d)
    write_hex16_arr(f, '%s_exp' % prefix, exp_res)

def vec_16_rrr_sc_base(f, prefix, func, mina, maxa, minb, maxb, mind, maxd):

    ops_a    = []
    ops_b    = []
    ops_d    = []
    exp_res  = []

    for i in range(0,10):
        op_a  = []
        op_b  = []
        op_d  = []
        res   = []

        b = random.randint(minb, maxb)

        for j in range(0,2):
            a = random.randint(mina, maxa)
            d = random.randint(mind, maxd)

            r = func(a, b, d)

            op_a.append(a)
            op_d.append(d)
            res.append(r)

            if(j == 1):
                op_b.append(b)
            else:
                op_b.append(random.randint(minb, maxb))

        ops_a.append(op_a)
        ops_b.append(op_b)
        ops_d.append(op_d)
        exp_res.append(res)

    write_hex16_arr(f, '%s_a'   % prefix, ops_a)
    write_hex16_arr(f, '%s_b'   % prefix, ops_b)
    write_hex16_arr(f, '%s_d'   % prefix, ops_d)
    write_hex16_arr(f, '%s_exp' % prefix, exp_res)

def vec_16_rrr_sci_base(f, prefix, func, mina, maxa, imm, mind, maxd):

    ops_a    = []
    ops_d    = []
    exp_res  = []

    for i in range(0,10):
        op_a  = []
        op_d  = []
        res   = []

        for j in range(0,2):
            a = random.randint(mina, maxa)
            d = random.randint(mind, maxd)

            r = func(a, imm, d)

            op_a.append(a)
            op_d.append(d)
            res.append(r)

        ops_a.append(op_a)
        ops_d.append(op_d)
        exp_res.append(res)

    write_hex16_arr(f, '%s_a'   % prefix, ops_a)
    write_hex16_arr(f, '%s_d'   % prefix, ops_d)
    write_hex16_arr(f, '%s_exp' % prefix, exp_res)

def vec_8_rrr_base(f, prefix, func, mina, maxa, minb, maxb, mind, maxd):

    ops_a    = []
    ops_b    = []
    ops_d    = []
    exp_res  = []

    for i in range(0,10):
        op_a  = []
        op_b  = []
        op_d  = []
        res   = []

        for j in range(0,4):
            a = random.randint(mina, maxa)
            b = random.randint(minb, maxb)
            d = random.randint(mind, maxd)

            r = func(a, b, d)

            op_a.append(a)
            op_b.append(b)
            op_d.append(d)
            res.append(r)

        ops_a.append(op_a)
        ops_b.append(op_b)
        ops_d.append(op_d)
        exp_res.append(res)

    write_hex8_arr(f, '%s_a'   % prefix, ops_a)
    write_hex8_arr(f, '%s_b'   % prefix, ops_b)
    write_hex8_arr(f, '%s_d'   % prefix, ops_d)
    write_hex8_arr(f, '%s_exp' % prefix, exp_res)

def vec_8_rrr_sc_base(f, prefix, func, mina, maxa, minb, maxb, mind, maxd):

    ops_a    = []
    ops_b    = []
    ops_d    = []
    exp_res  = []

    for i in range(0,10):
        op_a  = []
        op_b  = []
        op_d  = []
        res   = []

        b = random.randint(minb, maxb)

        for j in range(0,4):
            a = random.randint(mina, maxa)
            d = random.randint(mind, maxd)

            r = func(a, b ,d)

            op_a.append(a)
            op_d.append(d)
            res.append(r)

            if(j == 4):
                op_b.append(b)
            else:
                op_b.append(random.randint(minb, maxb)) # just a random value, we don't care

        ops_a.append(op_a)
        ops_b.append(op_b)
        ops_d.append(op_d)
        exp_res.append(res)

    write_hex8_arr(f, '%s_a'   % prefix, ops_a)
    write_hex8_arr(f, '%s_b'   % prefix, ops_b)
    write_hex8_arr(f, '%s_d'   % prefix, ops_d)
    write_hex8_arr(f, '%s_exp' % prefix, exp_res)

def vec_8_rrr_sci_base(f, prefix, func, mina, maxa, imm, mind, maxd):

    ops_a    = []
    ops_d    = []
    exp_res  = []

    for i in range(0,10):
        op_a  = []
        op_d  = []
        res   = []

        for j in range(0,4):
            a = random.randint(mina, maxa)
            d = random.randint(mind, maxd)

            r = func(a, imm, d)

            op_a.append(a)
            op_d.append(d)
            res.append(r)

        ops_a.append(op_a)
        ops_d.append(op_d)
        exp_res.append(res)

    write_hex8_arr(f, '%s_a'   % prefix, ops_a)
    write_hex8_arr(f, '%s_d'   % prefix, ops_d)
    write_hex8_arr(f, '%s_exp' % prefix, exp_res)

def vec_16_rrr(f, prefix, func):
    vec_16_rrr_base(f, prefix, func, -2**15, 2**15-1, -2**15, 2**15-1, -2**15, 2**15-1)

def vec_16_rrr_sc(f, prefix, func):
    vec_16_rrr_sc_base(f, prefix, func, -2**15, 2**15-1, -2**15, 2**15-1, -2**15, 2**15-1)

def vec_16_rrr_sci(f, prefix, func, imm):
    vec_16_rrr_sci_base(f, prefix, func, -2**15, 2**15-1, imm, -2**15, 2**15-1)

def vec_8_rrr(f, prefix, func):
    vec_8_rrr_base(f, prefix, func, -2**7, 2**7-1, -2**7, 2**7-1, -2**7, 2**7-1)

def vec_8_rrr_sc(f, prefix, func):
    vec_8_rrr_sc_base(f, prefix, func, -2**7, 2**7-1, -2**7, 2**7-1, -2**7, 2**7-1)

def vec_8_rrr_sci(f, prefix, func, imm):
    vec_8_rrr_sci_base(f, prefix, func, -2**7, 2**7-1, imm, -2**7, 2**7-1)

################################################################################
# instructions with two read registers
################################################################################

def instr_rr_base(f, prefix, func, mina, maxa, minb, maxb):

    ops_a    = []
    ops_b    = []
    exp_res  = []

    for i in range(0,10):
        a = random.randint(mina, maxa)
        b = random.randint(minb, maxb)

        r = func(a, b)

        ops_a.append(a)
        ops_b.append(b)
        exp_res.append(r)

    write_hex32_arr(f, '%s_a'   % prefix, ops_a)
    write_hex32_arr(f, '%s_b'   % prefix, ops_b)
    write_hex32_arr(f, '%s_exp' % prefix, exp_res)

def vec_16_rr_base(f, prefix, func, mina, maxa, minb, maxb):

    ops_a    = []
    ops_b    = []
    exp_res  = []

    for i in range(0,10):
        op_a  = []
        op_b  = []
        res   = []

        for j in range(0,2):
            a = random.randint(mina, maxa)
            b = random.randint(minb, maxb)

            r = func(a, b)

            op_a.append(a)
            op_b.append(b)
            res.append(r)

        ops_a.append(op_a)
        ops_b.append(op_b)
        exp_res.append(res)

    write_hex16_arr(f, '%s_a'   % prefix, ops_a)
    write_hex16_arr(f, '%s_b'   % prefix, ops_b)
    write_hex16_arr(f, '%s_exp' % prefix, exp_res)

def vec_16_rr_sc_base(f, prefix, func, mina, maxa, minb, maxb):

    ops_a    = []
    ops_b    = []
    exp_res  = []

    for i in range(0,10):
        op_a  = []
        op_b  = []
        res   = []

        b = random.randint(minb, maxb)

        for j in range(0,2):
            a = random.randint(mina, maxa)

            r = func(a, b)

            op_a.append(a)
            res.append(r)

            if(j == 1):
                op_b.append(b)
            else:
                op_b.append(random.randint(minb, maxb))

        ops_a.append(op_a)
        ops_b.append(op_b)
        exp_res.append(res)

    write_hex16_arr(f, '%s_a'   % prefix, ops_a)
    write_hex16_arr(f, '%s_b'   % prefix, ops_b)
    write_hex16_arr(f, '%s_exp' % prefix, exp_res)

def vec_16_rr_sci_base(f, prefix, func, mina, maxa, imm):

    ops_a    = []
    exp_res  = []

    for i in range(0,10):
        op_a  = []
        res   = []

        for j in range(0,2):
            a = random.randint(mina, maxa)

            r = func(a, imm)

            op_a.append(a)
            res.append(r)

        ops_a.append(op_a)
        exp_res.append(res)

    write_hex16_arr(f, '%s_a'   % prefix, ops_a)
    write_hex16_arr(f, '%s_exp' % prefix, exp_res)

def vec_8_rr_base(f, prefix, func, mina, maxa, minb, maxb):

    ops_a    = []
    ops_b    = []
    exp_res  = []

    for i in range(0,10):
        op_a  = []
        op_b  = []
        res   = []

        for j in range(0,4):
            a = random.randint(mina, maxa)
            b = random.randint(minb, maxb)

            r = func(a, b)

            op_a.append(a)
            op_b.append(b)
            res.append(r)

        ops_a.append(op_a)
        ops_b.append(op_b)
        exp_res.append(res)

    write_hex8_arr(f, '%s_a'   % prefix, ops_a)
    write_hex8_arr(f, '%s_b'   % prefix, ops_b)
    write_hex8_arr(f, '%s_exp' % prefix, exp_res)

def vec_8_rr_sc_base(f, prefix, func, mina, maxa, minb, maxb):

    ops_a    = []
    ops_b    = []
    exp_res  = []

    for i in range(0,10):
        op_a  = []
        op_b  = []
        res   = []

        b = random.randint(minb, maxb)

        for j in range(0,4):
            a = random.randint(mina, maxa)

            r = func(a, b)

            op_a.append(a)
            res.append(r)

            if(j == 3):
                op_b.append(b)
            else:
                op_b.append(random.randint(minb, maxb)) # just a random value, we don't care

        ops_a.append(op_a)
        ops_b.append(op_b)
        exp_res.append(res)

    write_hex8_arr(f, '%s_a'   % prefix, ops_a)
    write_hex8_arr(f, '%s_b'   % prefix, ops_b)
    write_hex8_arr(f, '%s_exp' % prefix, exp_res)

def vec_8_rr_sci_base(f, prefix, func, mina, maxa, imm):

    ops_a    = []
    exp_res  = []

    for i in range(0,10):
        op_a  = []
        res   = []

        for j in range(0,4):
            a = random.randint(mina, maxa)

            r = func(a, imm)

            op_a.append(a)
            res.append(r)

        ops_a.append(op_a)
        exp_res.append(res)

    write_hex8_arr(f, '%s_a'   % prefix, ops_a)
    write_hex8_arr(f, '%s_exp' % prefix, exp_res)

def instr_rr(f, prefix, func):
    instr_rr_base(f, prefix, func, -2**31, 2**31-1, -2**31, 2**31-1)

def instr_rr_u(f, prefix, func):
    instr_rr_base(f, prefix, func, 0, 2**32-1, 0, 2**32-1)

def vec_16_rr(f, prefix, func):
    vec_16_rr_base(f, prefix, func, -2**15, 2**15-1, -2**15, 2**15-1)

def vec_16_rr_sc(f, prefix, func):
    vec_16_rr_sc_base(f, prefix, func, -2**15, 2**15-1, -2**15, 2**15-1)

def vec_16_rr_sci(f, prefix, func, imm):
    vec_16_rr_sci_base(f, prefix, func, -2**15, 2**15-1, imm)

def vec_8_rr(f, prefix, func):
    vec_8_rr_base(f, prefix, func, -2**7, 2**7-1, -2**7, 2**7-1)

def vec_8_rr_sc(f, prefix, func):
    vec_8_rr_sc_base(f, prefix, func, -2**7, 2**7-1, -2**7, 2**7-1)

def vec_8_rr_sci(f, prefix, func, imm):
    vec_8_rr_sci_base(f, prefix, func, -2**7, 2**7-1, imm)

def vec_16_rr_shift(f, prefix, func):
    vec_16_rr_base(f, prefix, func, -2**15, 2**15-1, 0, 15)

def vec_16_rr_shift_sc(f, prefix, func):
    vec_16_rr_sc_base(f, prefix, func, -2**15, 2**15-1, 0, 15)

def vec_16_rr_shift_sci(f, prefix, func, imm):
    vec_16_rr_sci_base(f, prefix, func, -2**15, 2**15-1, imm)

def vec_8_rr_shift(f, prefix, func):
    vec_8_rr_base(f, prefix, func, -2**7, 2**7-1, 0, 7)

def vec_8_rr_shift_sc(f, prefix, func):
    vec_8_rr_sc_base(f, prefix, func, -2**7, 2**7-1, 0, 7)

def vec_8_rr_shift_sci(f, prefix, func, imm):
    vec_8_rr_sci_base(f, prefix, func, -2**7, 2**7-1, imm)

################################################################################
# Instructions with one read register only
################################################################################
def vec_16_r_base(f, prefix, func, min, max):

    ops_a    = []
    exp_res  = []

    for i in range(0,10):
        op_a  = []
        res   = []

        for j in range(0,2):
            a = random.randint(min, max)

            r = func(a)

            op_a.append(a)
            res.append(r)

        ops_a.append(op_a)
        exp_res.append(res)

    write_hex16_arr(f, '%s_a'   % prefix, ops_a)
    write_hex16_arr(f, '%s_exp' % prefix, exp_res)

def vec_8_r_base(f, prefix, func, min, max):

    ops_a    = []
    exp_res  = []

    for i in range(0,10):
        op_a  = []
        res   = []

        for j in range(0,4):
            a = random.randint(min, max)

            r = func(a)

            op_a.append(a)
            res.append(r)

        ops_a.append(op_a)
        exp_res.append(res)

    write_hex8_arr(f, '%s_a'   % prefix, ops_a)
    write_hex8_arr(f, '%s_exp' % prefix, exp_res)

def vec_8_r(f, prefix, func):
    vec_8_r_base(f, prefix, func, -2**7, 2**7-1)

def vec_16_r(f, prefix, func):
    vec_16_r_base(f, prefix, func, -2**15, 2**15-1)

################################################################################
# Instructions with two read register and one immediate
################################################################################
def instr_32_rri(f, prefix, func, imm):

    ops_a    = []
    ops_b    = []
    exp_res  = []

    for i in range(0,10):
        a = random.randint(-2**31, 2**31-1)
        b = random.randint(-2**31, 2**31-1)

        r = func(a, b, imm)

        ops_a.append(a)
        ops_b.append(b)
        exp_res.append(r)

    write_hex32_arr(f, '%s_a'   % prefix, ops_a)
    write_hex32_arr(f, '%s_b'   % prefix, ops_b)
    write_hex32_arr(f, '%s_exp' % prefix, exp_res)

################################################################################
# Instructions with one read register and one immediate
################################################################################
def instr_32_ri(f, prefix, func, imm):

    ops_a    = []
    exp_res  = []

    for i in range(0,10):
        a = random.randint(-2**31, 2**31-1)

        r = func(a, imm)

        ops_a.append(a)
        exp_res.append(r)

    write_hex32_arr(f, '%s_a'   % prefix, ops_a)
    write_hex32_arr(f, '%s_exp' % prefix, exp_res)

def vec_16_ri_base(f, prefix, func, mina, maxa, imm):

    ops_a    = []
    exp_res  = []

    for i in range(0,10):
        op_a  = []
        res   = []

        for j in range(0,2):
            a = random.randint(mina, maxa)

            r = func(a, imm)

            op_a.append(a)
            res.append(r)

        ops_a.append(op_a)
        exp_res.append(res)

    write_hex16_arr(f, '%s_a'   % prefix, ops_a)
    write_hex16_arr(f, '%s_exp' % prefix, exp_res)

def vec_8_ri_base(f, prefix, func, mina, maxa, imm):

    ops_a    = []
    exp_res  = []

    for i in range(0,10):
        op_a  = []
        res   = []

        for j in range(0,4):
            a = random.randint(mina, maxa)

            r = func(a, imm)

            op_a.append(a)
            res.append(r)

        ops_a.append(op_a)
        exp_res.append(res)

    write_hex8_arr(f, '%s_a'   % prefix, ops_a)
    write_hex8_arr(f, '%s_exp' % prefix, exp_res)

def vec_8_ri(f, prefix, func, imm):
    vec_8_ri_base(f, prefix, func, -2**7, 2**7-1, imm)

def vec_16_ri(f, prefix, func, imm):
    vec_16_ri_base(f, prefix, func, -2**15, 2**15-1, imm)

################################################################################
fl = open('testVecLogic_stimuli_riscv.h', 'w')

################################################################################
# generate testdata for lv.srl
################################################################################
vec_16_rr_shift    (fl, 'g_srl_h',     lambda a, b: ((a % 0x10000) >> b))
vec_16_rr_shift_sc (fl, 'g_srl_h_sc',  lambda a, b: ((a % 0x10000) >> b))
vec_16_rr_shift_sci(fl, 'g_srl_h_sci', lambda a, b: ((a % 0x10000) >> b), 9)

vec_8_rr_shift     (fl, 'g_srl_b',     lambda a, b: ((a % 0x100) >> b))
vec_8_rr_shift_sc  (fl, 'g_srl_b_sc',  lambda a, b: ((a % 0x100) >> b))
vec_8_rr_shift_sci (fl, 'g_srl_b_sci', lambda a, b: ((a % 0x100) >> b), 5)

################################################################################
# generate testdata for lv.sra
################################################################################
vec_16_rr_shift    (fl, 'g_sra_h',     lambda a, b: (a >> b))
vec_16_rr_shift_sc (fl, 'g_sra_h_sc',  lambda a, b: (a >> b))
vec_16_rr_shift_sci(fl, 'g_sra_h_sci', lambda a, b: (a >> b), 9)

vec_8_rr_shift     (fl, 'g_sra_b',     lambda a, b: (a >> b))
vec_8_rr_shift_sc  (fl, 'g_sra_b_sc',  lambda a, b: (a >> b))
vec_8_rr_shift_sci (fl, 'g_sra_b_sci', lambda a, b: (a >> b), 5)

################################################################################
# generate testdata for lv.sll
################################################################################
vec_16_rr_shift    (fl, 'g_sll_h',     lambda a, b: (a << b))
vec_16_rr_shift_sc (fl, 'g_sll_h_sc',  lambda a, b: (a << b))
vec_16_rr_shift_sci(fl, 'g_sll_h_sci', lambda a, b: (a << b), 9)

vec_8_rr_shift     (fl, 'g_sll_b',     lambda a, b: (a << b))
vec_8_rr_shift_sc  (fl, 'g_sll_b_sc',  lambda a, b: (a << b))
vec_8_rr_shift_sci (fl, 'g_sll_b_sci', lambda a, b: (a << b), 5)

################################################################################
# generate testdata for lv.or
################################################################################
vec_16_rr    (fl, 'g_or_h',     lambda a, b: (a | b))
vec_16_rr_sc (fl, 'g_or_h_sc',  lambda a, b: (a | b))
vec_16_rr_sci(fl, 'g_or_h_sci', lambda a, b: (a | b), sciImm)

vec_8_rr     (fl, 'g_or_b',     lambda a, b: (a | b))
vec_8_rr_sc  (fl, 'g_or_b_sc',  lambda a, b: (a | b))
vec_8_rr_sci (fl, 'g_or_b_sci', lambda a, b: (a | b), sciImm)

################################################################################
# generate testdata for lv.xor
################################################################################
vec_16_rr    (fl, 'g_xor_h',     lambda a, b: (a ^ b))
vec_16_rr_sc (fl, 'g_xor_h_sc',  lambda a, b: (a ^ b))
vec_16_rr_sci(fl, 'g_xor_h_sci', lambda a, b: (a ^ b), sciImm)

vec_8_rr     (fl, 'g_xor_b',     lambda a, b: (a ^ b))
vec_8_rr_sc  (fl, 'g_xor_b_sc',  lambda a, b: (a ^ b))
vec_8_rr_sci (fl, 'g_xor_b_sci', lambda a, b: (a ^ b), sciImm)

################################################################################
# generate testdata for lv.and
################################################################################
vec_16_rr    (fl, 'g_and_h',     lambda a, b: (a & b))
vec_16_rr_sc (fl, 'g_and_h_sc',  lambda a, b: (a & b))
vec_16_rr_sci(fl, 'g_and_h_sci', lambda a, b: (a & b), sciImm)

vec_8_rr     (fl, 'g_and_b',     lambda a, b: (a & b))
vec_8_rr_sc  (fl, 'g_and_b_sc',  lambda a, b: (a & b))
vec_8_rr_sci (fl, 'g_and_b_sci', lambda a, b: (a & b), sciImm)


################################################################################
# generate testdata for lv.ins
################################################################################

def ins_16(a, b, L):
    r = a

    if(L == 0):
        r = r      & ~(0x0000FFFF)
        r = r | (b &   0x0000FFFF)
    else:
        r = r              & ~(0xFFFF0000)
        r = r | ((b << 16) &   0xFFFF0000)

    return r

def ins_8(a, b, L):
    r = a

    if(L == 0):
        r = r      & ~(0x000000FF)
        r = r | (b &   0x000000FF)
    elif(L == 1):
        r = r              & ~(0x0000FF00)
        r = r | ((b << 8)  &   0x0000FF00)
    elif(L == 2):
        r = r               & ~(0x00FF0000)
        r = r | ((b << 16)  &   0x00FF0000)
    else:
        r = r              & ~(0xFF000000)
        r = r | ((b << 24) &   0xFF000000)

    return r

instr_32_rri(fl,'g_ins_h0', ins_16, 0)
instr_32_rri(fl,'g_ins_h1', ins_16, 1)
instr_32_rri(fl,'g_ins_b0', ins_8,  0)
instr_32_rri(fl,'g_ins_b1', ins_8,  1)
instr_32_rri(fl,'g_ins_b2', ins_8,  2)
instr_32_rri(fl,'g_ins_b3', ins_8,  3)
