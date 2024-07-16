#ifdef NNX_NEUREKA_TESTBENCH
    #include "neureka_testbench_bsp.h"
    #define neureka_bsp_conf_t neureka_testbench_conf_t
    #define neureka_bsp_open neureka_testbench_open
    #define neureka_bsp_close neureka_testbench_close
    #define neureka_bsp_event_wait_and_clear neureka_testbench_event_wait_and_clear
#else
    #include "neureka_siracusa_bsp.h"
    #define neureka_bsp_conf_t neureka_siracusa_conf_t
    #define neureka_bsp_open neureka_siracusa_open
    #define neureka_bsp_close neureka_siracusa_close
    #define neureka_bsp_event_wait_and_clear neureka_siracusa_event_wait_and_clear
#endif