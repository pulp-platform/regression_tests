#!/usr/bin/env python

import sys
import random

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
# instructions with two read registers
################################################################################

def instr_rr_base(prefix, func, mina, maxa, minb, maxb):
    global f

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


def instr_rr(prefix, func):
    instr_rr_base(prefix, func, -2**31, 2**31-1, -2**31, 2**31-1)

def instr_rr_u(prefix, func):
    instr_rr_base(prefix, func, 0, 2**32-1, 0, 2**32-1)

################################################################################
# MAC instructions with three registers
################################################################################

def mac_base(prefix, func, mina, maxa, minb, maxb, minc, maxc):
    global f

    ops_a    = []
    ops_b    = []
    ops_c    = []
    exp_res  = []
    
    for i in range(0,10):
        a = random.randint(mina, maxa)
        b = random.randint(minb, maxb)
        c = random.randint(minc, maxc)
    
        r = func(a, b, c)
    
        ops_a.append(a)
        ops_b.append(b)
        ops_c.append(c)
        exp_res.append(r)
    
    write_hex32_arr(f, '%s_a'   % prefix, ops_a)
    write_hex32_arr(f, '%s_b'   % prefix, ops_b)
    write_hex32_arr(f, '%s_act' % prefix, ops_c)
    write_hex32_arr(f, '%s_exp' % prefix, exp_res)


def mac_rrr(prefix, func):
    mac_base(prefix, func, -2**31, 2**31-1, -2**31, 2**31-1, -2**31, 2**31-1)


def mac_rrr_sl_sl(prefix, func):
    mac_base(prefix, func, -2**15, 2**15-1, -2**15, 2**15-1, -2**31, 2**31-1)

def mac_rrr_zl_zl(prefix, func):
    mac_base(prefix, func, 0, 2**16-1, 0, 2**16-1, -2**31, 2**31-1)

def mac_rrr_zl_sl(prefix, func):
    mac_base(prefix, func, 0, 2**16-1, -2**15, 2**15-1, -2**31, 2**31-1)


def mac_rrr_sh_sl(prefix, func):
    mac_base(prefix, func, -2**31, 2**31-1, -2**15, 2**15-1, -2**31, 2**31-1)

def mac_rrr_zh_zl(prefix, func):
    mac_base(prefix, func, 2**16, 2**32-1, 0, 2**16-1, -2**31, 2**31-1)

def mac_rrr_zh_sl(prefix, func):
    mac_base(prefix, func, 2**16, 2**32-1, -2**15, 2**15-1, -2**31, 2**31-1)

def mac_rrr_sh_zl(prefix, func):
    mac_base(prefix, func,(-2**15) << 16, (2**15-1) << 16, 0, 2**16-1, -2**31, 2**31-1)


def mac_rrr_sh_sh(prefix, func):
    mac_base(prefix, func, (-2**15) << 16, (2**15-1) << 16, (-2**15) << 16, (2**15-1) << 16, -2**31, 2**31-1)

def mac_rrr_zh_zh(prefix, func):
    mac_base(prefix, func, 2**16, 2**32-1, 2**16, 2**32-1, -2**31, 2**31-1)

def mac_rrr_zh_sh(prefix, func):
    mac_base(prefix, func, 2**16, 2**32-1, (-2**15) << 16, (2**15-1) << 16, -2**31, 2**31-1)


################################################################################
# MAC instructions with three registers, check for carry and overflow too
################################################################################

def mac_flags_base(prefix, func, mina, maxa, minb, maxb, minc, maxc):
    global f

    ops_a     = []
    ops_b     = []
    ops_c     = []
    exp_res   = []
    exp_flags = []
    
    for i in range(0,10):
        a = random.randint(mina, maxa)
        b = random.randint(minb, maxb)
        c = random.randint(minc, maxc)

        cy = 0
        ov = 0
    
        r = func(a, b, c)

        if((r % 0x200000000) & 0x100000000):
            cy = 0x400

        if( ((r % 0x100000000) & 0x80000000) ^ ((c % 0x100000000) & 0x80000000) ):
            ov = 0x800
            cy = 0x400
    
        ops_a.append(a)
        ops_b.append(b)
        ops_c.append(c)
        exp_res.append(r)
        exp_flags.append(ov | cy)
    
    write_hex32_arr(f, '%s_a'     % prefix, ops_a)
    write_hex32_arr(f, '%s_b'     % prefix, ops_b)
    write_hex32_arr(f, '%s_act'   % prefix, ops_c)
    write_hex32_arr(f, '%s_exp'   % prefix, exp_res)
    write_hex32_arr(f, '%s_flags' % prefix, exp_flags)


def mac_rrr_flags_cy(prefix, func):
    mac_flags_base(prefix, func, 100, 2**16-1, 100, 2**16-1, 2**32-100, 2**32-1)

def mac_rrr_flags_ov(prefix, func):
    mac_flags_base(prefix, func, 100, 2**15-1, 100, 2**15-1, -2**10, -1)

def mac_rrr_sl_sl_cy(prefix, func):
    mac_flags_base(prefix, func, 100, 2**15-1, 100, 2**15-1, 2**32-100, 2**32-1)

def mac_rrr_sl_sl_ov(prefix, func):
    mac_flags_base(prefix, func, 100, 2**15-1, 100, 2**15-1, -2**10,-1)

################################################################################
f = open('testMAC3_stimuli.h', 'w')


################################################################################
# generate testdata for l.mac (three registers)
################################################################################
mac_rrr         ('g_mac',    lambda a, b, c: (c + a * b))
mac_rrr         ('g_msu',    lambda a, b, c: (c - a * b))
mac_rrr         ('g_mmul',   lambda a, b, c: (-a * b))
mac_rrr         ('g_mul',    lambda a, b, c: ( a * b))

mac_rrr_flags_cy('g_mac3_cy', lambda a, b, c: (c + a * b))
mac_rrr_flags_ov('g_mac3_ov', lambda a, b, c: (c + a * b))


################################################################################
# generate testdata for l.{mac,mul,msu,mmul} with subword selection, no carry in
################################################################################

mac_rrr_sl_sl   ('g_macs',  lambda a, b, c: (c + a * b))
mac_rrr_zl_zl   ('g_macu',  lambda a, b, c: (c + a * b))
mac_rrr_zl_sl   ('g_macus', lambda a, b, c: (c + a * b))

mac_rrr_sl_sl   ('g_muls',  lambda a, b, c: (a * b))
mac_rrr_zl_zl   ('g_muluu', lambda a, b, c: (a * b))
mac_rrr_zl_sl   ('g_mulus', lambda a, b, c: (a * b))

mac_rrr_sl_sl   ('g_msus',  lambda a, b, c: (c - a * b))
mac_rrr_zl_zl   ('g_msuu',  lambda a, b, c: (c - a * b))
mac_rrr_zl_sl   ('g_msuus', lambda a, b, c: (c - a * b))

mac_rrr_sl_sl   ('g_mmuls',  lambda a, b, c: (-a * b))
mac_rrr_zl_zl   ('g_mmulu',  lambda a, b, c: (-a * b))
mac_rrr_zl_sl   ('g_mmulus', lambda a, b, c: (-a * b))

mac_rrr_sh_sl   ('g_machls',  lambda a, b, c: (c + (a >> 16) * b))
mac_rrr_zh_zl   ('g_machlu',  lambda a, b, c: (c + (a >> 16) * b))
mac_rrr_zh_sl   ('g_machlus', lambda a, b, c: (c + (a >> 16) * b))
mac_rrr_sh_zl   ('g_machlsu', lambda a, b, c: (c + (a >> 16) * b))

mac_rrr_sh_sl   ('g_mulhls',  lambda a, b, c: ((a >> 16) * b))
mac_rrr_zh_zl   ('g_mulhlu',  lambda a, b, c: ((a >> 16) * b))
mac_rrr_zh_sl   ('g_mulhlus', lambda a, b, c: ((a >> 16) * b))
mac_rrr_sh_zl   ('g_mulhlsu', lambda a, b, c: ((a >> 16) * b))

mac_rrr_sh_sl   ('g_msuhls',  lambda a, b, c: (c - (a >> 16) * b))
mac_rrr_zh_zl   ('g_msuhlu',  lambda a, b, c: (c - (a >> 16) * b))
mac_rrr_zh_sl   ('g_msuhlus', lambda a, b, c: (c - (a >> 16) * b))
mac_rrr_sh_zl   ('g_msuhlsu', lambda a, b, c: (c - (a >> 16) * b))

mac_rrr_sh_sl   ('g_mmulhls',  lambda a, b, c: (-(a >> 16) * b))
mac_rrr_zh_zl   ('g_mmulhlu',  lambda a, b, c: (-(a >> 16) * b))
mac_rrr_zh_sl   ('g_mmulhlus', lambda a, b, c: (-(a >> 16) * b))
mac_rrr_sh_zl   ('g_mmulhlsu', lambda a, b, c: (-(a >> 16) * b))


mac_rrr_sh_sh   ('g_machhs',  lambda a, b, c: (c + (a >> 16) * (b >> 16)))
mac_rrr_zh_zh   ('g_machhu',  lambda a, b, c: (c + (a >> 16) * (b >> 16)))
mac_rrr_zh_sh   ('g_machhus', lambda a, b, c: (c + (a >> 16) * (b >> 16)))

mac_rrr_sh_sh   ('g_mulhhs',  lambda a, b, c: ((a >> 16) * (b >> 16)))
mac_rrr_zh_zh   ('g_mulhhu',  lambda a, b, c: ((a >> 16) * (b >> 16)))
mac_rrr_zh_sh   ('g_mulhhus', lambda a, b, c: ((a >> 16) * (b >> 16)))

mac_rrr_sh_sh   ('g_msuhhs',  lambda a, b, c: (c - (a >> 16) * (b >> 16)))
mac_rrr_zh_zh   ('g_msuhhu',  lambda a, b, c: (c - (a >> 16) * (b >> 16)))
mac_rrr_zh_sh   ('g_msuhhus', lambda a, b, c: (c - (a >> 16) * (b >> 16)))

mac_rrr_sh_sh   ('g_mmulhhs',  lambda a, b, c: (-(a >> 16) * (b >> 16)))
mac_rrr_zh_zh   ('g_mmulhhu',  lambda a, b, c: (-(a >> 16) * (b >> 16)))
mac_rrr_zh_sh   ('g_mmulhhus', lambda a, b, c: (-(a >> 16) * (b >> 16)))


