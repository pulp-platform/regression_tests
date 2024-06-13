// massive hack to enable rt compatibility
#define pi_core_id get_core_id
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "dory_dma.h"

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
  printf("===> TEST 0: Running xpulp_tnn_linear_ternary_i32_signed...\n");
  printf("  ch_in/out   = [100, 100]\n");
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
  printf("===> TEST 0: Finished running xpulp_tnn_linear_ternary_i32_signed\n");
  printf("num_cycles = %d\n", num_cycles);
  printf("MACs = 10000\n");
  printf("MACs/cycle = %.4f\n", 10000/num_cycles);
  }
  #endif
  if (get_core_id() == 0) {
  printf("Checking for mismatches..\n");
  n_mismatches = 0;

  for(int i=0; i < 100; i++) {
    if (outputs_fp[i] != exp_outp_0[i]){
        printf("***Mismatch in test 0 at iteration %d: Expected: %x, got: %x\n", i, exp_outp_0[i], outputs_fp[i]);
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
  xpulp_tnn_linear_ternary_i32_signed(
    pInp,
    pBias,
    (int32_t *) pOut,
    pWeight,
    100,
    100);

#if KRAKEN_PTEST == 1
  if (pi_core_id() == 0) {
    kraken_padframe_aon_pad_gpioa_cfg_chip2pad_set(24, 0);
  }
#endif
}

void test_0(void) {
  uint32_t dma_channel = dory_dma_allocate();
  DMA_copy dma_tx = {0};
  // DMA transfer inputs from L2 to L1
  dma_tx.ext = pIn_0;
  dma_tx.loc = inp_l1;
  dma_tx.number_of_1d_copies = 1;
  dma_tx.number_of_2d_copies = 1;
  dma_tx.length_1d_copy = 20;
  dma_tx.stride_1d = 1;
  dma_tx.stride_2d = 1;
  dma_tx.dir = 1;
  dma_tx.tid = dma_channel;
  dory_dma_memcpy_async(&dma_tx);
  // transfer weights
  dma_tx.ext = pWeight_0;
  dma_tx.loc = wt_l1;
  dma_tx.length_1d_copy = 2000;
  dory_dma_memcpy_async(&dma_tx);
  call_krnl_0();
  // get outputs back with DMA
  dma_tx.dir = 0;
  dma_tx.ext = outputs_fp;
  dma_tx.loc = outp_l1;
  dma_tx.length_1d_copy = 400;
  dory_dma_memcpy_async(&dma_tx);
  dory_dma_free(&dma_tx);
}










