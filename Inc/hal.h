/*
 *  Copyright (c) 2022   Author: Столяров Сергей
 *                      Company: НПЦ Промэлектроника
 *                          URL: https://www.npcprom.ru/
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

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


/**
* @brief	Программная реализация 64-битного деления
*
* @param	rem - Делимое
* @param	base - Делитель
*
* @return	uint64_t - Результат
*/
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