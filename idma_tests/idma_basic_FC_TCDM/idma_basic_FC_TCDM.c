#include <math.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include "pulp.h"

#define VERBOSE

#define MAX_BUFFER_SIZE 0x2000 

L2_DATA static uint8_t ext[MAX_BUFFER_SIZE]; // External memory buffer (L2)
L1_DATA static uint8_t loc[MAX_BUFFER_SIZE]; // Local memory buffer (TCDM / L1)

typedef enum {L2_TO_L1, L1_TO_L2} test_type_t;

int test_idma(uint32_t size, test_type_t type, uint32_t ext_addr, uint32_t tcdm_addr);

int main(void) {
    if (rt_cluster_id() != 0) {
        printf("Test only runs on cluster 0\n");
        return bench_cluster_forward(0);
    }
    
    int error_count = 0;

    if (get_core_id() == 0) {

        uint32_t size = 5;
        // Test for L2_TO_L1 operation
        for (int i = 0; i < size; i++) {
            error_count += test_idma(size, L2_TO_L1, (uint32_t)ext, (uint32_t)loc);
        }

        // Test for L1_TO_L2 operation
        for (int i = 0; i < size; i++) {
            error_count += test_idma(size, L1_TO_L2, (uint32_t)ext, (uint32_t)loc);
        }
    }

    return error_count;
}

int test_idma(uint32_t size, test_type_t type, uint32_t ext_addr, uint32_t tcdm_addr) {
    volatile uint8_t expected, actual;
    volatile int error = 0;
    volatile unsigned int id;

    if (type == L2_TO_L1) {

        for (uint32_t i = 0; i < size; i++) {
            *(uint8_t *)(ext_addr + i) = (uint8_t)(i & 0xFF);
        }

        memset((void *)tcdm_addr, 0, size + 16);

        id = pulp_idma_memcpy(ext_addr, tcdm_addr, size, IDMA_PROT_AXI, IDMA_PROT_OBI);
    
        /* L2_TO_L1 transaction:
        +----------------+                        +----------------+
        |                |       DMA Transfer     |                |
        |  L2 Memory     | ---------------------> |  L1 Memory     |
        |  (ext buffer)  |   (pulp_idma_memcpy)   |  (loc buffer)  |
        |                |                        |                |
        +----------------+                        +----------------+
        */
    
    } else if (type == L1_TO_L2) {
        // Fill L1 buffer with a pattern
        for (uint32_t i = 0; i < size; i++) {
            *(uint8_t *)(tcdm_addr + i) = (uint8_t)(i & 0xFF);
        }

        // Clear L2
        memset((void *)ext_addr, 0, size + 16);

        // Perform DMA transfer from local memory to external memory
        id = pulp_idma_memcpy(tcdm_addr, ext_addr, size, IDMA_PROT_OBI, IDMA_PROT_AXI);

        /* L1_TO_L2 transaction:
        +----------------+                        +----------------+
        |                |       DMA Transfer     |                |
        |  L2 Memory     | <--------------------- |  L1 Memory     |
        |  (ext buffer)  |   (pulp_idma_memcpy)   |  (loc buffer)  |
        |                |                        |                |
        +----------------+                        +----------------+
        */
    } else {
        printf("Invalid test type. It must be either L2_TO_L1 or L1_TO_L2.\n");
        return 1;
    }

    plp_dma_barrier();

    // Verify data
    for (uint32_t i = 0; i < size; i++) {
        expected = (uint8_t)(i & 0xFF); // Same pattern as L2_TO_L1
        if (type == L2_TO_L1) {
            // Reading from the local memory buffer "loc" allocated in L1 memory
            actual = *(uint8_t *)(tcdm_addr + i);
        } else { // L1_TO_L2
            // Reading from the external memory buffer "ext" allocated in L2 memory
            actual = *(uint8_t *)(ext_addr + i);
        } 

        if (expected != actual) {
            printf("Error at index %u: Expected 0x%02X, Got 0x%02X\n", i, expected, actual);
            error++;
        }
    }

    if (error == 0) {
        printf("Test passed for %s of length %u.\n", type == L2_TO_L1 ? "L2_TO_L1" : "L1_TO_L2", size);
    } else {
        printf("Test failed for %s of length %u with %u errors.\n", type == L2_TO_L1 ? "L2_TO_L1" : "L1_TO_L2", size, error);
    }
    
    return error;
}