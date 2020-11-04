#!/usr/bin/env python

import sys
import random


class StimuliGenerator(object):

    def __init__(self, fn, N):
        self.fn = fn
        self.N = N

    def __enter__(self):
        # define StimuliGen internall only
        class StimuliGen(object):

            SIGNED_MIN = -2**31
            SIGNED_MAX = 2**31-1
            UNSIGNED_MIN = 0
            UNSIGNED_MAX = 2**32-1

            def __init__(self, fn, N):
                self.fn = fn
                self.f = open(fn, 'w')
                self.N = N

            def cleanup(self):
                self.f.close()

            ############################################################################
            # C Array output functions
            ############################################################################

            def write_hex8_arr(self, name, arr):
                self.f.write('unsigned int %s[] = {\n' % name)
                for v in arr:
                    self.f.write('0x%02X%02X%02X%02X,\n' % (
                        v[0] & 0xFF, v[1] & 0xFF, v[2] & 0xFF, v[3] & 0xFF))
                self.f.write('};\n\n')

            def write_hex16_arr(self, name, arr):
                self.f.write('unsigned int %s[] = {\n' % name)
                for v in arr:
                    self.f.write('0x%04X%04X,\n' % (
                        v[0] & 0xFFFF, v[1] & 0xFFFF))
                self.f.write('};\n\n')

            def write_hex32_arr(self, name, arr):
                self.f.write('unsigned int %s[] = {\n' % name)
                for v in arr:
                    self.f.write('0x%08X,\n' % (v & 0xFFFFFFFF))
                self.f.write('};\n\n')

            ############################################################################
            # Random stimuli generation
            ############################################################################

            def instr_base(self, prefix, func, nparams, minv, maxv):
                ops = []
                results = []

                for i in range(N):
                    # generate random operands
                    current_ops = []
                    for j in range(nparams):
                        current_ops.append(random.randint(minv[j], maxv[j]))

                    # calculate expected value
                    if type(func) is list:
                        # apply a function to each parameter first
                        for j in range(nparams):
                            current_ops[j] = func[j](current_ops[j])
                        result = func[-1](*current_ops)
                    else:
                        result = func(*current_ops)

                    ops.append(current_ops)
                    results.append(result)

                # write operands and result to file
                abc = 'abcdefghijklmnopqrstuvwxyz'
                for i in range(nparams):
                    self.write_hex32_arr('{0}_{1}'.format(prefix, abc[i]), [x[i] for x in ops])

                self.write_hex32_arr('%s_exp' % prefix, results)

            def instr_rx32u(self, prefix, func, n):
                minv = [self.UNSIGNED_MIN for x in range(n)]
                maxv = [self.UNSIGNED_MAX for x in range(n)]
                self.instr_base(prefix, func, n, minv, maxv)

            def instr_rx32s(self, prefix, func, n):
                minv = [self.SIGNED_MIN for x in range(n)]
                maxv = [self.SIGNED_MAX for x in range(n)]
                self.instr_base(prefix, func, n, minv, maxv)

            def instr_r(self, prefix, func):
                self.instr_rx32s(prefix, func, 1)

            def instr_ru(self, prefix, func):
                self.instr_rx32u(prefix, func, 1)

            def instr_rr(self, prefix, func):
                self.instr_rx32s(prefix, func, 2)

            def instr_rru(self, prefix, func):
                self.instr_rx32u(prefix, func, 2)

            def instr_rrr(self, prefix, func):
                self.instr_rx32s(prefix, func, 3)

        # return an instance of the object for with
        self.obj = StimuliGen(self.fn, self.N)
        return self.obj

    def __exit__(self, exc_type, exc_value, traceback):
        self.obj.cleanup()


