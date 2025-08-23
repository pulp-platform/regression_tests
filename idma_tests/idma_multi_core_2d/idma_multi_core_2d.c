#include "idma_multi_core_2d.h"

#define TOT_SIZE 8 * CORE_SPACE

int errors[8] = {0};
int test_status = 8;

uint32_t l1_addr[8] = {0};
uint32_t l1_dst_addr[8] = {0};
uint32_t l2_addr[8] = {0};

void print_transfer (TransferParameters transfer) {
    if (rt_core_id() == 0) {
        PRINTF ("Transfer Parameters: \n");
        PRINTF ("Size: %d | Length: %d \n", transfer.size, transfer.length);
        PRINTF ("Src_stride_2d: %d | Dst_stride_2d: %d \n", transfer.src_stride, transfer.dst_stride);
    }
}

int test_idma_2D (int core_id, TransferParameters transfer, int ext2loc, int loc2loc) {
    volatile uint8_t *src_ptr, *dst_ptr;

    int error = 0;
    int offset_2d;

    uint32_t src_stride = transfer.src_stride;
    uint32_t dst_stride = transfer.dst_stride;
    uint32_t size = transfer.size;
    uint32_t length = transfer.length;
    uint32_t num_reps = size/length;

    if (loc2loc == 1) {
        // L1 to L1 transfer
        src_ptr = (uint8_t*) l1_addr[core_id];
        dst_ptr = (uint8_t*) l1_dst_addr[core_id];
    } else if (ext2loc == 1) {
        // L2 to L1 transfer
        src_ptr = (uint8_t*) l2_addr[core_id];
        dst_ptr = (uint8_t*) l1_addr[core_id];
    } else {
        // L1 to L2 transfer
        src_ptr = (uint8_t*) l1_addr[core_id];
        dst_ptr = (uint8_t*) l2_addr[core_id];
    }

    // Fill source region with test data
    for (int q = 0; q < num_reps; q++) {
        offset_2d = q * src_stride;
        for (int i = 0; i < length; i++) {
            src_ptr[i+offset_2d] = (uint8_t)(i & 0xFF);
        }
    }

    if (loc2loc == 1) {
        plp_cl_dma_wait_toL1(pulp_cl_idma_L1ToL1_2d((unsigned int)src_ptr, (unsigned int)dst_ptr, length, src_stride, dst_stride, num_reps));
    } if (ext2loc == 1) {
        plp_cl_dma_wait_toL1(pulp_cl_idma_L2ToL1_2d((unsigned int)src_ptr, (unsigned int)dst_ptr, length, src_stride, dst_stride, num_reps));
    } else {
        plp_cl_dma_wait_toL2(pulp_cl_idma_L1ToL2_2d((unsigned int)src_ptr, (unsigned int)dst_ptr, length, src_stride, dst_stride, num_reps));
    }

    // Check the results
    
    for (unsigned int rep = 0; rep < num_reps; rep++) {
        unsigned int src_offset = rep * src_stride;
        unsigned int dst_offset = rep * dst_stride;
        for (unsigned int i = 0; i < length; i++) {
            uint8_t expected = src_ptr[src_offset + i];
            uint8_t actual = dst_ptr[dst_offset + i];

            if (expected != actual) {
                error++;
                if (core_id == 0) {
                    PRINTF ("ERROR: expected[%d] @%8x = %8x vs actual[%d] @%8x = %8x \n", src_offset + i, &src_ptr[src_offset + i], 
                            expected, dst_offset+i, &dst_ptr[dst_offset + i], actual);
                }
            }

        }
    }
    
    return error;
}

void allocate_mem_to_cores () {
    int core_id = rt_core_id();

    // Pre-allocate TOT_SIZE = 8 * CORE_SPACE: then we split this window to assign
    // each core its available space for iDMA transfers
    // pi_l1_malloc starts allocating from 0x10004008 in L1
    // pi_l2_malloc starts allocating from 0x1c000a60 in L2

    if (core_id == 0) {
        l1_addr[0]     = (uint32_t) pi_l1_malloc(0, TOT_SIZE);
        l1_dst_addr[0] = (uint32_t) pi_l1_malloc(0, TOT_SIZE);
        l2_addr[0]     = (uint32_t) pi_l2_malloc(TOT_SIZE);
    }

    // The following synch_barrier is needed so that
    // no core can assign its address range until the mallocs are executed
    synch_barrier();

    l1_addr[core_id]     = l1_addr[0] + core_id * CORE_SPACE;
    l1_dst_addr[core_id] = l1_dst_addr[0] + core_id * CORE_SPACE;
    l2_addr[core_id]     = l2_addr[0] + core_id * CORE_SPACE;

    // The following synch_barrier is needed so that
    // no core can start executing until all address ranges have been assigned
    synch_barrier();

}

void free_allocated_memory () {

    synch_barrier();
    // Only Core 0 takes care of freeing the allocated memory, since it's the one
    // allocated it at the beginning of the test
    if (core_id == 0) {
        pi_l1_free(0, l1_addr, TOT_SIZE);
        pi_l1_free(0, l1_dst_addr, TOT_SIZE);
        pi_l2_free(l2_addr, TOT_SIZE);
    }
}

int main () {

    int core_id = rt_core_id();

    allocate_mem_to_cores();

    TransferParameters transfer;

    #ifdef MULTI_CORE_P
        // MULTI CORE PARALLEL MODE: each core uses the iDMA in a parallel manner
        if (core_id == 0) {
            PRINTF ("MULTI CORE PARALLEL MODE \n");
        }
        for (int k = 0; k < TRANSFERS; k++) {
            #ifdef QUICK_MODE
            transfer = idma_presets[k];
            #else
            transfer = transfer_params[k];
            #endif
            print_transfer(transfer);
            // L1 -> L2
            errors[core_id] += test_idma_2D(core_id, transfer, 0, 0);
            // L2 -> L1
            errors[core_id] += test_idma_2D(core_id, transfer, 1, 0);
            // L1 -> L1
            errors[core_id] += test_idma_2D(core_id, transfer, 0, 1);
        }
        synch_barrier();
    #elif MULTI_CORE_S
        // MULTI CORE SERIAL MODE: each core uses the iDMA in a serial manner
        if (core_id == 0) {
            PRINTF ("MULTI CORE SERIAL MODE \n");
        }
        for (int i = 0; i < 8; i++) {
            if (core_id == i) {
                for (int k = 0; k < TRANSFERS; k++) {
                    #ifdef QUICK_MODE
                    transfer = idma_presets[k];
                    #else
                    transfer = transfer_params[k];
                    #endif
                    print_transfer(transfer);
                    // L1 -> L2
                    errors[core_id] += test_idma_2D(core_id, transfer, 0, 0);
                    // L2 -> L1
                    errors[core_id] += test_idma_2D(core_id, transfer, 1, 0);
                    // L1 -> L1
                    errors[core_id] += test_idma_2D(core_id, transfer, 0, 1);
                }
            }
        }
    #else
        // SINGLE CORE MODE: just core 0 uses the iDMA
        if (core_id == 0) {
            PRINTF ("SINGLE CORE MODE \n");
            for (int k = 0; k < TRANSFERS; k++) {
                #ifdef QUICK_MODE
                transfer = idma_presets[k];
                #else
                transfer = transfer_params[k];
                #endif
                print_transfer(transfer);
                // L1 -> L2
                errors[core_id] += test_idma_2D(core_id, transfer, 0, 0);
                // L2 -> L1
                errors[core_id] += test_idma_2D(core_id, transfer, 1, 0);
                // L1 -> L1
                errors[core_id] += test_idma_2D(core_id, transfer, 0, 1);
            }
        }
    #endif

    if (core_id == 0) {
        for (int i = 0; i<8; i++) {
            if (errors[i] == 0) {
                PRINTF ("Core %d returned %d errors \n", i, errors[i]);
                test_status --;
            }
        }
    }

    free_allocated_memory();

    return test_status;
}