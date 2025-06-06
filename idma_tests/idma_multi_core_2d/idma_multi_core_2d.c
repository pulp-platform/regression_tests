#include "idma_multi_core_2d.h"

#define CORE_SPACE 0x500
#define MAX_BUFFER_SIZE CORE_SPACE

L2_DATA static uint8_t ext[MAX_BUFFER_SIZE];
L1_DATA static uint8_t loc[MAX_BUFFER_SIZE];
L1_DATA static uint8_t loc_dst[MAX_BUFFER_SIZE];

int errors[8] = {0};
int test_status = 0;

int test_idma_2D (int core_id, uint32_t size, int ext2loc, int loc2loc, uint32_t ext_addr, uint32_t tcdm_addr, unsigned int length, unsigned int src_stride, unsigned int dst_stride, unsigned int num_reps) {
    volatile uint8_t *src_ptr, *dst_ptr;

    int error = 0;
    int offset_2d;
    if (loc2loc == 1) {
        // L1 to L1 transfer
        src_ptr = (uint8_t*) tcdm_addr;
        dst_ptr = (uint8_t*) ext_addr;

        // Fill source region with test data
        for (int q = 0; q < num_reps; q++) {
            offset_2d = q * src_stride;
            for (int i = 0; i < length; i++) {
                src_ptr[i+offset_2d] = (uint8_t)(i & 0xFF);
            }
        }
        plp_cl_dma_wait_toL1(pulp_cl_idma_L1ToL1_2d((unsigned int)src_ptr, (unsigned int)dst_ptr, length, src_stride, dst_stride, num_reps));
    } else {
        if (ext2loc == 1) {

            // L2 to L1 transfer
            src_ptr = (uint8_t*) ext_addr;
            dst_ptr = (uint8_t*) tcdm_addr;

            // Fill source region with test data
            for (int q = 0; q < num_reps; q++) {
                offset_2d = q * src_stride;
                for (int i = 0; i < length; i++) {
                    src_ptr[i+offset_2d] = (uint8_t)(i & 0xFF);
                }
            }
            plp_cl_dma_wait_toL1(pulp_cl_idma_L2ToL1_2d((unsigned int)src_ptr, (unsigned int)dst_ptr, length, src_stride, dst_stride, num_reps));
        } else {

            // L1 to L2 transfer
            src_ptr = (uint8_t*) tcdm_addr;
            dst_ptr = (uint8_t*) ext_addr;

            // Fill source region with test data
            for (int q = 0; q < num_reps; q++) {
                offset_2d = q * src_stride;
                for (int i = 0; i < length; i++) {
                    src_ptr[i+offset_2d] = (uint8_t)(i & 0xFF);
                }
            }
            plp_cl_dma_wait_toL2(pulp_cl_idma_L1ToL2_2d((unsigned int)src_ptr, (unsigned int)dst_ptr, length, src_stride, dst_stride, num_reps));
        }
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
                    PRINTF ("ERROR: expected[%d] @%8x = %8x vs actual[%d] @%8x = %8x \n", src_offset + i, &src_ptr[src_offset + i], expected, dst_offset+i, &dst_ptr[dst_offset + i], actual);
                }
            }

        }
    }
    
    return error;
}

int main () {

    int core_id = rt_core_id();

    unsigned int size, length, src_stride, dst_stride;
    uint32_t ext_addr;
    uint32_t loc_addr;
    uint32_t loc_dst_addr;

    ext_addr = (uint32_t)ext + core_id * CORE_SPACE;
    loc_addr = (uint32_t)loc + core_id * CORE_SPACE;
    loc_dst_addr = (uint32_t)loc_dst + core_id * CORE_SPACE;

    if (core_id == 0){
    PRINTF ("loc_addr: %8x | loc_dst_addr: %8x | ext_addr: %8x \n", loc_addr, loc_dst_addr, ext_addr);
    }

    #ifdef MULTI_CORE_P
        // MULTI CORE PARALLEL MODE: each core uses the iDMA in a parallel manner
        if (core_id == 0) {
            PRINTF ("MULTI CORE PARALLEL MODE \n");
        }
        for (int k = 0; k < NB_TRANSFERS; k++) {
            size = transfer_params[k].size;
            length = transfer_params[k].length;
            src_stride = transfer_params[k].src_stride;
            dst_stride = transfer_params[k].dst_stride;
            if (core_id == 0) {
                PRINTF ("Transfer: %d | Size: %d | Length: %d | Src_stride: %d | Dst_stride: %d | Num_reps: %d \n", k, size, length, src_stride, dst_stride, (size/length));
            }
            // L1 -> L2
            errors[core_id] += test_idma_2D(core_id, size, 0, 0, ext_addr, loc_addr, length, src_stride, dst_stride, size/length);
            // L2 -> L1
            errors[core_id] += test_idma_2D(core_id, size, 1, 0, ext_addr, loc_addr, length, src_stride, dst_stride, size/length);
            // L1 -> L1
            errors[core_id] += test_idma_2D(core_id, size, 0, 1, loc_dst_addr, loc_addr, length, src_stride, dst_stride, size/length);
            synch_barrier();
        }
    #elif MULTI_CORE_S
        // MULTI CORE SERIAL MODE: each core uses the iDMA in a serial manner
        if (core_id == 0) {
            PRINTF ("MULTI CORE SERIAL MODE \n");
        }
        for (int i = 0; i < 8; i++) {
            if (core_id == i) {
                for (int k = 0; k < NB_TRANSFERS; k++) {
                    size = transfer_params[k].size;
                    length = transfer_params[k].length;
                    src_stride = transfer_params[k].src_stride;
                    dst_stride = transfer_params[k].dst_stride;
                    if (core_id == 0) {
                        PRINTF ("Transfer: %d | Size: %d | Length: %d | Src_stride: %d | Dst_stride: %d | Num_reps: %d \n", k, size, length, src_stride, dst_stride, (size/length));
                    }
                    // L1 -> L2
                    errors[core_id] += test_idma_2D(core_id, size, 0, 0, ext_addr, loc_addr, length, src_stride, dst_stride, size/length);
                    // L2 -> L1
                    errors[core_id] += test_idma_2D(core_id, size, 1, 0, ext_addr, loc_addr, length, src_stride, dst_stride, size/length);
                    // L1 -> L1
                    errors[core_id] += test_idma_2D(core_id, size, 0, 1, loc_dst_addr, loc_addr, length, src_stride, dst_stride, size/length);
                }
            }
       }
    #else
        // SINGLE CORE MODE: just core 0 uses the iDMA
        if (core_id == 0) {
            PRINTF ("SINGLE CORE MODE \n");
            for (int k = 0; k < NB_TRANSFERS; k++) {
                size = transfer_params[k].size;
                length = transfer_params[k].length;
                src_stride = transfer_params[k].src_stride;
                dst_stride = transfer_params[k].dst_stride;
                PRINTF ("Transfer: %d \n", k);
                PRINTF ("Size: %d | Length: %d | Src_stride: %d | Dst_stride: %d | Num_reps: %d \n", size, length, src_stride, dst_stride, (size/length));
                PRINTF ("L1 to L2 \n");
                errors[core_id] += test_idma_2D(core_id, size, 0, 0, ext_addr, loc_addr, length, src_stride, dst_stride, (size/length));
                PRINTF ("L2 to L1 \n");
                errors[core_id] += test_idma_2D(core_id, size, 1, 0, ext_addr, loc_addr, length, src_stride, dst_stride, (size/length));
                PRINTF ("L1 to L1 \n");
                errors[core_id] += test_idma_2D(core_id, size, 0, 1, loc_dst_addr, loc_addr, length, src_stride, dst_stride, (size/length));
            }
        }
    #endif
    if (core_id == 0) {
        for (int i = 0; i<8; i++) {
            if (errors[i] !=0) {
                PRINTF ("Core %d returned %d errors \n", i, errors[i]);
                test_status = 1;
            }
        }
    }

    return test_status;
}