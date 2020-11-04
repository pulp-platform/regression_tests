#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stddef.h>
#include "pulp.h"

#define __sram RT_LOCAL_DATA

#ifdef __cplusplus
extern "C" {
#endif

uint32_t crc32(const void *src, size_t len);

#include "string.h"

#ifdef __cplusplus
}
#endif

#endif
