// // License, Version 0.51 (the "License"); you may not use this file except in
// // or agreed to in writing, software, hardware and materials distributed under
// // this License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// // CONDITIONS OF ANY KIND, either express or implied. See the License for the
// // specific language governing permissions and limitations under the License.

// #include "config.h"
// #include "pulp.h"

// #include <stdio.h>
// #include <stdint.h>
// #include <limits.h> /* for CHAR_BIT */
// #include <math.h>

// #include "matmul.h"

// #include "data.h"

// #define STACK_SIZE 2048

// void main_fn(testresult_t *result, void (*start)(), void (*stop)());

// testcase_t testcases[] = {
//   { .name = "Matrix Multiplication", .test = main_fn },
//   {0, 0}
// };

// DATA_LOCATION MA_TYPE matA[M*N] __attribute__ ((aligned (4)));
// DATA_LOCATION MB_TYPE matB[N*P] __attribute__ ((aligned (4)));
// DATA_LOCATION OUT_TYPE matC[M*P] __attribute__ ((aligned (4)));

// // End of computation
// int done = 0;

// int retval = 0;

// void __attribute__ ((noinline)) matrix_init(MA_TYPE * __restrict__ A, MB_TYPE * __restrict__ B, OUT_TYPE * __restrict__ C) {
//   for (int i = 0; i < M; i++) 
//     for (int j = 0; j < N; j++){
//       A[i*N+j] = A_mat[i*N+j];
//     } 
      
//   for (int i = 0; i < N; i++) 
//     for (int j = 0; j < P; j++){
//       B[i*P+j] = B_mat[i*P+j];
//     }
    
//   for (int i = 0; i < M; i++) 
//     for (int j = 0; j < P; j++)  
//       C[i*P+j] = 0;
  
// }

// int __attribute ((noinline)) check_result(OUT_TYPE * __restrict__ result) {
//   #ifndef FABRIC
//     synch_barrier();
//   #endif

//   if(get_core_id() == 0) {
//     float diff;
//     int err = 0;

//     for (int i = 0; i < (M*P); i++) {
//       diff = fabs(result[i] - ref[i]);
//       if(diff > THR) {
//         err++;
//       #ifdef VERBOSE

//         printf("Error at index %d:\t refrence %f\t output %f\t error %.4f\n", i, ref[i], result[i], diff);
//       #endif
      
//       }

//       #ifdef PRINT_RESULTS

//         printf("index %d:\t refrence %f\t output %f\t error %f\n", i, ref[i], result[i], diff);
//       #endif
//     }

//     return err;

//   }
// }

// void main_fn(testresult_t *result, void (*start)(), void (*stop)()){
  
//   if (get_core_id() == 0)
//     matrix_init(matA, matB, matC);
 
//   #ifndef FABRIC
//   synch_barrier();
//   #endif
  
//   start();
//   matMul(matA, matB, matC, M, N, P);
//   // matMulBeppe(matA, matB, matC, M, N, P);
  
//   stop();

//   #ifdef CHECK
//   result->errors = check_result(matC);
//   #endif
// };


// int main()
// {
//   int nbErrors = 0;
//   #ifdef FABRIC
//       main_fn();
//   #else
//   if (rt_cluster_id() != 0)
//     return bench_cluster_forward(0);

//   nbErrors = run_suite(testcases);

//   synch_barrier();
//   #endif
//   retval = nbErrors;

//   return retval;
// }




// License, Version 0.51 (the "License"); you may not use this file except in
// or agreed to in writing, software, hardware and materials distributed under
// this License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include "config.h"
#include "pulp.h"

#include <stdio.h>
#include <stdint.h>
#include <limits.h> /* for CHAR_BIT */
#include <math.h>

#include "matmul.h"

#include "data.h"

#define STACK_SIZE 2048

// void main_fn(testresult_t *result, void (*start)(), void (*stop)());

// testcase_t testcases[] = {
//   { .name = "Matrix Multiplication", .test = main_fn },
//   {0, 0}
// };

// DATA_LOCATION MA_TYPE matA[M*N] __attribute__ ((aligned (4)));
// DATA_LOCATION MB_TYPE matB[N*P] __attribute__ ((aligned (4)));
// DATA_LOCATION OUT_TYPE matC[M*P] __attribute__ ((aligned (4)));

// #define M 8
// #define N 8
// #define P 8
// DATA_LOCATION MA_TYPE matA[M*N] = {
//     0.176752, 0.491711, 0.429671, 0.675534, 0.068130, 0.670481, 0.542697, 0.696783, 
//     0.717564, 0.937371, 0.090031, 0.344593, 0.168206, 0.799651, 0.647601, 0.312144,
//     0.437652, 0.860971, 0.610762, 0.113725, 0.555328, 0.576084, 0.455330, 0.462992,
//     0.604485, 0.067010, 0.102986, 0.841586, 0.232434, 0.059415, 0.609322, 0.386260,
//     0.115570, 0.266360, 0.005684, 0.494681, 0.703959, 0.445297, 0.168109, 0.639743,
//     0.348519, 0.873973, 0.291722, 0.654982, 0.967186, 0.616990, 0.960774, 0.693926,
//     0.885897, 0.091966, 0.211831, 0.337563, 0.732764, 0.748504, 0.778368, 0.358903,
//     0.959345, 0.813612, 0.010650, 0.288702, 0.466080, 0.554527, 0.980395, 0.899280};
// DATA_LOCATION MB_TYPE matB[N*P] = {
//     0.176752, 0.491711, 0.429671, 0.675534, 0.068130, 0.670481, 0.542697, 0.696783, 
//     0.717564, 0.937371, 0.090031, 0.344593, 0.168206, 0.799651, 0.647601, 0.312144,
//     0.437652, 0.860971, 0.610762, 0.113725, 0.555328, 0.576084, 0.455330, 0.462992,
//     0.604485, 0.067010, 0.102986, 0.841586, 0.232434, 0.059415, 0.609322, 0.386260,
//     0.115570, 0.266360, 0.005684, 0.494681, 0.703959, 0.445297, 0.168109, 0.639743,
//     0.348519, 0.873973, 0.291722, 0.654982, 0.967186, 0.616990, 0.960774, 0.693926,
//     0.885897, 0.091966, 0.211831, 0.337563, 0.732764, 0.748504, 0.778368, 0.358903,
//     0.959345, 0.813612, 0.010650, 0.288702, 0.466080, 0.554527, 0.980395, 0.899280};
// DATA_LOCATION OUT_TYPE matC[M*P] ;






// End of computation
int done = 0;

int retval = 0;

// void __attribute__ ((noinline)) matrix_init(MA_TYPE * __restrict__ A, MB_TYPE * __restrict__ B, OUT_TYPE * __restrict__ C) {
//   for (int i = 0; i < M; i++) 
//     for (int j = 0; j < N; j++){
//       A[i*N+j] = A_mat[i*N+j];
//     } 
      
//   for (int i = 0; i < N; i++) 
//     for (int j = 0; j < P; j++){
//       B[i*P+j] = B_mat[i*P+j];
//     }
    
//   for (int i = 0; i < M; i++) 
//     for (int j = 0; j < P; j++)  
//       C[i*P+j] = 0;
  
// }

// int __attribute ((noinline)) check_result(OUT_TYPE * __restrict__ result) {
//   #ifndef FABRIC
//     synch_barrier();
//   #endif

//   if(get_core_id() == 0) {
//     float diff;
//     int err = 0;

//     for (int i = 0; i < (M*P); i++) {
//       diff = fabs(result[i] - ref[i]);
//       if(diff > THR) {
//         err++;
//       #ifdef VERBOSE

//         printf("Error at index %d:\t refrence %f\t output %f\t error %.4f\n", i, ref[i], result[i], diff);
//       #endif
      
//       }

//       #ifdef PRINT_RESULTS

//         printf("index %d:\t refrence %f\t output %f\t error %f\n", i, ref[i], result[i], diff);
//       #endif
//     }

//     return err;

//   }
// }

// void main_fn(testresult_t *result, void (*start)(), void (*stop)()){
  
//   // if (get_core_id() == 0)
//   //   matrix_init(matA, matB, matC);
 
//   // #ifndef FABRIC
//   // synch_barrier();
//   // #endif
  
//   start();
//   matMul(matA, matB, matC, M, N, P);
//   // matMulBeppe(matA, matB, matC, M, N, P);
  
//   stop();

//   // #ifdef CHECK
//   // result->errors = check_result(matC);
//   // #endif
// };


int main()
{
  int nbErrors = 0;

  // if (rt_cluster_id() != 0)
  //   return bench_cluster_forward(0);

  // nbErrors = run_suite(testcases);

  // matMul(matA, matB, matC, M, N, P);
  matMulBeppe(matA, matB, matC, M, N, P);


  synch_barrier();

  retval = nbErrors;

  return retval;
}
