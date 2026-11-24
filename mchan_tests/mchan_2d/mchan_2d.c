#include "mchan_2d.h"

#define TOT_SIZE 8 * CORE_SPACE
#define NB_PRESETS 13

int errors[8] = {0};
int test_status = 8;

uint32_t l1_addr[8] = {0};
uint32_t l2_addr[8] = {0};
uint32_t l1_dst_addr[8] = {0};

int mchan_2d(transfer_2d transfer_params, int core_id, int ext2loc) {
    int error = 0;
    volatile uint8_t *l1_ptr, *l2_ptr;
    uint32_t offset_2d;

    // Adapting transfer parameters
    uint32_t num_reps = 0;
    uint32_t size = transfer_params.size_2d;
    
    uint32_t l1_stride = transfer_params.l1_stride_2d;
    uint32_t l1_length = transfer_params.l1_length_2d;
    uint32_t l2_stride = transfer_params.l2_stride_2d;
    uint32_t l2_length = transfer_params.l2_length_2d;

    if (ext2loc == 1) {
        l1_stride = transfer_params.l1_stride_2d;
        l1_length = transfer_params.l1_length_2d;
        num_reps = size / l1_length;
        l2_stride = 1;
        l2_length = 1;
    } else {
        l1_stride = 1;
        l1_length = 1;
        l2_stride = transfer_params.l2_stride_2d;
        l2_length = transfer_params.l2_length_2d;
        num_reps = size / l2_length;
    }

    l1_ptr = (uint8_t*) l1_addr[core_id];
    l2_ptr = (uint8_t*) l2_addr[core_id];
    int j = 0;

    // Filling L1 and L2 regions with test data
    for (int i = 0; i < CORE_SPACE; i++) {
        l1_ptr[i] = (uint8_t)(i & 0xFF);
        l2_ptr[i] = (uint8_t)((i+1) & 0xFF);
    }

    PRINTF ("Passing parameters: \n");
    if (ext2loc==1) {
        PRINTF ("TRANSFER TOWARDS L1 --> L1_Addr: 0x%8x | L2_Addr: 0x%8x | Size: %d | Stride: %d | Length: %d \n", 
            l1_addr[core_id], l2_addr[core_id], size, l1_stride, l1_length);    
    } else {
        PRINTF ("TRANSFER TOWARDS L2 --> L1_Addr: 0x%8x | L2_Addr: 0x%8x | Size: %d | Stride: %d | Length: %d \n", 
            l1_addr[core_id], l2_addr[core_id], size, l2_stride, l2_length);    
    }

    if (ext2loc==1) {
        reset_cycle_count();
        start_cycle_count();
        plp_mchan_wait(plp_mchan_extToL1_2d(l1_addr[core_id], l2_addr[core_id], size, l1_stride, l1_length));
        stop_cycle_count();
    } else {
        reset_cycle_count();
        start_cycle_count();
        plp_mchan_wait(plp_mchan_l1ToExt_2d(l2_addr[core_id], l1_addr[core_id], size, l2_stride, l2_length));
        stop_cycle_count();
    }
    print_perf();

    // Check the results
    if (ext2loc == 1) {
        // Contiguous access in L2 | Strided access to L1
        int rep_counter = 0;
        int length_counter = 0;
        for (int i = 0; i < size; i++) {
            uint32_t l1_idx = length_counter + rep_counter * l1_stride;
            uint32_t l2_idx = i;
            if (length_counter == (l1_length-1)) {
                length_counter = 0;
                rep_counter ++;
            } else {
                length_counter ++;
            }
            if (l1_ptr[l1_idx] != l2_ptr[l2_idx]) {
                error++;
                if (core_id == 0) {
                    PRINTF ("ERROR: L1[%d] @%8x = %8x vs L2[%d] @%8x = %8x \n", l1_idx, &l1_ptr[l1_idx], 
                            l1_ptr[l1_idx], l2_idx, &l2_ptr[l2_idx], l2_ptr[l2_idx]);
                }
            }
        }
    } else {
        // Contiguous access in L1 | Strided access to L2
        int rep_counter = 0;
        int length_counter = 0;
        for (int i = 0; i < size; i++) {
            uint32_t l1_idx = i;
            uint32_t l2_idx = length_counter + rep_counter * l2_stride;
            if (length_counter == (l2_length-1)) {
                length_counter = 0;
                rep_counter ++;
            } else {
                length_counter ++;
            }

            if (l1_ptr[l1_idx] != l2_ptr[l2_idx]) {
                error++;
                if (core_id == 0) {
                    PRINTF ("ERROR: L1[%d] @%8x = %8x vs L2[%d] @%8x = %8x \n", l1_idx, &l1_ptr[l1_idx], 
                            l1_ptr[l1_idx], l2_idx, &l2_ptr[l2_idx], l2_ptr[l2_idx]);
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

    if (core_id == 0) {
        l1_addr[0]     = (uint32_t) pi_l1_malloc(0, TOT_SIZE);
        l1_dst_addr[0] = (uint32_t) pi_l1_malloc(0, TOT_SIZE);
        l2_addr[0]     = (uint32_t) pi_l2_malloc(TOT_SIZE);
    }
    synch_barrier();
    // The following rt_team_barrier is needed so that
    // no core can assign its address range until the mallocs are executed

    l1_addr[core_id] = l1_addr[0] + core_id * CORE_SPACE;
    l1_dst_addr[core_id] = l1_dst_addr[0] + core_id * CORE_SPACE;
    l2_addr[core_id] = l2_addr[0] + core_id * CORE_SPACE;

    PRINTF ("Core %d: l1_addr = %8x \n", core_id, l1_addr[core_id]);
    PRINTF ("Core %d: l1_dst_addr = %8x \n", core_id, l1_dst_addr[core_id]);
    PRINTF ("Core %d: l2_addr = %8x \n", core_id, l2_addr[core_id]);

    // The following rt_team_barrier is needed so that
    // no core can start executing until all address ranges have been assigned
    synch_barrier();
}

void free_allocated_memory () {
    synch_barrier();
    // Only Core 0 takes care of freeing the allocated memory, since it's the one
    // allocated it at the beginning of the test
    if (rt_core_id() == 0) {
        pi_l1_free(0, l1_addr, TOT_SIZE);
        pi_l1_free(0, l1_dst_addr, TOT_SIZE);
        pi_l2_free(l2_addr, TOT_SIZE);
    }
}

int cluster_task() {
    int core_id = rt_core_id();
    unsigned int size = 0;

    allocate_mem_to_cores();

    #ifdef MULTI_CORE_P
        // MULTI CORE PARALLEL MODE: each core uses the MCHAN in a parallel manner
        if (core_id == 0) {
            PRINTF ("MULTI CORE PARALLEL MODE \n");
        }
        for (int k = 0; k < NB_TRANSFERS; k++) {
            size = params_2d[k].size_2d;
            if (core_id == 0){
                PRINTF ("Size: %d \n", size);
            }
            // MCHAN 1D L1 -> L2
            if (core_id==0) {
                PRINTF ("L1 -> L2: Transfer %d with size %d \n", k, size);
            }
            errors[core_id] += mchan_2d(params_2d[k], rt_core_id(), 0);
            // MCHAN 1D L2 -> L1
            if (core_id==0) {
                PRINTF ("L2 -> L1: Transfer %d with size %d \n", k, size);
            }
            errors[core_id] += mchan_2d(params_2d[k], rt_core_id(), 1);
        }
        synch_barrier();
    #elif MULTI_CORE_S
        // MULTI CORE SERIAL MODE: each core uses the MCHAN in a serial manner
        if (core_id == 0) {
            PRINTF ("MULTI CORE SERIAL MODE \n");
        }
        for (int i = 0; i < 8; i++) {
            if (core_id == i) {
                for (int k = 0; k < NB_TRANSFERS; k++) {
                    size = params_2d[k].size_2d;
                    if (core_id == 0){
                        PRINTF ("Size: %d \n", size);
                    }
                    // MCHAN 1D L1 -> L2
                    if (core_id==0) {
                        PRINTF ("L1 -> L2: Transfer %d with size %d \n", k, size);
                    }
                    errors[core_id] += mchan_2d(params_2d[k], rt_core_id(), 0);
                    // MCHAN 1D L2 -> L1
                    if (core_id==0) {
                        PRINTF ("L2 -> L1: Transfer %d with size %d \n", k, size);
                    }
                    errors[core_id] += mchan_2d(params_2d[k], rt_core_id(), 1);
                }
            }
            synch_barrier();
        }
    #else
        if (core_id == 0) {
            // SINGLE CORE MODE: just core 0 uses the MCHAN
            PRINTF ("SINGLE CORE MODE: CORE 0 \n");
            for (int k = 0; k < NB_TRANSFERS; k++) {
                size = params_2d[k].size_2d;
                if (core_id == 0){
                    PRINTF ("Size: %d \n", size);
                }
                // MCHAN 1D L1 -> L2
                if (core_id==0) {
                    PRINTF ("L1 -> L2: Transfer %d with size %d \n", k, size);
                }
                errors[core_id] += mchan_2d(params_2d[k], rt_core_id(), 0);
                // MCHAN 1D L2 -> L1
                if (core_id==0) {
                    PRINTF ("L2 -> L1: Transfer %d with size %d \n", k, size);
                }
                errors[core_id] += mchan_2d(params_2d[k], rt_core_id(), 1);
            }
        }
    #endif

    if (core_id == 0) {
        for (int i = 0; i<8; i++) {
            if (errors[i] == 0) {
                PRINTF ("Core %d returned %d errors \n", i, errors[i]);
                test_status--;
            }
        }
    }

    free_allocated_memory();

    return test_status;
}

int main () {
    int retval = 1;
    #ifdef ARCHI_HAS_FC
    PRINTF ("Fabric Controller calling cluster task \n");
    if (rt_cluster_id() != 0)
        return bench_cluster_forward(0);
    #endif
    retval = cluster_task();

    return retval;
}