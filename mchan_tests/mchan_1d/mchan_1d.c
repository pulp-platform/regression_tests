#include "mchan_1d.h"

#define TOT_SIZE 8 * CORE_SPACE
#define NB_PRESETS 13

int errors[8] = {0};
int test_status = 8;

uint32_t l1_addr[8] = {0};
uint32_t l2_addr[8] = {0};
uint32_t l1_dst_addr[8] = {0};

int mchan_1d(unsigned int size, int core_id, int ext2loc) {
    int error = 0;
    volatile uint8_t *l1_ptr, *l2_ptr;

    l1_ptr = (uint8_t*) l1_addr[core_id];
    l2_ptr = (uint8_t*) l2_addr[core_id];

    for (int i = 0; i < size; i++) {
        l1_ptr[i] = (uint8_t)(i & 0xFF);
    }

    for (int i = 0; i < size; i++) {
        l2_ptr[i] = (uint8_t)((size-i) & 0xFF);
    }

    reset_cycle_count();
    start_cycle_count();
    printf ("Launching transfer with L2_addr: %8x | L1_addr: %8x | size: %d | ext2loc: %d \n", l2_addr[core_id], l1_addr[core_id], size, ext2loc);
    plp_mchan_wait(plp_mchan_memcpy(l2_addr[core_id], l1_addr[core_id], size, ext2loc));
    stop_cycle_count();

    // Check the results

    for (int i=0; i < size; i++) {
        uint8_t l1_result = l1_ptr[i]; 
        uint8_t l2_result = l2_ptr[i];
        if (l1_result != l2_result) {
            error++;
            if (core_id == 0) {
                PRINTF ("Error: l1_result @%8x = %8x vs l2_result @%8x = %8x \n", &l1_ptr[i], l1_result, &l2_ptr[i], l2_result);
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

    if (core_id == 0) {
        for (int i = 0; i < 8; i++) {
            PRINTF ("Core %d: l1_addr[%d] = %8x \n", core_id, i, l1_addr[i]);
            PRINTF ("Core %d: l1_dst_addr[%d] = %8x \n", core_id, i, l1_dst_addr[i]);
            PRINTF ("Core %d: l2_addr[%d] = %8x \n", core_id, i, l2_addr[i]);
        }
    }

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
            size = params_1d[k].size_1d;
            if (core_id == 0){
                PRINTF ("Size: %d \n", size);
            }
            // MCHAN 1D L1 -> L2
            if (core_id==0) {
                PRINTF ("L1 -> L2: Transfer %d with size %d \n", k, size);
            }
            errors[core_id] += mchan_1d(size, rt_core_id(), 0);
            // MCHAN 1D L2 -> L1
            if (core_id==0) {
                PRINTF ("L2 -> L1: Transfer %d with size %d \n", k, size);
            }
            errors[core_id] += mchan_1d(size, rt_core_id(), 1);
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
                    size = params_1d[k].size_1d;
                    if (core_id == 0){
                        PRINTF ("Size: %d \n", size);
                    }
                    // MCHAN 1D L1 -> L2
                    if (core_id==0) {
                        PRINTF ("L1 -> L2: Transfer %d with size %d \n", k, size);
                    }
                    errors[core_id] += mchan_1d(size, rt_core_id(), 0);
                    // MCHAN 1D L2 -> L1
                    if (core_id==0) {
                        PRINTF ("L2 -> L1: Transfer %d with size %d \n", k, size);
                    }
                    errors[core_id] += mchan_1d(size, rt_core_id(), 1);
                }
            }
            synch_barrier();
        }
    #else
        if (core_id == 0) {
            // SINGLE CORE MODE: just core 0 uses the MCHAN
            PRINTF ("SINGLE CORE MODE: CORE 0 \n");
            for (int k = 0; k < NB_TRANSFERS; k++) {
                size = params_1d[k].size_1d;
                if (core_id == 0){
                    PRINTF ("Size: %d \n", size);
                }
                // MCHAN 1D L1 -> L2
                PRINTF ("L1 -> L2: Transfer %d with size %d \n", k, size);
                errors[core_id] += mchan_1d(size, rt_core_id(), 0);
                // MCHAN 1D L2 -> L1
                PRINTF ("L2 -> L1: Transfer %d with size %d \n", k, size);
                errors[core_id] += mchan_1d(size, rt_core_id(), 1);
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