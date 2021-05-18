#include <stdio.h>
#include "pulp.h"

//#define USE_CLUSTER

#define MAESTRO_REG_0 0x

#define NUM_CORES 8
#define SIZE 4

//#define PARALLEL
//#define PULP_COUNTERS

L1_DATA int32_t matA[SIZE*SIZE] __attribute__ ((aligned (4)));
L1_DATA int32_t matB[SIZE*SIZE] __attribute__ ((aligned (4)));
L1_DATA int32_t matC[SIZE*SIZE] __attribute__ ((aligned (4)));

int matmul () {
  
  int32_t *A = matA;
  int32_t *B = matB;
  int32_t *C = matC;
  uint32_t M = SIZE;
  uint32_t N = SIZE;
  if(get_core_id() == 0) {
    
    for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
        A[i*SIZE+j] = j+1;
        B[i*SIZE+j] = i+1;
        C[i*SIZE+j] = 0;
      }
    }
  }



#ifdef PARALLEL
  synch_barrier();
  int blockSize = (SIZE+NUM_CORES-1) / NUM_CORES;
  int start = get_core_id()*blockSize;
  for (int i=start; i < start+blockSize; i++) {
#else
  if(get_core_id() == 0) {
    for (int i = 0; i < N; i++) {
#endif
    for (int j = 0; j < M; j++) {
      C[i*N+j] = 0;
      for (int k = 0; k < N; k+=1) {
        C[i*N+j] += A[i*N+k] * B[k*N+j];
      }
    }
  }
  }
#ifdef PARALLEL
    synch_barrier();
#endif

  return 0;
}
  
int main()
{

  #ifdef USE_CLUSTER
  if (rt_cluster_id() != 0){
    return bench_cluster_forward(0);
  }
  #endif

  uint8_t event;
  uint32_t counter_num;
  uint32_t val;
  int error = 0;
  counter_num = 1 << 3 ;
  #ifndef PULP_COUNTERS
  //enabling minstr
  asm volatile("csrc 0x320, %0" : : "r"(1<<2));
  //enabling mcycle
  asm volatile("csrc 0x320, %0" : : "r"(1));
  #endif
  
  for(int i=0; i<16; i++)
    {
       // disable reg 3
       asm volatile("csrs 0x320, %0" : : "r"(counter_num));
       // counter reset 
       asm volatile("csrw 0xB03, x0");
       // enable reg 3
       asm volatile("csrc 0x320, %0" : : "r"(counter_num));
       
       event = (1 << i);
       
       // register 3 is the only one implemented, select the event
       asm volatile("csrw 0x323, %0" : : "r"(event));

       error = matmul();

       // disable perf count for reporting
       asm volatile("csrs 0x320, %0" : : "r"(counter_num));
       #ifndef PULP_COUNTERS

       // read the perf
       asm volatile("csrr %0, 0xB00" : "=r"(val));

       printf("Num cycle cumulative %d\n", val);
       
       asm volatile("csrr %0, 0xB02" : "=r"(val));

       printf("Num isntr cumulative: %d\n", val);
       #endif
       
       asm volatile("csrr %0, 0xB03" : "=r"(val));

       printf("Num PERF event %d: %d\n", i, val);
      
    }
  
  return 0;
}
