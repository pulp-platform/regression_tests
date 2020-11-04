/*
 * Copyright (C) 2018 ETH Zurich and University of Bologna
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* 
 * Mantainer: Luca Valente, luca.valente2@unibo.it
 */
#ifndef CHECK_BIT_REVERSE_RAD2
#define CHECK_BIT_REVERSE_RAD2

asm volatile ("p.bitrev %[c], %[a], 25, 0\n"
             : [c] "+r" (tmp_result[0])
             : [a] "r"  (cplxbitrev_opA_radix2[0]));

asm volatile ("p.bitrev %[c], %[a], 4, 0\n"
             : [c] "+r" (tmp_result[1])
             : [a] "r"  (cplxbitrev_opA_radix2[1]));

asm volatile ("p.bitrev %[c], %[a], 30, 0\n"
             : [c] "+r" (tmp_result[2])
             : [a] "r"  (cplxbitrev_opA_radix2[2]));

asm volatile ("p.bitrev %[c], %[a], 23, 0\n"
             : [c] "+r" (tmp_result[3])
             : [a] "r"  (cplxbitrev_opA_radix2[3]));

asm volatile ("p.bitrev %[c], %[a], 22, 0\n"
             : [c] "+r" (tmp_result[4])
             : [a] "r"  (cplxbitrev_opA_radix2[4]));

asm volatile ("p.bitrev %[c], %[a], 30, 0\n"
             : [c] "+r" (tmp_result[5])
             : [a] "r"  (cplxbitrev_opA_radix2[5]));

asm volatile ("p.bitrev %[c], %[a], 30, 0\n"
             : [c] "+r" (tmp_result[6])
             : [a] "r"  (cplxbitrev_opA_radix2[6]));

asm volatile ("p.bitrev %[c], %[a], 28, 0\n"
             : [c] "+r" (tmp_result[7])
             : [a] "r"  (cplxbitrev_opA_radix2[7]));

asm volatile ("p.bitrev %[c], %[a], 19, 0\n"
             : [c] "+r" (tmp_result[8])
             : [a] "r"  (cplxbitrev_opA_radix2[8]));

asm volatile ("p.bitrev %[c], %[a], 14, 0\n"
             : [c] "+r" (tmp_result[9])
             : [a] "r"  (cplxbitrev_opA_radix2[9]));

asm volatile ("p.bitrev %[c], %[a], 11, 0\n"
             : [c] "+r" (tmp_result[10])
             : [a] "r"  (cplxbitrev_opA_radix2[10]));

asm volatile ("p.bitrev %[c], %[a], 12, 0\n"
             : [c] "+r" (tmp_result[11])
             : [a] "r"  (cplxbitrev_opA_radix2[11]));

asm volatile ("p.bitrev %[c], %[a], 31, 0\n"
             : [c] "+r" (tmp_result[12])
             : [a] "r"  (cplxbitrev_opA_radix2[12]));

asm volatile ("p.bitrev %[c], %[a], 9, 0\n"
             : [c] "+r" (tmp_result[13])
             : [a] "r"  (cplxbitrev_opA_radix2[13]));

asm volatile ("p.bitrev %[c], %[a], 8, 0\n"
             : [c] "+r" (tmp_result[14])
             : [a] "r"  (cplxbitrev_opA_radix2[14]));

asm volatile ("p.bitrev %[c], %[a], 28, 0\n"
             : [c] "+r" (tmp_result[15])
             : [a] "r"  (cplxbitrev_opA_radix2[15]));

asm volatile ("p.bitrev %[c], %[a], 22, 0\n"
             : [c] "+r" (tmp_result[16])
             : [a] "r"  (cplxbitrev_opA_radix2[16]));

asm volatile ("p.bitrev %[c], %[a], 21, 0\n"
             : [c] "+r" (tmp_result[17])
             : [a] "r"  (cplxbitrev_opA_radix2[17]));

asm volatile ("p.bitrev %[c], %[a], 7, 0\n"
             : [c] "+r" (tmp_result[18])
             : [a] "r"  (cplxbitrev_opA_radix2[18]));

asm volatile ("p.bitrev %[c], %[a], 13, 0\n"
             : [c] "+r" (tmp_result[19])
             : [a] "r"  (cplxbitrev_opA_radix2[19]));

asm volatile ("p.bitrev %[c], %[a], 10, 0\n"
             : [c] "+r" (tmp_result[20])
             : [a] "r"  (cplxbitrev_opA_radix2[20]));

asm volatile ("p.bitrev %[c], %[a], 6, 0\n"
             : [c] "+r" (tmp_result[21])
             : [a] "r"  (cplxbitrev_opA_radix2[21]));

asm volatile ("p.bitrev %[c], %[a], 2, 0\n"
             : [c] "+r" (tmp_result[22])
             : [a] "r"  (cplxbitrev_opA_radix2[22]));

asm volatile ("p.bitrev %[c], %[a], 1, 0\n"
             : [c] "+r" (tmp_result[23])
             : [a] "r"  (cplxbitrev_opA_radix2[23]));

asm volatile ("p.bitrev %[c], %[a], 31, 0\n"
             : [c] "+r" (tmp_result[24])
             : [a] "r"  (cplxbitrev_opA_radix2[24]));

asm volatile ("p.bitrev %[c], %[a], 31, 0\n"
             : [c] "+r" (tmp_result[25])
             : [a] "r"  (cplxbitrev_opA_radix2[25]));

asm volatile ("p.bitrev %[c], %[a], 7, 0\n"
             : [c] "+r" (tmp_result[26])
             : [a] "r"  (cplxbitrev_opA_radix2[26]));

asm volatile ("p.bitrev %[c], %[a], 16, 0\n"
             : [c] "+r" (tmp_result[27])
             : [a] "r"  (cplxbitrev_opA_radix2[27]));

asm volatile ("p.bitrev %[c], %[a], 13, 0\n"
             : [c] "+r" (tmp_result[28])
             : [a] "r"  (cplxbitrev_opA_radix2[28]));

asm volatile ("p.bitrev %[c], %[a], 27, 0\n"
             : [c] "+r" (tmp_result[29])
             : [a] "r"  (cplxbitrev_opA_radix2[29]));

asm volatile ("p.bitrev %[c], %[a], 26, 0\n"
             : [c] "+r" (tmp_result[30])
             : [a] "r"  (cplxbitrev_opA_radix2[30]));

asm volatile ("p.bitrev %[c], %[a], 18, 0\n"
             : [c] "+r" (tmp_result[31])
             : [a] "r"  (cplxbitrev_opA_radix2[31]));

asm volatile ("p.bitrev %[c], %[a], 5, 0\n"
             : [c] "+r" (tmp_result[32])
             : [a] "r"  (cplxbitrev_opA_radix2[32]));

asm volatile ("p.bitrev %[c], %[a], 30, 0\n"
             : [c] "+r" (tmp_result[33])
             : [a] "r"  (cplxbitrev_opA_radix2[33]));

asm volatile ("p.bitrev %[c], %[a], 25, 0\n"
             : [c] "+r" (tmp_result[34])
             : [a] "r"  (cplxbitrev_opA_radix2[34]));

asm volatile ("p.bitrev %[c], %[a], 28, 0\n"
             : [c] "+r" (tmp_result[35])
             : [a] "r"  (cplxbitrev_opA_radix2[35]));

asm volatile ("p.bitrev %[c], %[a], 2, 0\n"
             : [c] "+r" (tmp_result[36])
             : [a] "r"  (cplxbitrev_opA_radix2[36]));

asm volatile ("p.bitrev %[c], %[a], 12, 0\n"
             : [c] "+r" (tmp_result[37])
             : [a] "r"  (cplxbitrev_opA_radix2[37]));

asm volatile ("p.bitrev %[c], %[a], 21, 0\n"
             : [c] "+r" (tmp_result[38])
             : [a] "r"  (cplxbitrev_opA_radix2[38]));

asm volatile ("p.bitrev %[c], %[a], 16, 0\n"
             : [c] "+r" (tmp_result[39])
             : [a] "r"  (cplxbitrev_opA_radix2[39]));

asm volatile ("p.bitrev %[c], %[a], 5, 0\n"
             : [c] "+r" (tmp_result[40])
             : [a] "r"  (cplxbitrev_opA_radix2[40]));

asm volatile ("p.bitrev %[c], %[a], 12, 0\n"
             : [c] "+r" (tmp_result[41])
             : [a] "r"  (cplxbitrev_opA_radix2[41]));

asm volatile ("p.bitrev %[c], %[a], 0, 0\n"
             : [c] "+r" (tmp_result[42])
             : [a] "r"  (cplxbitrev_opA_radix2[42]));

asm volatile ("p.bitrev %[c], %[a], 22, 0\n"
             : [c] "+r" (tmp_result[43])
             : [a] "r"  (cplxbitrev_opA_radix2[43]));

asm volatile ("p.bitrev %[c], %[a], 20, 0\n"
             : [c] "+r" (tmp_result[44])
             : [a] "r"  (cplxbitrev_opA_radix2[44]));

asm volatile ("p.bitrev %[c], %[a], 12, 0\n"
             : [c] "+r" (tmp_result[45])
             : [a] "r"  (cplxbitrev_opA_radix2[45]));

asm volatile ("p.bitrev %[c], %[a], 13, 0\n"
             : [c] "+r" (tmp_result[46])
             : [a] "r"  (cplxbitrev_opA_radix2[46]));

asm volatile ("p.bitrev %[c], %[a], 20, 0\n"
             : [c] "+r" (tmp_result[47])
             : [a] "r"  (cplxbitrev_opA_radix2[47]));

asm volatile ("p.bitrev %[c], %[a], 31, 0\n"
             : [c] "+r" (tmp_result[48])
             : [a] "r"  (cplxbitrev_opA_radix2[48]));

asm volatile ("p.bitrev %[c], %[a], 15, 0\n"
             : [c] "+r" (tmp_result[49])
             : [a] "r"  (cplxbitrev_opA_radix2[49]));


#endif
