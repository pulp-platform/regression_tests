#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include <pmsis.h>

#define OUTPUT_SIZE (335)
extern uint8_t output[OUTPUT_SIZE];

#define GOLDEN_OUTPUT_SIZE (335)
extern uint8_t golden_output[GOLDEN_OUTPUT_SIZE];

int check_output();

#endif  // __OUTPUT_H__
