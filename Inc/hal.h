#ifndef HAL_CFG_H
#define HAL_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

#include <csr.h>
#include <scr1_csr_encoding.h>

#include <mcu32_memory_map.h>
#include <power_manager.h>

#include "hal_types.h"


#define CPU_CLOCK_MHZ        32


typedef enum {
	HAL_OK,
	HAL_BUSY,
	HAL_ERROR
} HAL_StatusTypeDef;


uint64_t __div64_32(uint64_t rem, uint32_t base);


__weak uint64_t HAL_GetCpuClock(void);


__weak uint32_t HAL_GetCpuTimeMs(void);


__weak uint32_t HAL_GetCpuTimeMcs(void);


__weak void HAL_Delay(uint32_t DelayMs);


__weak void HAL_DelayMcs(uint32_t DelayMcs);


void HAL_InitClock();


#ifdef __cplusplus
}
#endif

#endif