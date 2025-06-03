#include "idma_multi_core_3d.h"

#define MAX_BUFFER_SIZE 0x1000
#define CORE_SPACE 0x1000

L2_DATA static uint8_t ext[MAX_BUFFER_SIZE];
L1_DATA static uint8_t loc[MAX_BUFFER_SIZE];
L1_DATA static uint8_t loc_dst[MAX_BUFFER_SIZE];

int errors[8] = {0};
int test_status = 0;

int test_idma_3D (int core_id, uint32_t size, int ext2loc, int loc2loc, uint32_t ext_addr, uint32_t tcdm_addr, unsigned int length, unsigned int src_stride_2d, unsigned int dst_stride_2d, unsigned int num_reps, unsigned int src_stride_3d, unsigned int dst_stride_3d, unsigned int num_reps_3d) {
    volatile uint8_t *src_ptr, *dst_ptr;
    unsigned int offset_3d, offset_2d;

    int error = 0;

    if (loc2loc == 1) {
        // L1 to L1 transfer
        src_ptr = (uint8_t*) tcdm_addr;
        dst_ptr = (uint8_t*) ext_addr;

        // Fill source region with test data
        offset_2d = 0;
        offset_3d = 0;
        for (int j = 0; j < num_reps_3d; j++) {
            for (int q = 0; q < num_reps; q++) {
                for (int i = 0; i < length; i++) {
                    src_ptr[i+offset_2d+offset_3d] = (uint8_t)(i & 0xFF);
                }
                offset_2d += src_stride_2d;
            }
            offset_2d = 0;
            offset_3d += (num_reps-1) * src_stride_2d + src_stride_3d;
        }

        plp_cl_dma_wait_toL1(pulp_cl_idma_L1ToL1_3d((unsigned int)src_ptr, (unsigned int)dst_ptr, length, src_stride_2d, dst_stride_2d, num_reps, src_stride_3d, dst_stride_3d, num_reps_3d));

    } else {
        if (ext2loc == 1) {

            // L2 to L1 transfer
            src_ptr = (uint8_t*) ext_addr;
            dst_ptr = (uint8_t*) tcdm_addr;

            // Fill source region with test data
            offset_2d = 0;
            offset_3d = 0;
            for (int j = 0; j < num_reps_3d; j++) {
                for (int q = 0; q < num_reps; q++) {
                    for (int i = 0; i < length; i++) {
                        src_ptr[i+offset_2d+offset_3d] = (uint8_t)(i & 0xFF);
                    }
                    offset_2d += src_stride_2d;
                }
                offset_2d = 0;
                offset_3d += (num_reps-1) * src_stride_2d + src_stride_3d;
            }

            plp_cl_dma_wait_toL1(pulp_cl_idma_L2ToL1_3d((unsigned int)src_ptr, (unsigned int)dst_ptr, length, src_stride_2d, dst_stride_2d, num_reps, src_stride_3d, dst_stride_3d, num_reps_3d));
        } else {

            // L1 to L2 transfer
            src_ptr = (uint8_t*) tcdm_addr;
            dst_ptr = (uint8_t*) ext_addr;

            // Fill source region with test data
            offset_2d = 0;
            offset_3d = 0;
            for (int j = 0; j < num_reps_3d; j++) {
                for (int q = 0; q < num_reps; q++) {
                    for (int i = 0; i < length; i++) {
                        src_ptr[i+offset_2d+offset_3d] = (uint8_t)(i & 0xFF);
                    }
                    offset_2d += src_stride_2d;
                }
                offset_2d = 0;
                offset_3d += (num_reps-1) * src_stride_2d + src_stride_3d;
            }

            plp_cl_dma_wait_toL2(pulp_cl_idma_L1ToL2_3d((unsigned int)src_ptr, (unsigned int)dst_ptr, length, src_stride_2d, dst_stride_2d, num_reps, src_stride_3d, dst_stride_3d, num_reps_3d));
        }
    }

    // Check the results
    int src_offset_2d = 0;
    int dst_offset_2d = 0;
    int src_offset_3d = 0;
    int dst_offset_3d = 0;

    for (int rep_3d = 0; rep_3d < num_reps_3d; rep_3d ++) {
        for (unsigned int rep = 0; rep < num_reps; rep++) {
            for (unsigned int i = 0; i < length; i++) {
                uint8_t expected = src_ptr[src_offset_2d + src_offset_3d + i];
                uint8_t actual   = dst_ptr[dst_offset_2d + dst_offset_3d + i];

                if (expected != actual) {
                    if (core_id == 0) {
                        PRINTF ("ERROR: expected @%8x[%d] = %8x vs actual @%8x[%d] = %8x \n", &src_ptr[src_offset_2d + src_offset_3d + i], src_offset_2d + src_offset_3d + i, expected, &dst_ptr[dst_offset_2d + dst_offset_3d + i], dst_offset_2d + dst_offset_3d + i, actual);
                    }
                    error++;
                }
            }
            src_offset_2d += src_stride_2d;
            dst_offset_2d += dst_stride_2d;
        }
        src_offset_2d = 0;
        dst_offset_2d = 0;
        src_offset_3d += (num_reps-1) * src_stride_2d + src_stride_3d;
        dst_offset_3d += (num_reps-1) * dst_stride_2d + dst_stride_3d;
    }

    return error;
}

int main () {

    int core_id = rt_core_id();

    unsigned int size, length, src_stride_2d, dst_stride_2d;
    unsigned int num_reps_3d, src_stride_3d, dst_stride_3d;
    uint32_t ext_addr;
    uint32_t loc_addr;
    uint32_t loc_dst_addr;

    ext_addr = (uint32_t)ext + core_id * CORE_SPACE;
    loc_addr = (uint32_t)loc + core_id * CORE_SPACE;
    loc_dst_addr = (uint32_t)loc_dst + core_id * CORE_SPACE;

    if (core_id == 0){
        PRINTF ("loc_addr: %8x | loc_dst_addr: %8x \n", loc_addr, loc_dst_addr);
    }

    #ifdef MULTI_CORE_P
        // MULTI CORE PARALLEL MODE: each core uses the iDMA in a parallel manner
        if (core_id == 0) {
            PRINTF ("MULTI CORE PARALLEL MODE \n");
        }
        for (int k = 0; k < NB_TRANSFERS; k++) {
            size = transfer_params[k].size;
            length = transfer_params[k].length;
            src_stride_2d = transfer_params[k].src_stride_2d;
            dst_stride_2d = transfer_params[k].dst_stride_2d;
            src_stride_3d = transfer_params[k].src_stride_3d;
            dst_stride_3d = transfer_params[k].dst_stride_3d;
            num_reps_3d   = transfer_params[k].num_reps_3d;

            if (core_id == 0) {
                PRINTF ("Transfer: %d \n", k);
                PRINTF ("Size: %d | Length: %d | Src_stride_2d: %d | Dst_stride_2d: %d | Num_reps_2d: %d \n", size, length, src_stride_2d, dst_stride_2d, (size/length));
                PRINTF ("Src_stride_3d: %d | Dst_stride_3d: %d | Num_reps_3d: %d \n", src_stride_3d, dst_stride_3d, num_reps_3d);
            }
            errors[core_id] += test_idma_3D(core_id, size, (core_id%2), 0, ext_addr, loc_addr, length, src_stride_2d, dst_stride_2d, (size/length), src_stride_3d, dst_stride_3d, num_reps_3d);
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
                    src_stride_2d = transfer_params[k].src_stride_2d;
                    dst_stride_2d = transfer_params[k].dst_stride_2d;
                    src_stride_3d = transfer_params[k].src_stride_3d;
                    dst_stride_3d = transfer_params[k].dst_stride_3d;
                    num_reps_3d   = transfer_params[k].num_reps_3d;
                    if (core_id == 0) {
                        PRINTF ("Transfer: %d \n", k);
                        PRINTF ("Size: %d | Length: %d | Src_stride_2d: %d | Dst_stride_2d: %d | Num_reps_2d: %d \n", size, length, src_stride_2d, dst_stride_2d, (size/length));
                        PRINTF ("Src_stride_3d: %d | Dst_stride_3d: %d | Num_reps_3d: %d \n", src_stride_3d, dst_stride_3d, num_reps_3d);
                    }
                    errors[core_id] += test_idma_3D(core_id, size, (core_id%2), 0, ext_addr, loc_addr, length, src_stride_2d, dst_stride_2d, (size/length), src_stride_3d, dst_stride_3d, num_reps_3d);
                }
            }
        }
    #else
        if (core_id == 0) {
            for (int k = 0; k < NB_TRANSFERS; k++) {
                size = transfer_params[k].size;
                length = transfer_params[k].length;
                src_stride_2d = transfer_params[k].src_stride_2d;
                dst_stride_2d = transfer_params[k].dst_stride_2d;
                src_stride_3d = transfer_params[k].src_stride_3d;
                dst_stride_3d = transfer_params[k].dst_stride_3d;
                num_reps_3d   = transfer_params[k].num_reps_3d;
                PRINTF ("Transfer: %d \n", k);
                PRINTF ("Size: %d | Length: %d | Src_stride_2d: %d | Dst_stride_2d: %d | Num_reps_2d: %d \n", size, length, src_stride_2d, dst_stride_2d, (size/length));
                PRINTF ("Src_stride_3d: %d | Dst_stride_3d: %d | Num_reps_3d: %d \n", src_stride_3d, dst_stride_3d, num_reps_3d);
                PRINTF ("L1 to L2 transfer \n");
                errors[core_id] += test_idma_3D(core_id, size, 0, 0, ext_addr, loc_addr, length, src_stride_2d, dst_stride_2d, (size/length), src_stride_3d, dst_stride_3d, num_reps_3d);
                PRINTF ("L2 to L1 transfer \n");
                errors[core_id] += test_idma_3D(core_id, size, 1, 0, ext_addr, loc_addr, length, src_stride_2d, dst_stride_2d, (size/length), src_stride_3d, dst_stride_3d, num_reps_3d);
                PRINTF ("L1 to L1 transfer \n");
                errors[core_id] += test_idma_3D(core_id, size, 0, 1, loc_dst_addr, loc_addr, length, src_stride_2d, dst_stride_2d, (size/length), src_stride_3d, dst_stride_3d, num_reps_3d);
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