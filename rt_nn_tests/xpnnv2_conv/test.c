#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


#include "pmsis.h"

#include "data_statstest.h"
//#include "pulp_nn_kernels.h"
#include "pulp_nn_mix_kernels.h"


#define start_cycle_counter()                                   asm volatile("csrw 0xCC0, 0x01;")
#define stop_cycle_counter()                                    asm volatile("csrw 0xCC0, 0x00;")
#define read_cycle_counter(x)                                   asm volatile("csrr %0, 0x780;" : "=r" (x))
#define reset_cycle_counter()                                   asm volatile("csrw 0x780, 0x0;")

uint8_t im2col[IM2COL_DIM] = {0};
uint8_t outputs[OUTPUT_DIM] = {0};

int32_t outputs_fp[OUTPUT_DIM_FP] = {0};

#ifndef PROFILE
int num_cycles;
#else
int im2col_cycles;
int hotloop_prep_cycles;
int hotloop_cycles;
int threshold_cycles;
int requant_cycles;
int hotloop_leftover_cycles;
int matmul4x2_leftover_cycles;
#endif

void call_krnl_0();
void test_0();

int main(int argc, char *argv[])
{
#if KRAKEN_PTEST == 1
  kraken_padframe_aon_pad_gpioa_cfg_rxe_set(24, 0);
  kraken_padframe_aon_pad_gpioa_cfg_trie_set(24, 0);
  kraken_padframe_aon_pad_gpioa_cfg_chip2pad_set(24, 0);
#endif
  int n_mismatches = 0;
  int mismatches_tot = 0;

    

  #ifndef PROFILE
  num_cycles = 0;
  #endif

  if (get_core_id() == 0) {
  printf("===> TEST 0: Running xpulp_nn_mix_conv_u4_u8_i2...\n");
  printf("  dims_in     = [4, 4]\n");
  printf("  dims_kernel = [3, 3]\n");
  printf("  ch_in/out   = [16, 32]\n");
  //printf("  padding_y_top    = [%d]\n", padding_y_top);
  //printf("  padding_y_bottom = [%d]\n", padding_y_bottom);
  //printf("  padding_x_left   = [%d]\n", padding_x_left);
  //printf("  padding_x_right  = [%d]\n", padding_x_right);
  //printf("  stride_x         = [%d]\n", stride_x);
  //printf("  stride_y         = [%d]\n", stride_y);
  }
  test_0();
  #ifndef PROFILE
  stop_cycle_counter();
  read_cycle_counter(num_cycles);
  if (get_core_id() == 0) {
  printf("===> TEST 0: Finished running xpulp_nn_mix_conv_u4_u8_i2\n");
  printf("num_cycles = %d\n", num_cycles);
  printf("MACs = 73728\n");
  printf("MACs/cycle = %.4f\n", 73728/num_cycles);
  }
  #endif
  if (get_core_id() == 0) {
  printf("Checking for mismatches..\n");
  n_mismatches = 0;

  for(int i=0; i < 512; i++) {
    if (outputs[i] != exp_outp_0[i]){
        printf("***Mismatch in test 0 at iteration %d: Expected: %x, got: %x\n", i, exp_outp_0[i], outputs[i]);
        n_mismatches++;
    }
  }
  }
  mismatches_tot += n_mismatches;

  if (get_core_id() == 0) {
  printf("Got %d mismatches in %d tests\n", mismatches_tot, 1);
  }
  return mismatches_tot;
}


void call_krnl_0(void) {
  uint8_t * pInp;
  uint8_t * pIm2ColBuffer;
  int8_t * pBias = NULL;
  uint8_t * pOut;
  int8_t * pWeight;
  uint32_t * pThr;
  int32_t * pKappa, pLambda;
  #ifdef PROFILE
  int32_t im2col_cycles = 0;
  int32_t hotloop_prep_cycles = 0;
  int32_t hotloop_cycles = 0;
  int32_t threshold_cycles = 0;
  int32_t requant_cycles = 0;
  int32_t hotloop_leftover_cycles = 0;
  int32_t matmul4x2_leftover_cycles = 0;
  #endif
  pInp = inp_l1;
  
  pOut = outp_l1;
  pIm2ColBuffer = im2col_l1;
  pWeight = wt_l1;
  pThr = threshs_l1;
  pKappa = kappa_l1;
  pLambda = lambda_l1;
#if KRAKEN_PTEST == 1
  if (pi_core_id() == 0) {
    kraken_padframe_aon_pad_gpioa_cfg_chip2pad_set(24, 1);
  } 
#endif
  xpulp_nn_mix_conv_u4_u8_i2(
    pInp,
    pIm2ColBuffer,
    pBias,
    pOut,
    pWeight,
    pKappa,
    pLambda,
    1,
    13,
    4,
    4,
    16,
    4,
    4,
    32,
    3,
    3,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
#ifndef PROFILE
    1
#else
    1,
    &im2col_cycles,
    &hotloop_prep_cycles,
    &hotloop_cycles,
    &requant_cycles,
    &hotloop_leftover_cycles,
    &matmul4x2_leftover_cycles
#endif
    );

#if KRAKEN_PTEST == 1
  if (pi_core_id() == 0) {
    kraken_padframe_aon_pad_gpioa_cfg_chip2pad_set(24, 0);
  }
#endif
  #ifdef PROFILE
  if (pi_core_id() == 0) {
  printf("im2col_cycles = %d\n", im2col_cycles);
  printf("hotloop_prep_cycles = %d\n", hotloop_prep_cycles);
  printf("hotloop_cycles = %d\n", hotloop_cycles);
  printf("requant_cycles = %d\n", requant_cycles);
  printf("threshold_cycles = %d\n", threshold_cycles);
  printf("hotloop_leftover_cycles = %d\n", hotloop_leftover_cycles);
  printf("matmul4x2_leftover_cycles = %d\n", matmul4x2_leftover_cycles);
  }
  #endif
}

void test_0(void) {
  // DMA transfer inputs from L2 to L1
  if (pi_core_id() == 0) {
     plp_dma_memcpy(pIn_0, inp_l1, 128, 1);
     plp_dma_barrier();
  }
  pi_cl_team_barrier(0);
  if (pi_core_id() == 0) {
     plp_dma_memcpy(pLambda_0, lambda_l1, 32 * 4, 1); // 4 bytes per lambda item
     plp_dma_barrier();
  }
  if (pi_core_id() == 0) {
     plp_dma_memcpy(pKappa_0, kappa_l1, 32 * 4, 1); // 4 bytes per lambda item
     plp_dma_barrier();
  }
  pi_cl_team_barrier(0);
  // transfer weights
  if (pi_core_id() == 0) {
     plp_dma_memcpy(pWeight_0, wt_l1, 1152, 1);
     plp_dma_barrier();
  }
  pi_cl_team_barrier(0);
  call_krnl_0();
  // get outputs back with DMA
  if (pi_core_id() == 0) {
     plp_dma_memcpy(outputs, outp_l1, 512, 0);
     plp_dma_barrier();
  }
}










