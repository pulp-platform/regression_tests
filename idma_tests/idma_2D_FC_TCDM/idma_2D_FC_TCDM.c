#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include "pulp.h"

#define VERBOSE

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
        
        // Number of test cases
        unsigned int cases = 4;

        // Total number of bytes (for initialization of the values in memory)
        unsigned int sizes[] = {16, 64, 256, 1024};
        // unsigned int size = 16;

        // Number of bytes to transfer per 1D transaction
        unsigned int lengths[] = {4, 8, 16, 64};
        // unsigned int length = 2;

        // Number of repetitions of 1D transactions
        unsigned int num_reps[] = {4, 8, 16, 16};
        // unsigned int num_reps = 4;

        // Number of strides in source memory
        unsigned int src_strides[] = {4, 8, 24, 56};
        // unsigned int src_stride = 4;

        // Number of strides in destination memory
        unsigned int dst_strides[] = {4, 12, 24, 64};
        // unsigned int dst_stride = 3;

        for (unsigned int i = 0; i < cases; i++) {
            error_count += test_idma_2D(sizes[i], L2_TO_L1, (uint32_t)ext, (uint32_t)loc,
                                        lengths[i], src_strides[i], dst_strides[i], num_reps[i]);
        }

        for (unsigned int i = 0; i < cases; i++) {
            error_count += test_idma_2D(sizes[i], L1_TO_L2, (uint32_t)ext, (uint32_t)loc,
                                        lengths[i], src_strides[i], dst_strides[i], num_reps[i]);
        }
    }

    return error_count;
}

int test_idma_2D(uint32_t size, test_type_t type, uint32_t ext_addr, uint32_t tcdm_addr,
                 unsigned int length, unsigned int src_stride, unsigned int dst_stride, unsigned int num_reps) {
    volatile uint8_t expected, actual;
    volatile int error = 0;
    volatile unsigned int id;

    if (type == L2_TO_L1) {
    
        for (uint32_t i = 0; i < size; i++) {
            *(uint8_t *)(ext_addr + i) = (uint8_t)(i & 0xFF);
        }

// #ifdef VERBOSE
//         // Initialized memory
//         print_memory((uint8_t *)ext_addr, size, "L2 (Source)");
// #endif
        memset((void *)tcdm_addr, 0, size + 16);

        id = pulp_cl_idma_L2ToL1_2d(ext_addr, tcdm_addr, length, src_stride, dst_stride, num_reps);
        
    } else if (type == L1_TO_L2) {

        for (uint32_t i = 0; i < size; i++) {
            *(uint8_t *)(tcdm_addr + i) = (uint8_t)(i & 0xFF);
        }

// #ifdef VERBOSE
//         // Initialized memory
//         print_memory((uint8_t *)tcdm_addr, size, "L1 (Source)");
// #endif

        memset((void *)ext_addr, 0, size + 16);

        id = pulp_cl_idma_L1ToL2_2d(tcdm_addr, ext_addr, length, src_stride, dst_stride, num_reps);
    } else {
        printf("Invalid test type. It must be either L2_TO_L1 or L1_TO_L2.\n");
        return 1;
    }

    // Wait for DMA transfer to complete
    plp_dma_barrier();

    // Verify data
    if (type == L2_TO_L1) {
        // Verify data transferred from L2 to L1
        for (unsigned int rep = 0; rep < num_reps; rep++) {
            unsigned int src_offset = rep * src_stride;
            unsigned int dst_offset = rep * dst_stride;
            for (unsigned int i = 0; i < length; i++) {
                expected = *(uint8_t *)(ext_addr + src_offset + i);
                actual = *(uint8_t *)(tcdm_addr + dst_offset + i);
                if (expected != actual) {
                    printf("Error at L1 address 0x%08X: Expected 0x%02X, Got 0x%02X\n",
                           tcdm_addr + dst_offset + i, expected, actual);
                    error++;
                }
            }
        }
    } else if (type == L1_TO_L2) {
        // Verify data transferred from L1 to L2
        for (unsigned int rep = 0; rep < num_reps; rep++) {
            unsigned int src_offset = rep * src_stride;
            unsigned int dst_offset = rep * dst_stride;
            for (unsigned int i = 0; i < length; i++) {
                expected = *(uint8_t *)(tcdm_addr + src_offset + i);
                actual = *(uint8_t *)(ext_addr + dst_offset + i);
                if (expected != actual) {
                    printf("Error at L2 address 0x%08X: Expected 0x%02X, Got 0x%02X\n",
                           ext_addr + dst_offset + i, expected, actual);
                    error++;
                }
            }
        }
    }

    if (error == 0) {
        printf("Test passed for %s transfer.\n", type == L2_TO_L1 ? "L2_TO_L1" : "L1_TO_L2");
    } else {
        printf("Test failed for %s transfer with %d errors.\n", type == L2_TO_L1 ? "L2_TO_L1" : "L1_TO_L2", error);
    }

    return error;
}
