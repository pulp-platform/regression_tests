#include "pulp.h"
void __attribute__ ((noinline)) matMul(float * pSrcA, float * pSrcB, float * pDstC, int M, int N, int O) {


    int i; // loop counter for M
    int j; // loop counter for N
    int k; // loop counter for O

    int core_id = get_core_id();

    if(M<=0 || N<=0 || O<=0) return;

    for (k = core_id; k < O/2; k += NUM_CORES) {
    // for (k = core_id; k < O/2; k += get_core_num()) {

        for (i = 0; i < M/2; i++) {
            // printf("i = %d\n",i);
            float sum00 = 0;
            float sum01 = 0;
            float sum10 = 0;
            float sum11 = 0;

#ifdef UNROLL_INNER_LOOP
            for (j = 0; j < N/2; j++) {
                float AVal0 = pSrcA[i * 2 * N + (j*2)];
                float AVal1 = pSrcA[i * 2 * N + N + (j*2)];
                float BVal0 = pSrcB[(j*2) * O + (k * 2)];
                float BVal1 = pSrcB[(j*2) * O + (k * 2 + 1)];

                float AVal2 = pSrcA[i * 2 * N + (j*2+1)];
                float AVal3 = pSrcA[i * 2 * N + N + (j*2+1)];
                float BVal2 = pSrcB[(j*2+1) * O + (k * 2)];
                float BVal3 = pSrcB[(j*2+1) * O + (k * 2 + 1)];

                sum00 = sum00 + AVal0 * BVal0 + AVal2 * BVal2;
                sum01 = sum01 + AVal0 * BVal1 + AVal2 * BVal3;
                sum10 = sum10 + AVal1 * BVal0 + AVal3 * BVal2;
                sum11 = sum11 + AVal1 * BVal1 + AVal3 * BVal3;	        	
            }
	    
#else	   
	     
            for (j = 0; j < N; j++) {
                // printf("j = %d\n",j);

                float AVal0 = pSrcA[i * 2 * N + (j)];
                float AVal1 = pSrcA[i * 2 * N + N + (j)];

                float BVal0 = pSrcB[j * O + (k * 2)];
                float BVal1 = pSrcB[j * O + (k * 2 + 1)];

                sum00 = sum00 + (float) AVal0 * (float) BVal0;
                sum01 = sum01 + (float) AVal0 * (float) BVal1;
                sum10 = sum10 + (float) AVal1 * (float) BVal0;
                sum11 = sum11 + (float) AVal1 * (float) BVal1;
            }
#endif	    
        

        // printf("i = %d\n",i);
        // printf("O = %d\n",O);
        // printf("k = %d\n",k);
        // printf("index = %d\n",((i * 2) * O + k * 2));
        // printf("index2 = %d\n",((i * 2 + 1) * O + k * 2));
        
        pDstC[(i * 2) * O + k * 2] = sum00;
        pDstC[(i * 2) * O + k * 2 + 1] = sum01;
	    pDstC[(i * 2 + 1) * O + k * 2] = sum10;
        pDstC[(i * 2 + 1) * O + k * 2 + 1] = sum11;
        // printf("ITER DONE\n");
        } // i 
    } // k
    // clean up code
    i = i * 2;
#ifdef UNROLL_INNER_LOOP    
    j = j * 2;
#endif
    k = k * 2;
    // check if every index is nicely finished
    // printf("main loop done\n");
    if (i == M && j == N && k >= O) {

    } else {
        uint32_t iEnd = i;
        uint32_t jEnd = j;
        uint32_t kEnd = k >= O ? O : k;

        // clean up for j
        if (jEnd != N) {
            for (i = 0; i < iEnd; i++) {
                for (k = 0; k < kEnd; k += NUM_CORES) {
                    int32_t sum = 0;
                    for (j = jEnd; j < N; j++) {
                        sum += sum + pSrcA[i * N + j] * pSrcB[j * O + k];
                    }
                    pDstC[i * O + k] += sum;
                }
            }
        }

        // clean up for i
        if (iEnd != M) {
            for (k = core_id; k < kEnd; k += NUM_CORES) {
                for (i = iEnd; i < M; i++) {
                    int32_t sum = 0;
                    for (j = 0; j < N; j++) {
                        sum = sum + pSrcA[i * N + j] * pSrcB[j * O + k];
                    }
                    pDstC[i * O + k] = sum;
                }
            }
        }

        // clean up for k
        for (k = kEnd; k < O; k += NUM_CORES) {
            for (i = 0; i < M; i++) {
                int32_t sum = 0;
                for (j = 0; j < N; j++) {
                    sum = sum + pSrcA[i * N + j] * pSrcB[j * O + k];
                }
                pDstC[i * O + k] = sum;
            }
        }
    }

    synch_barrier(0);

}

// void __attribute__ ((noinline)) matMul(float*  A, float* B, float* C, int M, int N, int P) {

//   int blockSize = (M+NUM_CORES-1)/NUM_CORES;
//   int start = pi_core_id()*blockSize;
//   int end = start + blockSize < M? start + blockSize : M;
  
//   for (int i = start; i < end; i++) {
//     for (int j = 0; j < P; j++) {
//       float temp = 0;

//       //Manual unrolling
//       for (int k = 0; k < (N & 0xfffffffe); k+=2) {
//         temp += (float)(A[i*N+k]   * B[k*P+j]);
//         temp += (float)(A[i*N+k+1] * B[k*P+j+P]);

//       }
//          C[i*P+j] = (float)(temp);
//         //  printf("c[%d]= %f\n",i*P+j,C[i*P+j]);
//     }
//   }
//       // Leftover on N

//       if (N & 0x00000001) 
//       {
//         for (int i=start; i<end; i++) 
//         {
//           for (int j=0; j<P; j++) 
//           {
//             C[i*P+j] += (float)(A[i*N+N-1] * B[(N-1)*P+j]);
//           }
//         }
//       } 

//   #if NUM_CORES > 1
//   pi_cl_team_barrier();
//   #endif
// }
