#include "pulp.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "mchan_def_1d.h"
#include "mchan_param_1d.h"

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
