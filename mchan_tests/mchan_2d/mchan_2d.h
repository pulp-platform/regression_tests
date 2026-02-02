/* 
 * Copyright (C) 2026 ETH Zurich, University of Bologna and Fondazione Chips-IT
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

#include "pulp.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "mchan_def_2d.h"
#include "mchan_param_2d.h"

#ifdef VERBOSE
    #define PRINTF(...) printf(__VA_ARGS__)
#else
    #define PRINTF(...)
#endif

#define CORE_SPACE 2048

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
