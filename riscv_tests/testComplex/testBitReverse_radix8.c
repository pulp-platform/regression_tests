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
#ifndef CHECK_BIT_REVERSE_RAD8
#define CHECK_BIT_REVERSE_RAD8

asm volatile ("p.bitrev %[c], %[a], 23, 2\n"
             : [c] "+r" (tmp_result[0])
             : [a] "r"  (cplxbitrev_opA_radix8[0]));

asm volatile ("p.bitrev %[c], %[a], 17, 2\n"
             : [c] "+r" (tmp_result[1])
             : [a] "r"  (cplxbitrev_opA_radix8[1]));

asm volatile ("p.bitrev %[c], %[a], 29, 2\n"
             : [c] "+r" (tmp_result[2])
             : [a] "r"  (cplxbitrev_opA_radix8[2]));

asm volatile ("p.bitrev %[c], %[a], 14, 2\n"
             : [c] "+r" (tmp_result[3])
             : [a] "r"  (cplxbitrev_opA_radix8[3]));

asm volatile ("p.bitrev %[c], %[a], 2, 2\n"
             : [c] "+r" (tmp_result[4])
             : [a] "r"  (cplxbitrev_opA_radix8[4]));

asm volatile ("p.bitrev %[c], %[a], 14, 2\n"
             : [c] "+r" (tmp_result[5])
             : [a] "r"  (cplxbitrev_opA_radix8[5]));

asm volatile ("p.bitrev %[c], %[a], 11, 2\n"
             : [c] "+r" (tmp_result[6])
             : [a] "r"  (cplxbitrev_opA_radix8[6]));

asm volatile ("p.bitrev %[c], %[a], 5, 2\n"
             : [c] "+r" (tmp_result[7])
             : [a] "r"  (cplxbitrev_opA_radix8[7]));

asm volatile ("p.bitrev %[c], %[a], 23, 2\n"
             : [c] "+r" (tmp_result[8])
             : [a] "r"  (cplxbitrev_opA_radix8[8]));

asm volatile ("p.bitrev %[c], %[a], 14, 2\n"
             : [c] "+r" (tmp_result[9])
             : [a] "r"  (cplxbitrev_opA_radix8[9]));

asm volatile ("p.bitrev %[c], %[a], 11, 2\n"
             : [c] "+r" (tmp_result[10])
             : [a] "r"  (cplxbitrev_opA_radix8[10]));

asm volatile ("p.bitrev %[c], %[a], 5, 2\n"
             : [c] "+r" (tmp_result[11])
             : [a] "r"  (cplxbitrev_opA_radix8[11]));

asm volatile ("p.bitrev %[c], %[a], 26, 2\n"
             : [c] "+r" (tmp_result[12])
             : [a] "r"  (cplxbitrev_opA_radix8[12]));

asm volatile ("p.bitrev %[c], %[a], 26, 2\n"
             : [c] "+r" (tmp_result[13])
             : [a] "r"  (cplxbitrev_opA_radix8[13]));

asm volatile ("p.bitrev %[c], %[a], 29, 2\n"
             : [c] "+r" (tmp_result[14])
             : [a] "r"  (cplxbitrev_opA_radix8[14]));

asm volatile ("p.bitrev %[c], %[a], 8, 2\n"
             : [c] "+r" (tmp_result[15])
             : [a] "r"  (cplxbitrev_opA_radix8[15]));

asm volatile ("p.bitrev %[c], %[a], 11, 2\n"
             : [c] "+r" (tmp_result[16])
             : [a] "r"  (cplxbitrev_opA_radix8[16]));

asm volatile ("p.bitrev %[c], %[a], 11, 2\n"
             : [c] "+r" (tmp_result[17])
             : [a] "r"  (cplxbitrev_opA_radix8[17]));

asm volatile ("p.bitrev %[c], %[a], 20, 2\n"
             : [c] "+r" (tmp_result[18])
             : [a] "r"  (cplxbitrev_opA_radix8[18]));

asm volatile ("p.bitrev %[c], %[a], 17, 2\n"
             : [c] "+r" (tmp_result[19])
             : [a] "r"  (cplxbitrev_opA_radix8[19]));

asm volatile ("p.bitrev %[c], %[a], 23, 2\n"
             : [c] "+r" (tmp_result[20])
             : [a] "r"  (cplxbitrev_opA_radix8[20]));

asm volatile ("p.bitrev %[c], %[a], 20, 2\n"
             : [c] "+r" (tmp_result[21])
             : [a] "r"  (cplxbitrev_opA_radix8[21]));

asm volatile ("p.bitrev %[c], %[a], 29, 2\n"
             : [c] "+r" (tmp_result[22])
             : [a] "r"  (cplxbitrev_opA_radix8[22]));

asm volatile ("p.bitrev %[c], %[a], 17, 2\n"
             : [c] "+r" (tmp_result[23])
             : [a] "r"  (cplxbitrev_opA_radix8[23]));

asm volatile ("p.bitrev %[c], %[a], 14, 2\n"
             : [c] "+r" (tmp_result[24])
             : [a] "r"  (cplxbitrev_opA_radix8[24]));

asm volatile ("p.bitrev %[c], %[a], 17, 2\n"
             : [c] "+r" (tmp_result[25])
             : [a] "r"  (cplxbitrev_opA_radix8[25]));

asm volatile ("p.bitrev %[c], %[a], 20, 2\n"
             : [c] "+r" (tmp_result[26])
             : [a] "r"  (cplxbitrev_opA_radix8[26]));

asm volatile ("p.bitrev %[c], %[a], 11, 2\n"
             : [c] "+r" (tmp_result[27])
             : [a] "r"  (cplxbitrev_opA_radix8[27]));

asm volatile ("p.bitrev %[c], %[a], 5, 2\n"
             : [c] "+r" (tmp_result[28])
             : [a] "r"  (cplxbitrev_opA_radix8[28]));

asm volatile ("p.bitrev %[c], %[a], 20, 2\n"
             : [c] "+r" (tmp_result[29])
             : [a] "r"  (cplxbitrev_opA_radix8[29]));

asm volatile ("p.bitrev %[c], %[a], 14, 2\n"
             : [c] "+r" (tmp_result[30])
             : [a] "r"  (cplxbitrev_opA_radix8[30]));

asm volatile ("p.bitrev %[c], %[a], 14, 2\n"
             : [c] "+r" (tmp_result[31])
             : [a] "r"  (cplxbitrev_opA_radix8[31]));

asm volatile ("p.bitrev %[c], %[a], 14, 2\n"
             : [c] "+r" (tmp_result[32])
             : [a] "r"  (cplxbitrev_opA_radix8[32]));

asm volatile ("p.bitrev %[c], %[a], 14, 2\n"
             : [c] "+r" (tmp_result[33])
             : [a] "r"  (cplxbitrev_opA_radix8[33]));

asm volatile ("p.bitrev %[c], %[a], 11, 2\n"
             : [c] "+r" (tmp_result[34])
             : [a] "r"  (cplxbitrev_opA_radix8[34]));

asm volatile ("p.bitrev %[c], %[a], 8, 2\n"
             : [c] "+r" (tmp_result[35])
             : [a] "r"  (cplxbitrev_opA_radix8[35]));

asm volatile ("p.bitrev %[c], %[a], 29, 2\n"
             : [c] "+r" (tmp_result[36])
             : [a] "r"  (cplxbitrev_opA_radix8[36]));

asm volatile ("p.bitrev %[c], %[a], 23, 2\n"
             : [c] "+r" (tmp_result[37])
             : [a] "r"  (cplxbitrev_opA_radix8[37]));

asm volatile ("p.bitrev %[c], %[a], 23, 2\n"
             : [c] "+r" (tmp_result[38])
             : [a] "r"  (cplxbitrev_opA_radix8[38]));

asm volatile ("p.bitrev %[c], %[a], 17, 2\n"
             : [c] "+r" (tmp_result[39])
             : [a] "r"  (cplxbitrev_opA_radix8[39]));

asm volatile ("p.bitrev %[c], %[a], 5, 2\n"
             : [c] "+r" (tmp_result[40])
             : [a] "r"  (cplxbitrev_opA_radix8[40]));

asm volatile ("p.bitrev %[c], %[a], 8, 2\n"
             : [c] "+r" (tmp_result[41])
             : [a] "r"  (cplxbitrev_opA_radix8[41]));

asm volatile ("p.bitrev %[c], %[a], 23, 2\n"
             : [c] "+r" (tmp_result[42])
             : [a] "r"  (cplxbitrev_opA_radix8[42]));

asm volatile ("p.bitrev %[c], %[a], 8, 2\n"
             : [c] "+r" (tmp_result[43])
             : [a] "r"  (cplxbitrev_opA_radix8[43]));

asm volatile ("p.bitrev %[c], %[a], 2, 2\n"
             : [c] "+r" (tmp_result[44])
             : [a] "r"  (cplxbitrev_opA_radix8[44]));

asm volatile ("p.bitrev %[c], %[a], 29, 2\n"
             : [c] "+r" (tmp_result[45])
             : [a] "r"  (cplxbitrev_opA_radix8[45]));

asm volatile ("p.bitrev %[c], %[a], 23, 2\n"
             : [c] "+r" (tmp_result[46])
             : [a] "r"  (cplxbitrev_opA_radix8[46]));

asm volatile ("p.bitrev %[c], %[a], 8, 2\n"
             : [c] "+r" (tmp_result[47])
             : [a] "r"  (cplxbitrev_opA_radix8[47]));

asm volatile ("p.bitrev %[c], %[a], 26, 2\n"
             : [c] "+r" (tmp_result[48])
             : [a] "r"  (cplxbitrev_opA_radix8[48]));

asm volatile ("p.bitrev %[c], %[a], 14, 2\n"
             : [c] "+r" (tmp_result[49])
             : [a] "r"  (cplxbitrev_opA_radix8[49]));


#endif
