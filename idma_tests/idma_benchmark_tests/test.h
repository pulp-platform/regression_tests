// Copyright 2022 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
//Author: Andreas Kuster <kustera@ethz.ch>
//
//Description: Generated register defines for dma_frontend

#include "pulp.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#ifndef _DMA_FRONTEND_REG_DEFS_
#define _DMA_FRONTEND_REG_DEFS_

#ifdef __cplusplus
extern "C" {
#endif

#define DMA_CONF_DECOUPLE 0
#define DMA_CONF_DEBURST 0
#define DMA_CONF_SERIALIZE 0

#define CORE_SPACE 64*1024
#define TRANSFER_SIZE 5*1024
#define TRANSFERS_QUEUE 1

#if VERBOSE
    #define PRINTF(...) printf(__VA_ARGS__)
#else
    #define PRINTF(...)
#endif

#ifdef CYCLE_COUNT
    static inline void start_cycle_count () { perf_start(); }
    static inline void stop_cycle_count () { perf_stop(); }
    static inline void reset_cycle_count () { perf_reset(); }
    static inline void print_perf() { PRINTF ("Performances: \n"); perf_print_all(); }
#else
    static inline void start_cycle_count () { }
    static inline void stop_cycle_count () { }
    static inline void reset_cycle_count () { }
    static inline void print_perf() { }
#endif


#ifdef QUICK_MODE
    #define TRANSFERS 12
#else
    #define TRANSFERS NB_TRANSFERS
#endif

#ifdef __cplusplus
}  // extern "C"
#endif
#endif  // _DMA_FRONTEND_REG_DEFS_
