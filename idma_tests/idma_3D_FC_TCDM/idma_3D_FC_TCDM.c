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

int test_idma_3D(uint32_t size, test_type_t type, uint32_t ext_addr, uint32_t tcdm_addr,
                 unsigned int length, unsigned int src_stride_2d, unsigned int dst_stride_2d, unsigned int num_reps,
                 unsigned int src_stride_3d, unsigned int dst_stride_3d, unsigned int num_reps_3d);

int main(void) {
    if (rt_cluster_id() != 0) {
        return bench_cluster_forward(0);
    }

    int error_count = 0;

    if (get_core_id() == 0) {
        unsigned int sizes[] = {64, 256, 1024, 2048};     // Total number of bytes
        unsigned int lengths[] = {4, 8, 16, 32};          // Number of bytes per 1D transaction
        unsigned int src_strides_2d[] = {8, 16, 32, 64};  // 2D stride in source
        unsigned int dst_strides_2d[] = {8, 16, 32, 64};  // 2D stride in destination
        unsigned int num_reps_3d[] = {2, 2, 2, 2};        // Number of 2D pages
        unsigned int src_strides_3d[] = {32, 128, 512, 1024}; // 3D stride in source
        unsigned int dst_strides_3d[] = {32, 128, 512, 1024}; // 3D stride in destination

        for (unsigned int i = 0; i < 4; i++) {
            unsigned int num_reps = sizes[i] / lengths[i]; // Calculate num_reps like in multi_core test
            
            printf("Transfer: %d\n", i);
            printf("Size: %d | Length: %d | Src_stride_2d: %d | Dst_stride_2d: %d | Num_reps_2d: %d\n", 
                   sizes[i], lengths[i], src_strides_2d[i], dst_strides_2d[i], num_reps);
            printf("Src_stride_3d: %d | Dst_stride_3d: %d | Num_reps_3d: %d\n", 
                   src_strides_3d[i], dst_strides_3d[i], num_reps_3d[i]);
            
            printf("L2 to L1 transfer\n");
            error_count += test_idma_3D(sizes[i], L2_TO_L1, (uint32_t)ext, (uint32_t)loc,
                                        lengths[i], src_strides_2d[i], dst_strides_2d[i], num_reps,
                                        src_strides_3d[i], dst_strides_3d[i], num_reps_3d[i]);

            printf("L1 to L2 transfer\n");
            error_count += test_idma_3D(sizes[i], L1_TO_L2, (uint32_t)ext, (uint32_t)loc,
                                        lengths[i], src_strides_2d[i], dst_strides_2d[i], num_reps,
                                        src_strides_3d[i], dst_strides_3d[i], num_reps_3d[i]);
        }
    }

    return error_count;
}

int test_idma_3D(uint32_t size, test_type_t type, uint32_t ext_addr, uint32_t tcdm_addr,
                 unsigned int length, unsigned int src_stride_2d, unsigned int dst_stride_2d, unsigned int num_reps,
                 unsigned int src_stride_3d, unsigned int dst_stride_3d, unsigned int num_reps_3d) {
    volatile uint8_t *src_ptr, *dst_ptr;
    unsigned int offset_2d, offset_3d;
    int error = 0;

    if (type == L2_TO_L1) {
        // L2 to L1 transfer
        src_ptr = (uint8_t*)ext_addr;
        dst_ptr = (uint8_t*)tcdm_addr;

        // Fill source region with test data
        offset_2d = 0;
        offset_3d = 0;
        for (int j = 0; j < num_reps_3d; j++) {
            for (int q = 0; q < num_reps; q++) {
                for (int i = 0; i < length; i++) {
                    src_ptr[i + offset_2d + offset_3d] = (uint8_t)(i & 0xFF);
                }
                offset_2d += src_stride_2d;
            }
            offset_2d = 0;
            offset_3d += (num_reps - 1) * src_stride_2d + src_stride_3d;
        }

        plp_cl_dma_wait_toL1(pulp_cl_idma_L2ToL1_3d((unsigned int)src_ptr, (unsigned int)dst_ptr, 
                                                     length, src_stride_2d, dst_stride_2d, num_reps, 
                                                     src_stride_3d, dst_stride_3d, num_reps_3d));
    } else {
        // L1 to L2 transfer
        src_ptr = (uint8_t*)tcdm_addr;
        dst_ptr = (uint8_t*)ext_addr;

        // Fill source region with test data
        offset_2d = 0;
        offset_3d = 0;
        for (int j = 0; j < num_reps_3d; j++) {
            for (int q = 0; q < num_reps; q++) {
                for (int i = 0; i < length; i++) {
                    src_ptr[i + offset_2d + offset_3d] = (uint8_t)(i & 0xFF);
                }
                offset_2d += src_stride_2d;
            }
            offset_2d = 0;
            offset_3d += (num_reps - 1) * src_stride_2d + src_stride_3d;
        }

        plp_cl_dma_wait_toL2(pulp_cl_idma_L1ToL2_3d((unsigned int)src_ptr, (unsigned int)dst_ptr, 
                                                     length, src_stride_2d, dst_stride_2d, num_reps, 
                                                     src_stride_3d, dst_stride_3d, num_reps_3d));
    }

    // Check the results - exactly like multi_core test
    int src_offset_2d = 0;
    int dst_offset_2d = 0;
    int src_offset_3d = 0;
    int dst_offset_3d = 0;

    for (int rep_3d = 0; rep_3d < num_reps_3d; rep_3d++) {
        for (unsigned int rep = 0; rep < num_reps; rep++) {
            for (unsigned int i = 0; i < length; i++) {
                uint8_t expected = src_ptr[src_offset_2d + src_offset_3d + i];
                uint8_t actual = dst_ptr[dst_offset_2d + dst_offset_3d + i];

                if (expected != actual) {
#ifdef VERBOSE
                    printf("ERROR: expected @%8x[%d] = %8x vs actual @%8x[%d] = %8x\n", 
                           &src_ptr[src_offset_2d + src_offset_3d + i], src_offset_2d + src_offset_3d + i, expected, 
                           &dst_ptr[dst_offset_2d + dst_offset_3d + i], dst_offset_2d + dst_offset_3d + i, actual);
#endif
                    error++;
                }
            }
            src_offset_2d += src_stride_2d;
            dst_offset_2d += dst_stride_2d;
        }
        src_offset_2d = 0;
        dst_offset_2d = 0;
        src_offset_3d += (num_reps - 1) * src_stride_2d + src_stride_3d;
        dst_offset_3d += (num_reps - 1) * dst_stride_2d + dst_stride_3d;
    }

#ifdef VERBOSE
    if (error == 0) {
        printf("Test passed for %s 3D transfer\n", type == L2_TO_L1 ? "L2_TO_L1" : "L1_TO_L2");
    } else {
        printf("Test failed for %s 3D transfer with %d errors\n", 
               type == L2_TO_L1 ? "L2_TO_L1" : "L1_TO_L2", error);
    }
#endif

    return error;
}