// License, Version 0.51 (the "License"); you may not use this file except in
// or agreed to in writing, software, hardware and materials distributed under
// this License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include "pulp.h"

#include <stdio.h>
#include <stdint.h>
#include <limits.h> /* for CHAR_BIT */


// #include "data.h"

#define STACK_SIZE 2048

// void main_fn(testresult_t *result, void (*start)(), void (*stop)());

// testcase_t testcases[] = {
//   { .name = "Matrix Multiplication", .test = main_fn },
//   {0, 0}
// };

// int done = 0;

int retval = 0;


// void main_fn(testresult_t *result, void (*start)(), void (*stop)()){
  
//   // if (get_core_id() == 0)
//   //   matrix_init(matA, matB, matC);
 
//   // #ifndef FABRIC
//   // synch_barrier();
//   // #endif
  
//   start();
//   // matMul(matA, matB, matC, M, N, P);
//   // matMulBeppe(matA, matB, matC, M, N, P);
  
//   stop();

//   // #ifdef CHECK
//   // result->errors = check_result(matC);
//   // #endif
// };


int main()
{
  int nbErrors = 0;

  if(get_core_id() == 0){
    while(1){

    }
  }

  synch_barrier();

  retval = nbErrors;

  return retval;
}
