#ifndef HAL_CFG_H
#define HAL_CFG_H

#include <stdlib.h>

#include <csr.h>
#include <scr1_csr_encoding.h>

#include <mcu32_memory_map.h>
#include <power_manager.h>

#include "hal_types.h"


#define CPU_CLOCK_MHZ		32


#define rdtime() read_csr(time)
#define rdcycle() read_csr(cycle)
#define rdinstret() read_csr(instret)


typedef enum {
	HAL_OK,
	HAL_BUSY,
	HAL_ERROR
} HAL_StatusTypeDef;



__weak uint64_t HAL_GetCpuTick(void);


__weak uint32_t HAL_GetCpuTimeMs(void);


__weak uint32_t HAL_GetCpuTimeMcs(void);


__weak void HAL_Delay(uint32_t DelayMs);


void HAL_InitClock();


#endif