// fake pmsis.h
#include <pulp.h>
#include <stdint.h>
// fake data in L2, actually in L1!
#ifndef PI_L1
  #define PI_L1 __attribute__((section(".data_l1")))
#endif
#ifndef PI_L2
  #define PI_L2 __attribute__((section(".data_l1")))
#endif

