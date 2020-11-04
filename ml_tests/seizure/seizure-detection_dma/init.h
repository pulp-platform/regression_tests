#ifndef __INIT_H__
#define __INIT_H__


#include <stdint.h>

#define channels 23 
#define window 256

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "bench.h"

//#include "archi/mchan_v5.h"
#define HWPERF 1
#define HWPERF_FUNC 1
//#define HWPERFMALLOC 1
//#define HWPERFFREE 1
//#define DEBUG

//#define FAKEDMA

static inline uint32_t
memcpy_async(void *dst, void *src, uint32_t size)
{
        uint32_t dmaId = -1;
        
        #ifdef FAKEDMA
        uint32_t i;
        for(i=0; i<size; i++) {
                ((uint8_t *) dst) [i] = ((uint8_t *) src) [i];
        }
        #else
        #if MCHAN_VERSION <= 3
        mchan_memcpy_async((uint32_t) dst, (uint32_t) src, size);
        #else
        if (L2_MEM_BASE_ADDR <= (int) dst)
	  dmaId = plp_dma_memcpy( (int) dst, (int)src, size, 0);
	else
	  dmaId = plp_dma_memcpy( (int) src, (int) dst, size, 1);
        #endif
        #endif
        
        return dmaId;
}

static inline uint32_t
memcpy_async2D(void *dst, void *src, uint32_t size, uint32_t stride, uint32_t lenght)
{
        uint32_t dmaId = -1;
        
        #if defined(FAKEDMA) || MCHAN_VERSION < 5
        uint32_t i;
        uint32_t idx;
        uint32_t idy;
        for(i=0; i<size; i++) {
                idy = i / lenght;
                idx = i % lenght;
                ((uint8_t *) dst) [i] = ((uint8_t *) src) [idy*stride+idx];
        }
        #else
	if (L2_MEM_BASE_ADDR <= (int) dst)
	  dmaId = plp_dma_memcpy_2d( (int) dst, (int)src, size, stride, lenght, 0);
	else
	  dmaId = plp_dma_memcpy_2d( (int) src, (int) dst, size, stride, lenght, 1);
        #endif
        
        return dmaId;
}

static inline void
memcpy_wait(uint32_t job_id)
{
        #ifndef FAKEDMA
        plp_dma_wait( job_id);
        #endif
        return;
}

static inline void
memcpy_(void *dst, void *src, uint32_t size)
{    
        #ifndef FAKEDMA
        memcpy_wait(memcpy_async(dst, src, size));
        #endif
        return;
}
#endif

