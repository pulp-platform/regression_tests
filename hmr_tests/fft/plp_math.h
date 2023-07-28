/** ==========================================================================
 * @file     plp_math.h
 * @brief    Public header file for PULP DSP Library
 * @version  V0
 * @date     16. May 2019
 * =========================================================================== */
/*
 * Copyright (C) 2019 ETH Zurich and University of Bologna. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 *  \mainpage PULP DSP Software Library
 * 
 *   Introduction
 *   ------------
 *
 *   This user manual describes the PULP DSP software library,
 *   a suite of common signal processing functions for use on PULP-based processors.
 *
 *   The library is divided into a number of functions each covering a specific category:
 *   - Basic math functions
 *   - Fast math functions
 *   - Complex math functions
 *   - Filters
 *   - Matrix functions
 *   - Transform functions
 *   - Motor control functions
 *   - Statistical functions
 *   - Support functions
 *   - Interpolation functions
 *
 *   ..
 *
 *
 *   The library has separate functions for operating on 8-bit integers, 16-bit integers,
 *   32-bit integer and 32-bit floating-point values.
 *
 *   The naming scheme of the functions follows the following pattern (for example plp_dot_prod_i32s):
 *
 *   <pre>
 *   < plp > _ < function name > _ < data type > < precision > < method > _ < isa extension >,
 *   </pre>
 *
 *   with
 *
 *   - data type = {f, i, q} respectively for floats, integers, fixed points
 *   - precision = {32, 16, 8} bits
 *   - method = {s, p} respectively meaning single core or parallel multicore implementation.
 *   - isa extension = rv32im, xpulpv2, etc. of which rv32im is the most general one.
 *
 *   ..
 *
 *
 *   If the user wants to use a parallel implementation, they can call the glue code functions with '_parallel'
 *   in the function name.
 *
 *
 *   The library is released under Apache v2.0 license. More details can be found in `LICENSE`.
 *
 */

/**
 * @defgroup groupMath Basic Math Functions
*/

/**
 * @defgroup groupCmplxMath Complex Math Functions
 */

/**
 * @defgroup groupFilters Filtering Functions
 */

/**
 * @defgroup groupMatrix Matrix Functions
 *
 * This set of functions provides basic matrix math operations.
 *
 */

/**
 * @defgroup groupTransforms Transform Functions
 */

/**
 * @defgroup groupStats Statistics Functions
 */

/**
 * @defgroup groupSupport Support Functions
 */

#ifndef __PLP_MATH_H__
#define __PLP_MATH_H__

#include "pulp.h"
#include "math.h"
// #include "rtos_hal.h"

// typedef float float32_t;

#define PLP_MATH_IBEX // previously called zero-riscy
//#define PLP_MATH_RISCY
#define PLP_MATH_LOOPUNROLL


/**
 * @brief Instance structure for the fixed-point CFFT/CIFFT function.
 * @param[in]   fftLen              length of the FFT
 * @param[in]   pTwiddle            points to the Twiddle factor table
 * @param[in]   pBitRevTable        points to the bit reversal table
 * @param[in]   bitRevTableLength   bit reversal table length
 */
typedef struct {
    uint16_t fftLen;             /*< length of the FFT. */
    const int16_t *pTwiddle;     /*< points to the Twiddle factor table. */
    const int16_t *pBitRevTable; /*< points to the bit reversal table. */
    uint16_t bitRevLength;       /*< bit reversal table length. */
} plp_cfft_instance_q16;

/**
 * @brief Instance structure for the parallel CFFT Q16
 * @param[in]       fft_struct          cfft_q16 struct
 * @param[in/out]   p1                  points to the complex data buffer of size <code>2*fftLen</code>.
 * Processing occurs in-place.
 * @param[in]       ifftFlag            flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1)
 * transform.
 * @param[in]       bitReverseFlag      flag that enables (bitReverseFlag=1) of disables
 * (bitReverseFlag=0) bit reversal of output.
 * @param[in]       deciPoint           decimal point for right shift
 * @param[in]       nPE                 number of cores to use
 */
typedef struct {
    plp_cfft_instance_q16 *S;
    int16_t *p1;
    uint8_t ifftFlag;
    uint8_t bitReverseFlag;
    uint32_t deciPoint;
    uint32_t nPE;
} plp_cfft_instance_q16_parallel;

/**
 * @brief Instance structure for the fixed-point CFFT/CIFFT function.
 * @param[in]   fftLen              length of the FFT
 * @param[in]   pTwiddle            points to the Twiddle factor table
 * @param[in]   pBitRevTable        points to the bit reversal table
 * @param[in]   bitRevTableLength   bit reversal table length
 */
typedef struct {
    uint16_t fftLen;             /*< length of the FFT. */
    const int32_t *pTwiddle;     /*< points to the Twiddle factor table. */
    const int16_t *pBitRevTable; /*< points to the bit reversal table. */
    uint16_t bitRevLength;       /*< bit reversal table length. */
} plp_cfft_instance_q32;

/**
 * @brief Instance structure for the parallel CFFT Q16
 * @param[in]       fft_struct          cfft_q16 struct
 * @param[in/out]   p1                  points to the complex data buffer of size <code>2*fftLen</code>.
 * Processing occurs in-place.
 * @param[in]       ifftFlag            flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1)
 * transform.
 * @param[in]       bitReverseFlag      flag that enables (bitReverseFlag=1) of disables
 * (bitReverseFlag=0) bit reversal of output.
 * @param[in]       deciPoint           decimal point for right shift
 * @param[in]       nPE                 number of cores to use
 */
typedef struct {
    plp_cfft_instance_q32 *S;
    int32_t *p1;
    uint8_t ifftFlag;
    uint8_t bitReverseFlag;
    uint32_t fracBits;
    uint32_t nPE;
} plp_cfft_instance_q32_parallel;

void plp_bitreversal_16s_rv32im(uint16_t *pSrc,
                                const uint16_t bitRevLen,
                                const uint16_t *pBitRevTab);

/**
  @brief      In-place 16 bit reversal function for XPULPV2
  @param[in,out] pSrc        points to in-place buffer of unknown 16-bit data type
  @param[in]  bitRevLen   bit reversal table length
  @param[in]  pBitRevTab  points to bit reversal table
  @return     none
*/

void plp_bitreversal_16s_xpulpv2(uint16_t *pSrc,
                                 const uint16_t bitRevLen,
                                 const uint16_t *pBitRevTab);

/**
  @brief         In-place 16 bit reversal function.
  @param[in,out] pSrc        points to in-place buffer of unknown 16-bit data type
  @param[in]     bitRevLen   bit reversal table length
  @param[in]     pBitRevTab  points to bit reversal table
  @param[in]     nPE         number of cores
  @return        none
*/

void plp_bitreversal_16p_xpulpv2(uint16_t *pSrc,
                                 const uint16_t bitRevLen,
                                 const uint16_t *pBitRevTab,
                                 uint32_t nPE);

/**
 * @brief      Glue code for quantized 16 bit complex fast fourier transform
 *
 * Fixed point units input -> output dependent on length:
 * len=16:    Q1.15 -> Q5.11
 * len=32:    Q1.15 -> Q6.10
 * len=64:    Q1.15 -> Q7.9
 * len=128:   Q1.15 -> Q8.8
 * len=256:   Q1.15 -> Q9.7
 * len=512:   Q1.15 -> Q10.6
 * len=1024:  Q1.15 -> Q11.5
 * len=2048:  Q1.15 -> Q12.4
 * len=4096:  Q1.15 -> Q13.3
 *
 * @param[in]  S               points to an instance of the 16bit quantized CFFT structure
 * @param[in,out] p1              points to the complex data buffer of size <code>2*fftLen</code>.
 * Processing occurs in-place.
 * @param[in]  ifftFlag        flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1)
 * transform.
 * @param[in]  bitReverseFlag  flag that enables (bitReverseFlag=1) of disables
 * (bitReverseFlag=0) bit reversal of output.
 * @param[in]  deciPoint       decimal point for right shift
 */

void plp_cfft_q16(const plp_cfft_instance_q16 *S,
                  int16_t *p1,
                  uint8_t ifftFlag,
                  uint8_t bitReverseFlag,
                  uint32_t deciPoint);

/**
 * @brief      Glue code for quantized 16 bit complex fast fourier transform
 *
 * Fixed point units input -> output dependent on length:
 * len=16:    Q1.15 -> Q5.11
 * len=32:    Q1.15 -> Q6.10
 * len=64:    Q1.15 -> Q7.9
 * len=128:   Q1.15 -> Q8.8
 * len=256:   Q1.15 -> Q9.7
 * len=512:   Q1.15 -> Q10.6
 * len=1024:  Q1.15 -> Q11.5
 * len=2048:  Q1.15 -> Q12.4
 * len=4096:  Q1.15 -> Q13.3
 *
 * @param[in]  S               points to an instance of the 16bit quantized CFFT structure
 * @param[in,out] p1           points to the complex data buffer of size <code>2*fftLen</code>.
 * Processing occurs in-place.
 * @param[in]  ifftFlag        flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1)
 * transform.
 * @param[in]  bitReverseFlag  flag that enables (bitReverseFlag=1) of disables
 * (bitReverseFlag=0) bit reversal of output.
 * @param[in]  deciPoint       decimal point for right shift
 * @param[in]  nPE             Number of cores to use
 */

void plp_cfft_q16_parallel(const plp_cfft_instance_q16 *S,
                           int16_t *p1,
                           uint8_t ifftFlag,
                           uint8_t bitReverseFlag,
                           uint32_t deciPoint,
                           uint32_t nPE);

/**
 * @brief      Quantized 16 bit complex fast fourier transform for RV32IM
 * @param[in]  S               points to an instance of the 16bit quantized CFFT structure
 * @param[in,out] p1              points to the complex data buffer of size <code>2*fftLen</code>.
 * Processing occurs in-place.
 * @param[in]  ifftFlag        flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1)
 * transform.
 * @param[in]  bitReverseFlag  flag that enables (bitReverseFlag=1) of disables
 * (bitReverseFlag=0) bit reversal of output.
 * @param[in]  deciPoint       decimal point for right shift
 */

void plp_cfft_q16s_rv32im(const plp_cfft_instance_q16 *S,
                          int16_t *p1,
                          uint8_t ifftFlag,
                          uint8_t bitReverseFlag,
                          uint32_t deciPoint);

/**
 * @brief      Quantized 16 bit complex fast fourier transform for XPULPV2
 * @param[in]  S               points to an instance of the 16bit quantized CFFT structure
 * @param[in,out] p1              points to the complex data buffer of size <code>2*fftLen</code>.
 * Processing occurs in-place.
 * @param[in]  ifftFlag        flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1)
 * transform.
 * @param[in]  bitReverseFlag  flag that enables (bitReverseFlag=1) of disables
 * (bitReverseFlag=0) bit reversal of output.
 * @param[in]  deciPoint       decimal point for right shift
 */

void plp_cfft_q16s_xpulpv2(const plp_cfft_instance_q16 *S,
                           int16_t *p1,
                           uint8_t ifftFlag,
                           uint8_t bitReverseFlag,
                           uint32_t deciPoint);

/**
 * @brief      Parallel quantized 16 bit complex fast fourier transform for XPULPV2
 * @param[in]   args    points to the plp_cfft_instance_q16_parallel
 */

void plp_cfft_q16p_xpulpv2(void *args);

/**
  @brief      In-place 32 bit reversal function for RV32IM
  @param[in,out] pSrc        points to in-place buffer of unknown 32-bit data type
  @param[in]  bitRevLen   bit reversal table length
  @param[in]  pBitRevTab  points to bit reversal table
  @return     none
*/

void plp_bitreversal_32s_rv32im(uint32_t *pSrc, const uint16_t bitRevLen, const uint16_t *pBitRevTab);

/**
  @brief      In-place 32 bit reversal function for XPULPV2
  @param[in,out] pSrc        points to in-place buffer of unknown 32-bit data type
  @param[in]  bitRevLen   bit reversal table length
  @param[in]  pBitRevTab  points to bit reversal table
  @return     none
*/

void plp_bitreversal_32s_xpulpv2(uint32_t *pSrc, const uint16_t bitRevLen, const uint16_t *pBitRevTab);

/**
  @brief      In-place 32 bit reversal function for XPULPV2
  @param[in,out] pSrc        points to in-place buffer of unknown 32-bit data type
  @param[in]  bitRevLen   bit reversal table length
  @param[in]  pBitRevTab  points to bit reversal table
  @param[in]     nPE         number of cores
  @return     none
*/

void plp_bitreversal_32p_xpulpv2(uint32_t *pSrc, const uint16_t bitRevLen, const uint16_t *pBitRevTab, uint32_t nPE);

/**
 * @brief      Glue code for quantized 32-bit complex fast fourier transform
 * 
 * Fixed point units input -> output dependent on length:
 * len=16:    Q1.31 -> Q5.27
 * len=32:    Q1.31 -> Q6.26
 * len=64:    Q1.31 -> Q7.25
 * len=128:   Q1.31 -> Q8.24
 * len=256:   Q1.31 -> Q9.23
 * len=512:   Q1.31 -> Q10.22
 * len=1024:  Q1.31 -> Q11.21
 * len=2048:  Q1.31 -> Q12.20
 * len=4096:  Q1.31 -> Q13.19
 *
 * @param[in]  S               points to an instance of the 32bit quantized CFFT structure
 * @param      p1              points to the complex data buffer of size <code>2*fftLen</code>. Processing occurs in-place.
 * @param[in]  ifftFlag        flag that selects forwart (ifftFlag=0) or inverse (ifftFlag=1)
 * @param[in]  bitReverseFlag  flag that enables (bitReverseFlag=1) of disables
 * (bitReverseFlag=0) bit reversal of output.
 * @param[in]  fracBits        decimal point for right shift (input format Q(32-fracBits).fracBits)
 */

void plp_cfft_q32(const plp_cfft_instance_q32 *S,
                      int32_t *p1,
                      uint8_t ifftFlag,
                      uint8_t bitReverseFlag,
                      uint32_t fracBits);

/**
 * @brief      Quantized 32-bit complex fast fourier transform for XPULPV2
 *
 * @param[in]  S               points to an instance of the 32bit quantized CFFT structure
 * @param      p1              points to the complex data buffer of size <code>2*fftLen</code>. Processing occurs in-place.
 * @param[in]  ifftFlag        flag that selects forwart (ifftFlag=0) or inverse (ifftFlag=1)
 * @param[in]  bitReverseFlag  flag that enables (bitReverseFlag=1) of disables (bitReverseFlag=0) bit reversal of output.
 * @param[in]  fracBits        decimal point for right shift (input format Q(32-fracBits).fracBits)
 * @param[in]  nPE             Number of cores to use
 */

void plp_cfft_q32_parallel( const plp_cfft_instance_q32 *S,
                            int32_t *p1,
                            uint8_t ifftFlag,
                            uint8_t bitReverseFlag,
                            uint32_t fracBits,
                            uint32_t nPE );

/**
 * @brief      Quantized 32-bit complex fast fourier transform for RV32IM
 *
 * @param[in]  S               points to an instance of the 32bit quantized CFFT structure
 * @param      p1              points to the complex data buffer of size <code>2*fftLen</code>. Processing occurs in-place.
 * @param[in]  ifftFlag        flag that selects forwart (ifftFlag=0) or inverse (ifftFlag=1)
 * @param[in]  bitReverseFlag  flag that enables (bitReverseFlag=1) of disables
 * (bitReverseFlag=0) bit reversal of output.
 * @param[in]  fracBits        decimal point for right shift (input format Q(32-fracBits).fracBits)
 */

void plp_cfft_q32s_rv32im(const plp_cfft_instance_q32 *S,
                      int32_t *p1,
                      uint8_t ifftFlag,
                      uint8_t bitReverseFlag,
                      uint32_t fracBits);

/**
 * @brief      Quantized 32-bit complex fast fourier transform for XPULPV2
 *
 * @param[in]  S               points to an instance of the 32bit quantized CFFT structure
 * @param      p1              points to the complex data buffer of size <code>2*fftLen</code>. Processing occurs in-place.
 * @param[in]  ifftFlag        flag that selects forwart (ifftFlag=0) or inverse (ifftFlag=1)
 * @param[in]  bitReverseFlag  flag that enables (bitReverseFlag=1) of disables
 * (bitReverseFlag=0) bit reversal of output.
 * @param[in]  fracBits        decimal point for right shift (input format Q(32-fracBits).fracBits)
 */

void plp_cfft_q32s_xpulpv2(const plp_cfft_instance_q32 *S,
                      int32_t *p1,
                      uint8_t ifftFlag,
                      uint8_t bitReverseFlag,
                      uint32_t fracBits);

/**
 * @brief      Parallel quantized 32 bit complex fast fourier transform for XPULPV2
 * @param[in]   args    points to the plp_cfft_instance_q32_parallel
 */

void plp_cfft_q32p_xpulpv2(void *args);

#endif // __PLP_MATH_H__