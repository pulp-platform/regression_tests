#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include "pulp.h"

// #define VERBOSE

#define MAX_BUFFER_SIZE 0x2000

L2_DATA static uint8_t ext[MAX_BUFFER_SIZE];
L1_DATA static uint8_t loc[MAX_BUFFER_SIZE];

// Transfer types
typedef enum {L2_TO_L1, L1_TO_L2} test_type_t;

#ifdef VERBOSE
static void print_memory(uint8_t *mem, unsigned int size, const char *name) {
    printf("Memory dump of %s:\n", name);
    for (unsigned int i = 0; i < size; i++) {
        printf("0x%02X ", mem[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}
#endif

int test_idma_2D(uint32_t size, test_type_t type, uint32_t ext_addr, uint32_t tcdm_addr,
                 unsigned int length, unsigned int src_stride, unsigned int dst_stride, unsigned int num_reps);

int main(void) {
    if (rt_cluster_id() != 0) {
        return bench_cluster_forward(0);
    }

    int error_count = 0;

    if (get_core_id() == 0) {
        unsigned int sizes[] = {16, 64, 256, 1024};     // Total number of bytes (for initialization of the values in memory)
        unsigned int lengths[] = {4, 8, 16, 64};        // Number of bytes to transfer per 1D transaction
        unsigned int num_reps[] = {4, 8, 16, 16};       // Number of repetitions of 1D transactions
        unsigned int src_strides[] = {4, 8, 24, 56};    // Number of strides in source memory
        unsigned int dst_strides[] = {4, 12, 24, 64};   // Number of strides in destination memory

        for (unsigned int i = 0; i < 4; i++) {
            error_count += test_idma_2D(sizes[i], L2_TO_L1, (uint32_t)ext, (uint32_t)loc,
                                        lengths[i], src_strides[i], dst_strides[i], num_reps[i]);
        }

        for (unsigned int i = 0; i < 4; i++) {
            error_count += test_idma_2D(sizes[i], L1_TO_L2, (uint32_t)ext, (uint32_t)loc,
                                        lengths[i], src_strides[i], dst_strides[i], num_reps[i]);
        }
    }

    return error_count;
}

int test_idma_2D(uint32_t size, test_type_t type, uint32_t ext_addr, uint32_t tcdm_addr,
                 unsigned int length, unsigned int src_stride, unsigned int dst_stride, unsigned int num_reps) {
    volatile uint8_t *src_ptr, *dst_ptr;
    volatile int error = 0;
    volatile unsigned int id;

    if (type == L2_TO_L1) {
        src_ptr = (uint8_t *)ext_addr;
        dst_ptr = (uint8_t *)tcdm_addr;
        for (uint32_t i = 0; i < size; i++) src_ptr[i] = (uint8_t)(i & 0xFF);
        id = pulp_cl_idma_L2ToL1_2d((unsigned int)src_ptr, (unsigned int)dst_ptr, length, src_stride, dst_stride, num_reps);
    } else {
        src_ptr = (uint8_t *)tcdm_addr;
        dst_ptr = (uint8_t *)ext_addr;
        for (uint32_t i = 0; i < size; i++) src_ptr[i] = (uint8_t)(i & 0xFF);
        id = pulp_cl_idma_L1ToL2_2d((unsigned int)src_ptr, (unsigned int)dst_ptr, length, src_stride, dst_stride, num_reps);
    }

    plp_dma_barrier();

    for (unsigned int rep = 0; rep < num_reps; rep++) {
        unsigned int src_offset = rep * src_stride;
        unsigned int dst_offset = rep * dst_stride;
        for (unsigned int i = 0; i < length; i++) {
            uint8_t expected = src_ptr[src_offset + i];
            uint8_t actual = dst_ptr[dst_offset + i];
            if (expected != actual) error++;
        }
    }

#ifdef VERBOSE
    if (error == 0) {
        printf("Test passed for %s with size %d, length %d, src_stride %d, dst_stride %d, num_reps %d\n", type == L2_TO_L1 ? "L2_TO_L1" : "L1_TO_L2", size, length, src_stride, dst_stride, num_reps);
    } else {
        printf("Test failed for %s with size %d, length %d, src_stride %d, dst_stride %d, num_reps %d\n", type == L2_TO_L1 ? "L2_TO_L1" : "L1_TO_L2", size, length, src_stride, dst_stride, num_reps);
    }
#endif

    return error;
}