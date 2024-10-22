
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include "pulp.h"

#define VERBOSE

#define MAX_BUFFER_SIZE 0x2000
#define BUFFER_SIZE     0x0200

L1_DATA static uint8_t src_buffer[MAX_BUFFER_SIZE];
L1_DATA static uint8_t dst_buffer[MAX_BUFFER_SIZE];

int test_idma_l1_to_l1(unsigned int len);

int main(void) {
    if (rt_cluster_id() != 0) {
        return bench_cluster_forward(0);
    }

    int error_count = 0;

    if (get_core_id() == 0) {
        // Run the test for different buffer sizes
        for (unsigned int len = 8; len <= BUFFER_SIZE; len *= 2) {
            error_count += test_idma_l1_to_l1(len);
        }
    }

    return error_count;
}

int test_idma_l1_to_l1(unsigned int len) {
    volatile unsigned int id;
    volatile int error = 0;
    volatile uint32_t test, read;

    printf("STARTING L1 TO L1 DMA TEST FOR LENGTH: %d\n", len);

    // Fill source buffer with known data pattern
    for (unsigned int i = 0; i < len / 4; i++) {
        ((uint32_t *)src_buffer)[i] = 0xABCD0000 + i;
    }

    // Clear destination buffer
    memset(dst_buffer, 0, len);

    // Perform DMA transfer from src_buffer to dst_buffer within L1 memory
    id = pulp_idma_L1ToL1((unsigned int)src_buffer, (unsigned int)dst_buffer, len);

    // Wait for DMA transfer to complete
    plp_dma_barrier();

    // Verify data in destination buffer
    for (unsigned int i = 0; i < len / 4; i++) {
        test = 0xABCD0000 + i;
        read = ((uint32_t *)dst_buffer)[i];

        if (test != read) {
            printf("Error!!! Read: %x, Expected: %x, Index: %d\n", read, test, i);
            error++;
        }
    }

    if (error == 0) {
        printf("L1 to L1 DMA transfer test passed for length %d.\n", len);
    } else {
        printf("L1 to L1 DMA transfer test failed for length %d with %d errors.\n", len, error);
    }

    return error;
}
