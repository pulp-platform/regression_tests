#include "test.h"

int errors = 0;

uint32_t l1_addr[2] = {0};
uint32_t l2_addr[2] = {0};

// Tests a L2 -> L1 transfer
int test_mchan_rx (int core_id, int size) {
    PRINTF ("RX TESTCASE --> Transfer from L2 to L1 \n");
    volatile uint8_t *src_ptr, *dst_ptr;
    int error = 0;

    // L2 to L1 transfer
    src_ptr = (uint8_t*) l2_addr[1];
    dst_ptr = (uint8_t*) l1_addr[1];

    // Fill source region with test data
    for (int i = 0; i < size; i++) {
        src_ptr[i] = (uint8_t)(i & 0xFF);
        dst_ptr[i] = (uint8_t)((i-1)&0xFF);
    }

    reset_cycle_count();
    start_cycle_count();
    for (int i=0; i<TRANSFERS_QUEUE; i++) {
        plp_mchan_memcpy(l2_addr[1], l1_addr[1], size, 1);
    }
    plp_mchan_barrier();
    stop_cycle_count();

    // Check the results

    #ifdef DISABLE_ERROR_CHECK
    error = 0;
    #else
    for (int i=0; i < size; i++) {
        uint8_t expected = src_ptr[i]; 
        uint8_t actual   = dst_ptr[i];

        if (expected != actual) {
            error++;
            if (core_id == 0) {
                PRINTF ("Error: expected @%8x = %8x vs actual @%8x = %8x \n", expected, &src_ptr[i], actual, &dst_ptr[i]);
            }
        }
    }
    #endif

    return error;
}

// Tests a L1 -> L2 transfer
int test_mchan_tx (int core_id, int size) {
    PRINTF ("TX TESTCASE --> Transfer from L1 to L2 \n");
    volatile uint8_t *src_ptr, *dst_ptr;
    int error = 0;

    // L1 to L2 transfer
    src_ptr = (uint8_t*) l1_addr[0];
    dst_ptr = (uint8_t*) l2_addr[0];

    // Fill source region with test data
    for (int i = 0; i < size; i++) {
        src_ptr[i] = (uint8_t)(i & 0xFF);
        dst_ptr[i] = (uint8_t)((i-1)&0xFF);
    }

    reset_cycle_count();
    start_cycle_count();
    for (int i=0; i<TRANSFERS_QUEUE; i++) {
        plp_mchan_memcpy(l2_addr[0], l1_addr[0], size, 0);
    }
    plp_mchan_barrier();
    stop_cycle_count();

    // Check the results

    #ifdef DISABLE_ERROR_CHECK
    error = 0;
    #else
    for (int i=0; i < size; i++) {
        uint8_t expected = src_ptr[i]; 
        uint8_t actual   = dst_ptr[i];

        if (expected != actual) {
            error++;
            if (core_id == 0) {
                PRINTF ("Error: expected @%8x = %8x vs actual @%8x = %8x \n", expected, &src_ptr[i], actual, &dst_ptr[i]);
            }
        }
    }
    #endif

    return error;
}

// Tests both directions in parallel
int test_mchan_tx_rx (int core_id, int size) {
    PRINTF ("TX & RX TESTCASE --> Transfer from L1 to L2 and from L2 to L1 in parallel \n");
    volatile uint8_t *src_ptr_tx, *dst_ptr_tx;
    volatile uint8_t *src_ptr_rx, *dst_ptr_rx;
    int error = 0;

    // L1 to L2 transfer
    src_ptr_tx = (uint8_t*) l1_addr[0];
    dst_ptr_tx = (uint8_t*) l2_addr[0];

    // L2 to L1 transfer
    src_ptr_rx = (uint8_t*) l2_addr[1];
    dst_ptr_rx = (uint8_t*) l1_addr[1];

    // Fill source region with test data for both transfers --> each will have size TRANSFER_SIZE/2
    for (int i = 0; i < (size); i++) {
        src_ptr_tx[i] = (uint8_t)(i & 0xFF);
        dst_ptr_tx[i] = (uint8_t)((i-1)&0xFF);
        src_ptr_rx[i] = (uint8_t)(i & 0xFF);
        dst_ptr_rx[i] = (uint8_t)((i-1)&0xFF);
    }

    for (int i=0; i<TRANSFERS_QUEUE; i++) {
        plp_mchan_memcpy(l2_addr[0], l1_addr[0], size, 0);
        plp_mchan_memcpy(l2_addr[1], l1_addr[1], size, 1);
    }
    
    plp_mchan_barrier();
    // Check the results

    #ifdef DISABLE_ERROR_CHECK
    error = 0;
    #else
    for (int i=0; i < size; i++) {
        uint8_t expected_tx = src_ptr_tx[i]; 
        uint8_t actual_tx   = dst_ptr_tx[i];
        uint8_t expected_rx = src_ptr_rx[i]; 
        uint8_t actual_rx   = dst_ptr_rx[i];

        if (expected_tx != actual_tx) {
            error++;
            PRINTF ("Error in TX transfer: expected @%8x = %8x vs actual @%8x = %8x \n", expected_tx, &src_ptr_tx[i], actual_tx, &dst_ptr_tx[i]);
        }
        if (expected_rx != actual_rx) {
            error++;
            PRINTF ("Error in RX transfer: expected @%8x = %8x vs actual @%8x = %8x \n", expected_rx, &src_ptr_rx[i], actual_rx, &dst_ptr_rx[i]);
        }
    }
    #endif

    return error;
}

// Tests an idle scenario
int test_mchan_idle (int size) {
    // Here MCHAN does nothing, we just wait.
    volatile uint8_t *src_ptr, *dst_ptr;
    // L1 to L2 transfer
    src_ptr = (uint8_t*) l1_addr[0];
    dst_ptr = (uint8_t*) l2_addr[0];

    for (int i=0; i<size; i++) {
        src_ptr[i] = (uint8_t)(i & 0xFF);
    }

    // Let the core do a transfer instead of the DMA
    for (int i=0; i<size; i++) {
        dst_ptr[i] = src_ptr[i];
    }
    return 0;
}

void allocate_mem_to_cores () {
    int core_id = rt_core_id();

    if (core_id == 0) {
        l1_addr[0]     = (uint32_t) pi_l1_malloc(0, CORE_SPACE);
        l2_addr[0]     = (uint32_t) pi_l2_malloc(CORE_SPACE);
        l1_addr[1]     = (uint32_t) pi_l1_malloc(0, CORE_SPACE);
        l2_addr[1]     = (uint32_t) pi_l2_malloc(CORE_SPACE);
    }

    // The following synch_barrier is needed so that
    // no core can assign its address range until the mallocs are executed
    synch_barrier();

    if (core_id == 0) {
        PRINTF ("Addresses for TX transfer \n");
        PRINTF ("l1_addr = %8x \n", l1_addr[0]);
        PRINTF ("l2_addr = %8x \n", l2_addr[0]);
        PRINTF ("Addresses for RX transfer \n");
        PRINTF ("l1_addr = %8x \n", l1_addr[1]);
        PRINTF ("l2_addr = %8x \n", l2_addr[1]);
    }

    // The following synch_barrier is needed so that
    // no core can start executing until all address ranges have been assigned
    synch_barrier();

}

void free_allocated_memory () {

    synch_barrier();
    // Only Core 0 takes care of freeing the allocated memory, since it's the one
    // allocated it at the beginning of the test
    if (rt_core_id() == 0) {
        pi_l1_free(0, l1_addr, CORE_SPACE);
        pi_l2_free(l2_addr, CORE_SPACE);
    }
}

int cluster_task () {
    int core_id = rt_core_id();
    unsigned int size = TRANSFER_SIZE;

    allocate_mem_to_cores();

    if (core_id == 0){
        #ifdef TX
        errors += test_mchan_tx(core_id, size);
        #endif
        #ifdef RX
        errors += test_mchan_rx(core_id, size);
        #endif
        #ifdef  TX_RX
        errors += test_mchan_tx_rx(core_id, size);
        #endif
        #ifdef IDLE
        errors += test_mchan_idle(size);
        #endif
    }

    synch_barrier();
    free_allocated_memory();

    return errors;
}

int main () {
    int retval = 1;
    retval = cluster_task();
    return retval;
}