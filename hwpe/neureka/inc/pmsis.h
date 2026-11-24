// pulp-nnx includes <pmsis.h>. pulp-runtime has none, so stub it there; under
// pulp-sdk defer to the real one, which -Iinc would otherwise shadow.
#ifdef PULP_COMPAT
#include_next <pmsis.h>
#else
#include <pulp.h>
#include <stdint.h>
#endif

// This test deliberately keeps its "L2" buffers in L1.
#undef PI_L1
#define PI_L1 __attribute__((section(".data_l1")))
#undef PI_L2
#define PI_L2 __attribute__((section(".data_l1")))
