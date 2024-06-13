#include "pmsis.h"
#include "pulp_nn_utils.h"
#include "xpulp_tnn_linear_ternary_i32_signed.h"

void __attribute__((noinline)) xpulp_tnn_linear_ternary_i32_signed(
                   int8_t *pIn,
                   int8_t *pBias,
                   int8_t *pOut,
                   int8_t *pWeight,
                   uint16_t dim_vec,
                   uint16_t num_o_neurons)

{
  uint16_t dim_vec_in = dim_vec/5; // number of bytes
  uint16_t dim_vec_wt = dim_vec_in;
  uint16_t dim_vec_words = dim_vec_in >> 2; // number of words

#ifdef FC_TEST
  int core_id = 0;
#else
  int core_id = pi_core_id();
#endif

  int Log2Core = log2(NUM_CORES);
  int chunk = (num_o_neurons >> Log2Core) + ((num_o_neurons & (NUM_CORES-1))!=0);
  int start = min(chunk * core_id, num_o_neurons);
  int stop = min(start + chunk, num_o_neurons);
  int32_t * pOutBuffer = ((int32_t *) pOut) + start;

  for(int i=start; i<stop; i++)
    {
      int sum = 0;

      if (pBias != NULL)
        {
          sum = *(int32_t *)(pBias + 4*i);
        }

      uint8_t *pA = pWeight + (i * dim_vec_wt);

      uint8_t *pB = pIn;

      int32_t *ptrA  = (int32_t *) pA;

      int32_t *ptrB  = (int32_t *) pB;

      ptrA = MacLoadInit(1, 0, 0, 0, ptrA);
      ptrB = MacLoadInit(0, 1, 0, 0, ptrB);

      for (int j=0; j<dim_vec_words; j++)
      {
        sum = MacLoads20(1, 0, 0, 0, ptrA, sum);
        ptrA = MacLoadUpdate(ptrA);
        ptrB = MacLoadInit(0, 1, 0, 0, ptrB);
        //ensure enough instructions in the HW loop - otherwise it will work on GVSOC but not in real hardware!
        asm volatile("nop;");
      }

      uint16_t col_cnt = dim_vec_in & 0x3;

      if (col_cnt) {
        int32_t valB;
        pA += (dim_vec_words << 2);
        pB += (dim_vec_words << 2);
        if (col_cnt == 1)
          {
            valB = 0xd9 << 24 | 0xd9 << 16 | 0xd9 << 8 | *pB;
          }
        else if (col_cnt == 2)
          {
            valB = 0xd9 << 24 | 0xd9 << 16 | *(pB+1) << 8 | *pB;
          }
        else if (col_cnt == 3)
          {
            valB = 0xd9 << 24 | *(pB+2) << 16 | *(pB+1) << 8 | *pB;
          }
        // we can leave ptrA and the associated nn-rf as is because we
        // zero-padded the B input so the "leftover" data in the A word doesn't
        // matter!
        uint32_t * pB_p = &valB;
        pB_p = MacLoadInit(0, 1, 0, 0, pB_p);
        // try to work around HW bug with misaligned NNRF addresses by initializing NNRF twice...
        pB_p = &valB;
        pB_p = MacLoadInit(0, 1, 0, 0, pB_p);
        sum = MacLoads20(0, 0, 0, 0, pB_p, sum);
        // work around broken/non-existent forwarding
        asm volatile("nop;");
      }
      *(pOutBuffer++) = sum;

    }
  #ifndef FC_TEST
  pi_cl_team_barrier(0);
  #endif
}
