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


/**
 * @brief	Получение текущего значения счётчика ядра микропроцессора
 *
 * @return	uint64_t - Значение счётчика
 */
__weak uint64_t HAL_GetCpuClock(void);


/**
 * @brief	Получение времени работы микропроцессора в милисекундах
 *
 * @return	uint32_t - Время работы микропроцессора в мс
 */
__weak uint32_t HAL_GetCpuTimeMs(void);


/**
 * @brief	Получение времени работы микропроцессора в микросекундах
 *
 * @return	uint32_t - Время работы микропроцессора в мкс
 */
__weak uint32_t HAL_GetCpuTimeMcs(void);


/**
 * @brief	Блокирующая задержка
 *
 * @param	DelayMs - Задержка в мс
 */
__weak void HAL_Delay(uint32_t DelayMs);


/**
 * @brief	Блокирующая задержка
 *
 * @param	DelayMs - Задержка в мкс
 */
__weak void HAL_DelayMcs(uint32_t DelayMcs);


/**
 * @brief	Инициализация ядра микропроцессора
 */
void HAL_InitClock();


#ifdef __cplusplus
}
#endif

#endif