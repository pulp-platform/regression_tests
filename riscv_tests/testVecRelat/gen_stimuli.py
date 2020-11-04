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

fr = open('testVecRelat_stimuli_riscv.h', 'w')

################################################################################
# generate testdata for l.min and l.minu
################################################################################

instr_rr  (fr, 'g_min',  lambda a, b: (b if (a > b) else a))
instr_rr_u(fr, 'g_minu', lambda a, b: (b if (a > b) else a))

################################################################################
# generate testdata for lv.min.h and lv.minu.h
################################################################################

def min_16(a, b):

    if(a > b):
       r = b;
    else:
       r = a;

    return r

def minu_16(a, b):
    a = a & 0xFFFF;
    b = b & 0xFFFF;

    if(a > b):
       r = b;
    else:
       r = a;

    return r

vec_16_rr    (fr, 'g_min_h',     min_16)
vec_16_rr_sc (fr, 'g_min_h_sc',  min_16)
vec_16_rr_sci(fr, 'g_min_h_sci', min_16, sciImm)

vec_16_rr    (fr, 'g_minu_h',     minu_16)
vec_16_rr_sc (fr, 'g_minu_h_sc',  minu_16)
vec_16_rr_sci(fr, 'g_minu_h_sci', minu_16, sciImm)

################################################################################
# generate testdata for lv.min.b and lv.minu.b
################################################################################

def min_8(a, b):

    if(a > b):
       r = b;
    else:
       r = a;

    return r

def minu_8(a, b):
    a = a & 0xFF;
    b = b & 0xFF;

    if(a > b):
       r = b;
    else:
       r = a;

    return r

vec_8_rr    (fr, 'g_min_b',     min_8)
vec_8_rr_sc (fr, 'g_min_b_sc',  min_8)
vec_8_rr_sci(fr, 'g_min_b_sci', min_8, sciImm)

vec_8_rr    (fr, 'g_minu_b',     minu_8)
vec_8_rr_sc (fr, 'g_minu_b_sc',  minu_8)
vec_8_rr_sci(fr, 'g_minu_b_sci', minu_8, sciImm)

################################################################################
# generate testdata for l.max and l.maxu
################################################################################

instr_rr  (fr, 'g_max',  lambda a, b: (a if (a > b) else b))
instr_rr_u(fr, 'g_maxu', lambda a, b: (a if (a > b) else b))

################################################################################
# generate testdata for lv.max.h and lv.maxu.h
################################################################################

def max_16(a, b):

    if(a > b):
       r = a;
    else:
       r = b;

    return r

def maxu_16(a, b):
    a = a & 0xFFFF;
    b = b & 0xFFFF;

    if(a > b):
       r = a;
    else:
       r = b;

    return r

vec_16_rr    (fr, 'g_max_h',     max_16)
vec_16_rr_sc (fr, 'g_max_h_sc',  max_16)
vec_16_rr_sci(fr, 'g_max_h_sci', max_16, sciImm)

vec_16_rr    (fr, 'g_maxu_h',     maxu_16)
vec_16_rr_sc (fr, 'g_maxu_h_sc',  maxu_16)
vec_16_rr_sci(fr, 'g_maxu_h_sci', maxu_16, sciImm)

################################################################################
# generate testdata for lv.max.b and lv.maxu.b
################################################################################

def max_8(a, b):

    if(a > b):
       r = a;
    else:
       r = b;

    return r

def maxu_8(a, b):
    a = a & 0xFF;
    b = b & 0xFF;

    if(a > b):
       r = a;
    else:
       r = b;

    return r

vec_8_rr    (fr, 'g_max_b',     max_8)
vec_8_rr_sc (fr, 'g_max_b_sc',  max_8)
vec_8_rr_sci(fr, 'g_max_b_sci', max_8, sciImm)

vec_8_rr    (fr, 'g_maxu_b',     maxu_8)
vec_8_rr_sc (fr, 'g_maxu_b_sc',  maxu_8)
vec_8_rr_sci(fr, 'g_maxu_b_sci', maxu_8, sciImm)
