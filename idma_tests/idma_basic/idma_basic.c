/*
 * Copyright (C) 2021 ETH Zurich and University of Bologna
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <math.h>
#include "pulp.h"
#include <stdio.h>

#define VERBOSE
#define MAX_BUFFER_SIZE 0x400

L2_DATA static unsigned char ext[MAX_BUFFER_SIZE*8];
L1_DATA static unsigned char loc[MAX_BUFFER_SIZE*8];

#define EXT_DATA_ADDR ((unsigned int)ext)
#define TCDM_DATA_ADDR ((unsigned int)loc)

int test_idma(unsigned int src_addr, unsigned int dst_addr,
              unsigned int num_bytes);

int main() {

  if (rt_cluster_id() != 0) return bench_cluster_forward(0);

  int error_count = 0;
  int core_id = get_core_id();

  // if (get_core_id() == 0) {

    for (int i = 1; i < MAX_BUFFER_SIZE; i = 2 * i) {
      error_count += test_idma(EXT_DATA_ADDR + (core_id*MAX_BUFFER_SIZE), TCDM_DATA_ADDR + (core_id*MAX_BUFFER_SIZE), i);
    }
    for (int i = 1; i < MAX_BUFFER_SIZE; i = 2 * i) {
      error_count += test_idma(TCDM_DATA_ADDR + (core_id*MAX_BUFFER_SIZE), EXT_DATA_ADDR + (core_id*MAX_BUFFER_SIZE), i);
    }
  // }

  return error_count;
}

int test_idma(unsigned int src_addr, unsigned int dst_addr,
              unsigned int num_bytes) {

#ifdef VERBOSE
  // printf("STARTING TEST FOR %d TRANSFERS FROM %p TO %p\n", num_bytes, src_addr,
        //  dst_addr);
#endif

  for (int i = 0; i < num_bytes; i++) {
    *(unsigned char*)(src_addr + i) = i & 0xFF;
  }

  for (int i = 0; i < num_bytes + 16; i++) {
    *(unsigned char*)(dst_addr + i) = 0;
  }

  // Setup DMA
  // unsigned char* dma_ptr = (char*)ARCHI_MCHAN_DEMUX_ADDR;

  // *(unsigned int *)(dma_ptr + CLUSTER_DMA_FRONTEND_SRC_ADDR_REG_OFFSET ) =
  // src_addr;
  // *(unsigned int *)(dma_ptr + CLUSTER_DMA_FRONTEND_DST_ADDR_REG_OFFSET ) =
  // dst_addr;
  // *(unsigned int *)(dma_ptr + CLUSTER_DMA_FRONTEND_NUM_BYTES_REG_OFFSET) =
  // num_bytes;
  // *(unsigned int *)(dma_ptr + CLUSTER_DMA_FRONTEND_CONF_REG_OFFSET     ) = 0;
  // asm volatile("" : : : "memory");

  // // Launch TX
  // unsigned int dma_tx_id = *(unsigned int *)(dma_ptr +
  // CLUSTER_DMA_FRONTEND_NEXT_ID_REG_OFFSET);
  synch_barrier();

  unsigned int dma_tx_id = pulp_idma_memcpy(dst_addr, src_addr, num_bytes);

  // printf("After launch, dma_id: %x, %x, %x\n", dma_tx_id, (unsigned int
  // *)(dma_ptr + CLUSTER_DMA_FRONTEND_DONE_REG_OFFSET), (unsigned int
  // *)(dma_ptr + CLUSTER_DMA_FRONTEND_DONE_REG_OFFSET + ((dma_tx_id &
  // 0xf0000000) >> 26)));

  // while((dma_tx_id & 0x0fffffff) > *(unsigned int *)(dma_ptr +
  // CLUSTER_DMA_FRONTEND_DONE_REG_OFFSET + ((dma_tx_id & 0xf0000000) >> 26))) {
  //   asm volatile("nop");
  // }
  plp_dma_wait(dma_tx_id);

  unsigned int test, read;
  unsigned int error = 0;

  for (int i = 0; i < num_bytes; i++) {
    test = i & 0xFF;
    read = *(unsigned char*)(dst_addr + i);
    if (test != read) {
      printf("Error!!! Read: %x, Test:%x, Index: %d \n ", read, test, i);
      error++;
    }
  }

  for (int i = num_bytes; i < num_bytes + 16; i++) {

    test = 0;
    read = *(unsigned char*)(dst_addr + i);

    if (test != read) {
      printf("Error!!! Read: %x, Test:%x, Index: %d \n ", read, test, i);
      error++;
    }
  }

  if (get_core_id() == 0) {
    if (error == 0)
      printf("OOOOOOK!!!!!!\n");
    else
      printf("NOT OK!!!!!\n");
  }

  return error;
}
