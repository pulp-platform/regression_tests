#include "config.h"
#include "pulp.h"


void __attribute__ ((noinline)) matMul(MA_TYPE * __restrict__ A, MB_TYPE * __restrict__ B, OUT_TYPE * __restrict__ C, int M, int N, int P) {

  int blockSize = (M+NUM_CORES-1)/NUM_CORES;
  int start = get_core_id()*blockSize;
  int end = start + blockSize < M? start + blockSize : M;
  
  for (int i = start; i < end; i++) {
    for (int j = 0; j < P; j++) {
      OUT_TYPE temp = 0;

      //Manual unrolling
      for (int k = 0; k < (N & 0xfffffffe); k+=2) {
        temp += (OUT_TYPE)(A[i*N+k]   * B[k*P+j]);
        temp += (OUT_TYPE)(A[i*N+k+1] * B[k*P+j+P]);

      }
         C[i*P+j] = (OUT_TYPE)(temp);
    }
  }
      // Leftover on N

      if (N & 0x00000001) 
      {
        for (int i=start; i<end; i++) 
        {
          for (int j=0; j<P; j++) 
          {
            C[i*P+j] += (OUT_TYPE)(A[i*N+N-1] * B[(N-1)*P+j]);
          }
        }
      } 

  #if NUM_CORES > 1
  synch_barrier();
  #endif
}
