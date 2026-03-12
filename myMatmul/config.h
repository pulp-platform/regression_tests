#ifndef _CONFIG_MATMUL_
#define _CONFIG_MATMUL_

#define DATA_LOCATION L1_DATA

#define THR 0.00001f

typedef float  MA_TYPE;
typedef float  MB_TYPE;
typedef float  OUT_TYPE;

void matMul(MA_TYPE * __restrict__ A, MB_TYPE * __restrict__ B, OUT_TYPE * __restrict__ C, int M, int N, int P);

#endif
