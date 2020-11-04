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
/******************************************************************************
 *                                                                            *
 *             Multitherman Lab @ DEI - University of Bologna                 *
 *                     Viale Risorgimento 2 40136                             *
 *                     Bologna - phone 0512092759                             *
 *                                                                            *
 * Engineer:       Francesco Conti - f.conti@unibo.it                         *
 *                                                                            *
 * Project:        CConvNet                                                   *
 * File:           conv16.h                                                   *
 * Description:    16-bit fixed point convolution test                        *
 *                                                                            *
 ******************************************************************************/

#ifndef _CONV16_H
#define _CONV16_H

// uncomment if doing test with SPI (disables printf's)
// #define PULP_SPI

// fractionary bits
#define QF 13

// uncomment if checking errors in detail
// #define CHECK_ERROR

// uncomment if performing checks at all
#define CHECK_CHECKSUM

#define IMPRECISE_ASM5

#define FIXED_MUL(a,b) ((a*b) >> QF);

#define IH 32
#define IW 32
#define FH 5
#define FW 5
#define OH (IH-FH+1)
#define OW (IW-FW+1)

// right checksum
#define RIGHT_CHECKSUM 0x009da8b0

#define FIXED_MUL_ASM(W_ptr,x_ptr,conv) \
__asm__ volatile \
( \
   "l.lhs  r28,0x0(%0);    " \
   "l.addi %0,%0,0x4;      " \
   "l.addi %1,%1,0xFFFC;   " \
   "l.mul  r28,r28,r29;    " \
   "l.srli r28,r28,0xD;    " \
   "l.add  %2,%2,r28;      " \
   : "=r"(W_ptr), "=r"(x_ptr), "=&r"(conv) \
   : "r"(W_ptr), "r"(x_ptr)                \
   : "r28", "r29", "cc"                    \
)

#define FIXED_MUL_ASM5_IMPRECISE(W_ptr,x_ptr,conv) \
__asm__ volatile \
( \
   "l.ori  r25,r0,0xffff;  " \
   "l.ori  r26,r0,16;      " \
   "l.andi r27,r27,0x0000; " \
   "l.lwz  r28,0x0000(%0); " \
   "l.lwz  r29,0x0000(%1); " \
   "l.ror  r30,r28,r26;    " \
   "l.ror  r31,r29,r26;    " \
   "l.and  r30,r30,r25;    " \
   "l.and  r31,r31,r25;    " \
   "l.mul  r30,r30,r31;    " \
   "l.add  r27,r27,r30;    " \
   "l.and  r28,r28,r25;    " \
   "l.and  r29,r29,r25;    " \
   "l.mul  r28,r28,r29;    " \
   "l.add  r27,r27,r28;    " \
   "l.lwz  r28,0x0004(%0); " \
   "l.lwz  r29,0xfffc(%1); " \
   "l.ror  r30,r28,r26;    " \
   "l.ror  r31,r29,r26;    " \
   "l.and  r30,r30,r25;    " \
   "l.and  r31,r31,r25;    " \
   "l.mul  r30,r30,r31;    " \
   "l.add  r27,r27,r30;    " \
   "l.and  r28,r28,r25;    " \
   "l.and  r29,r29,r25;    " \
   "l.mul  r28,r28,r29;    " \
   "l.add  r27,r27,r28;    " \
   "l.lwz  r28,0x0008(%0); " \
   "l.lwz  r29,0xfff8(%1); " \
   "l.ror  r31,r29,r26;    " \
   "l.and  r28,r28,r25;    " \
   "l.and  r31,r31,r25;    " \
   "l.mul  r28,r28,r31;    " \
   "l.add  r27,r27,r28;    " \
   "l.srli r27,r27,0xD;    " \
   "l.add  %2,%2,r27;      " \
   : "=r"(W_ptr), "=r"(x_ptr), "=&r"(conv) \
   : "r"(W_ptr), "r"(x_ptr), "r"(conv)     \
   : "r27", "r28", "r29", "cc"             \
)

#define FIXED_MUL_ASM5_PRECISE(W_ptr,x_ptr,conv) \
__asm__ volatile \
( \
   "l.lhs  r28,0x0000(%0); " \
   "l.lhs  r29,0x0000(%1); " \
   "l.mul  r28,r28,r29;    " \
   "l.srli r28,r28,0xD;    " \
   "l.add  %2,%2,r28;      " \
   "l.lhs  r28,0x0002(%0); " \
   "l.lhs  r29,0xfffe(%1); " \
   "l.mul  r28,r28,r29;    " \
   "l.srli r28,r28,0xD;    " \
   "l.add  %2,%2,r28;      " \
   "l.lhs  r28,0x0004(%0); " \
   "l.lhs  r29,0xfffc(%1); " \
   "l.mul  r28,r28,r29;    " \
   "l.srli r28,r28,0xD;    " \
   "l.add  %2,%2,r28;      " \
   "l.lhs  r28,0x0006(%0); " \
   "l.lhs  r29,0xfffa(%1); " \
   "l.mul  r28,r28,r29;    " \
   "l.srli r28,r28,0xD;    " \
   "l.add  %2,%2,r28;      " \
   "l.lhs  r28,0x0008(%0); " \
   "l.lhs  r29,0xfff8(%1); " \
   "l.mul  r28,r28,r29;    " \
   "l.srli r28,r28,0xD;    " \
   "l.add  %2,%2,r28;      " \
   : "=r"(W_ptr), "=r"(x_ptr), "=&r"(conv) \
   : "r"(W_ptr), "r"(x_ptr)                \
   : "r27", "r28", "r29", "cc"             \
)

// #define FIXED_MUL_ASM25_PRECISE(W_ptr,x_ptr,conv) \
// __asm__ volatile \
// ( \
//    "l.lwz  r28,0x0000(%0); " \
//    "l.lwz  r29,0x0000(%1); " \
//    "l.mul  r28,r28,r29;    " \
//    "l.srli r28,r28,0xD;    " \
//    "l.add  %2,%2,r28;      " \
//    "l.lwz  r28,0x0004(%0); " \
//    "l.lwz  r29,0xfffc(%1); " \
//    "l.mul  r28,r28,r29;    " \
//    "l.srli r28,r28,0xD;    " \
//    "l.add  %2,%2,r28;      " \
//    "l.lwz  r28,0x0008(%0); " \
//    "l.lwz  r29,0xfff8(%1); " \
//    "l.mul  r28,r28,r29;    " \
//    "l.srli r28,r28,0xD;    " \
//    "l.add  %2,%2,r28;      " \
//    "l.lwz  r28,0x000c(%0); " \
//    "l.lwz  r29,0xfff4(%1); " \
//    "l.mul  r28,r28,r29;    " \
//    "l.srli r28,r28,0xD;    " \
//    "l.add  %2,%2,r28;      " \
//    "l.lwz  r28,0x0010(%0); " \
//    "l.lwz  r29,0xfff0(%1); " \
//    "l.mul  r28,r28,r29;    " \
//    "l.srli r28,r28,0xD;    " \
//    "l.add  %2,%2,r28;      " \
//    \
//    "l.slli %1,r28,0x2;    " \
//    \
//    "l.lwz  r28,0x0014(%0); " \
//    "l.lwz  r29,0x0000(%1); " \
//    "l.mul  r28,r28,r29;    " \
//    "l.srli r28,r28,0xD;    " \
//    "l.add  %2,%2,r28;      " \
//    "l.lwz  r28,0x0018(%0); " \
//    "l.lwz  r29,0xfffc(%1); " \
//    "l.mul  r28,r28,r29;    " \
//    "l.srli r28,r28,0xD;    " \
//    "l.add  %2,%2,r28;      " \
//    "l.lwz  r28,0x001c(%0); " \
//    "l.lwz  r29,0xfff8(%1); " \
//    "l.mul  r28,r28,r29;    " \
//    "l.srli r28,r28,0xD;    " \
//    "l.add  %2,%2,r28;      " \
//    "l.lwz  r28,0x0020(%0); " \
//    "l.lwz  r29,0xfff4(%1); " \
//    "l.mul  r28,r28,r29;    " \
//    "l.srli r28,r28,0xD;    " \
//    "l.add  %2,%2,r28;      " \
//    "l.lwz  r28,0x0024(%0); " \
//    "l.lwz  r29,0xfff0(%1); " \
//    "l.mul  r28,r28,r29;    " \
//    "l.srli r28,r28,0xD;    " \
//    "l.add  %2,%2,r28;      " \
//    // WIP
//    : "=r"(W_ptr), "=r"(x_ptr), "=&r"(conv)   \
//    : "r"(W_ptr), "r"(x_ptr), "r"(w), "r"(fw) \
//    : "r27", "r28", "r29", "cc"               \
// )

#define XPTR_UPDATE(x_ptr,w,fw) \
__asm__ volatile \
( \
   "l.sub  r28,%1,%2;      " \
   "l.slli r28,r28,0x2;    " \
   "l.sub  %0,%0,r28;      " \
   : "=&r"(x_ptr) \
   : "r"(x_ptr), "r"(w), "r"(fw) \
   : "r28", "cc" \
)

int test_singlethread(void (*test)(int16_t *, int16_t *, int16_t *, int, int, int, int, int, int, int, int, int), char *str);
int test_multithread(void (*test)(int16_t *, int16_t *, int16_t *, int, int, int, int, int, int, int, int, int), char *str);

void conv16_gold(int16_t *__restrict__ W, int16_t *__restrict__ x, int16_t *__restrict__ y, int h, int w, int fh, int fw, int oh, int ow, int nif, int a, int b);
void conv16_asm_mul(int16_t *__restrict__ W, int16_t *__restrict__ x, int16_t *__restrict__ y, int h, int w, int fh, int fw, int oh, int ow, int nif, int a, int b);
// void conv16_asm_mac(int16_t *__restrict__ W, int16_t *__restrict__ x, int16_t *__restrict__ y, int h, int w, int fh, int fw, int oh, int ow, int nif, int a, int b);
void conv16_asm_mul_unrolled_5x5(int16_t *__restrict__ W, int16_t *__restrict__ x, int16_t *__restrict__ y, int h, int w, int fh, int fw, int oh, int ow, int nif, int a, int b);
void conv16_unrolled_5x5(int16_t *__restrict__ W, int16_t *__restrict__ x, int16_t *__restrict__ y, int h, int w, int fh, int fw, int oh, int ow, int nif, int a, int b);
void conv16_unrolled_ptr_5x5(int16_t *__restrict__ W, int16_t *__restrict__ x, int16_t *__restrict__ y, int h, int w, int fh, int fw, int oh, int ow, int nif, int a, int b);
// void conv16_gold_four_finest(int16_t *__restrict__ W, int16_t *__restrict__ x, int16_t *__restrict__ y, int h, int w, int fh, int fw, int oh, int ow, int nif, int a, int b, int32_t *shared_conv);
// void conv16_gold_four_fine(int16_t *__restrict__ W, int16_t *__restrict__ x, int16_t *__restrict__ y, int h, int w, int fh, int fw, int oh, int ow, int nif, int a, int b);
void conv16_gold_four_coarse(int16_t *__restrict__ W, int16_t *__restrict__ x, int16_t *__restrict__ y, int h, int w, int fh, int fw, int oh, int ow, int nif, int a, int b);
void conv16_unrolled_5x5_four_coarse(int16_t *__restrict__ W, int16_t *__restrict__ x, int16_t *__restrict__ y, int h, int w, int fh, int fw, int oh, int ow, int nif, int a, int b);
void conv16_unrolled_ptr_5x5_four_coarse(int16_t *__restrict__ W, int16_t *__restrict__ x, int16_t *__restrict__ y, int h, int w, int fh, int fw, int oh, int ow, int nif, int a, int b);
void conv16_gold_four_coarsest(int16_t *__restrict__ W, int16_t *__restrict__ x, int16_t *__restrict__ y, int h, int w, int fh, int fw, int oh, int ow, int nif, int a, int b);
void conv16_unrolled_5x5_four_coarsest(int16_t *__restrict__ W, int16_t *__restrict__ x, int16_t *__restrict__ y, int h, int w, int fh, int fw, int oh, int ow, int nif, int a, int b);
void conv16_unrolled_ptr_5x5_four_coarsest(int16_t *__restrict__ W, int16_t *__restrict__ x, int16_t *__restrict__ y, int h, int w, int fh, int fw, int oh, int ow, int nif, int a, int b);
void conv16_asm_mul_unrolled_5x5_four_coarsest(int16_t *__restrict__ W, int16_t *__restrict__ x, int16_t *__restrict__ y, int h, int w, int fh, int fw, int oh, int ow, int nif, int a, int b);

void load();
int check(int16_t *y);
int checksum(int16_t *y);

int16_t correct_yout[OH*OW] = {
   0x0352,
   0x036c,
   0x0386,
   0x03a0,
   0x03ba,
   0x03d4,
   0x03ee,
   0x0408,
   0x0422,
   0x043c,
   0x0456,
   0x0470,
   0x04ee,
   0x0508,
   0x0522,
   0x053c,
   0x0556,
   0x0570,
   0x058a,
   0x05a4,
   0x05be,
   0x05d8,
   0x05f2,
   0x060c,
   0x068a,
   0x06a4,
   0x06be,
   0x06d8,
   0x06f2,
   0x070c,
   0x0726,
   0x0740,
   0x075a,
   0x0774,
   0x078e,
   0x07a8,
   0x0826,
   0x0840,
   0x085a,
   0x0874,
   0x088e,
   0x08a8,
   0x08c2,
   0x08dc,
   0x08f6,
   0x0910,
   0x092a,
   0x0944,
   0x09c2,
   0x09dc,
   0x09f6,
   0x0a10,
   0x0a2a,
   0x0a44,
   0x0a5e,
   0x0a78,
   0x0a92,
   0x0aac,
   0x0ac6,
   0x0ae0,
   0x0b5e,
   0x0b78,
   0x0b92,
   0x0bac,
   0x0bc6,
   0x0be0,
   0x0bfa,
   0x0c14,
   0x0c2e,
   0x0c48,
   0x0c62,
   0x0c7c,
   0x0cfa,
   0x0d14,
   0x0d2e,
   0x0d48,
   0x0d62,
   0x0d7c,
   0x0d96,
   0x0db0,
   0x0dca,
   0x0de4,
   0x0dfe,
   0x0e18,
   0x0e96,
   0x0eb0,
   0x0eca,
   0x0ee4,
   0x0efe,
   0x0f18,
   0x0f32,
   0x0f4c,
   0x0f66,
   0x0f80,
   0x0f9a,
   0x0fb4,
   0x1032,
   0x104c,
   0x1066,
   0x1080,
   0x109a,
   0x10b4,
   0x10ce,
   0x10e8,
   0x1102,
   0x111c,
   0x1136,
   0x1150,
   0x11ce,
   0x11e8,
   0x1202,
   0x121c,
   0x1236,
   0x1250,
   0x126a,
   0x1284,
   0x129e,
   0x12b8,
   0x12d2,
   0x12ec,
   0x136a,
   0x1384,
   0x139e,
   0x13b8,
   0x13d2,
   0x13ec,
   0x1406,
   0x1420,
   0x143a,
   0x1454,
   0x146e,
   0x1488,
   0x1506,
   0x1520,
   0x153a,
   0x1554,
   0x156e,
   0x1588,
   0x15a2,
   0x15bc,
   0x15d6,
   0x15f0,
   0x160a,
   0x1624,
};

#endif
