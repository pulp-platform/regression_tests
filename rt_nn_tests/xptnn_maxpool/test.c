#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


#include "xpulp_tnn_matmul_ternary.h"
#include "xpulp_tnn_matmul_ternary_4x1.h"
#include "xpulp_tnn_conv_ternary.h"
#include "xpulp_tnn_conv_ternary_signed.h"
#ifndef PROFILE // HACKYTIME
#include "xpulp_tnn_conv1d_ternary.h"
#include "xpulp_tnn_conv1d_ternary_signed.h"
#endif
#include "xpulp_tnn_maxpool_ternary.h"
#include "xpulp_tnn_linear_ternary_i32_signed.h"
#include "xpulp_tnn_linear_ternary_i32.h"
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
  printf("===> TEST 0: Running xpulp_tnn_maxpool_ternary...\n");
  printf("  dims_in     = [32, 32]\n");
  printf("  dims_kernel = [2, 2]\n");
  printf("  ch_in/out   = [40, 40]\n");
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
  printf("===> TEST 0: Finished running xpulp_tnn_maxpool_ternary\n");
  printf("num_cycles = %d\n", num_cycles);
  printf("MACs = 1638400\n");
  printf("MACs/cycle = %.4f\n", 1638400/num_cycles);
  }
  #endif
  if (get_core_id() == 0) {
  printf("Checking for mismatches..\n");
  n_mismatches = 0;

  for(int i=0; i < 2048; i++) {
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
  pInp = inp_l1;
  
  pOut = outp_l1;
#if KRAKEN_PTEST == 1
  if (pi_core_id() == 0) {
    kraken_padframe_aon_pad_gpioa_cfg_chip2pad_set(24, 1);
  } 
#endif
  xpulp_tnn_maxpool_ternary(
    pInp,
    pOut,
    32,
    32,
    40,
    16,
    16,
    2,
    2,
    0,
    0,
    0,
    0,
    2,
    2);

#if KRAKEN_PTEST == 1
  if (pi_core_id() == 0) {
    kraken_padframe_aon_pad_gpioa_cfg_chip2pad_set(24, 0);
  }
#endif
}

void test_0(void) {
  // DMA transfer inputs from L2 to L1
  if (pi_core_id() == 0) {
     plp_dma_memcpy(pIn_0, inp_l1, 8192, 1);
     plp_dma_barrier();
  }
  pi_cl_team_barrier(0);
  call_krnl_0();
  // get outputs back with DMA
  if (pi_core_id() == 0) {
     plp_dma_memcpy(outputs, outp_l1, 2048, 0);
     plp_dma_barrier();
  }
}










