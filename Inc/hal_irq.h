#ifndef IRQ_H
#define IRQ_H

#ifdef __cplusplus
extern "C" {
#endif

#include <mcu32_memory_map.h>
#include <epic.h>
#include <csr.h>
#include <scr1_csr_encoding.h>

#include <gpio.h>
#include <timer32.h>

#include "hal.h"


#define __IRQ_IS(epic)			(EPIC->STATUS & (1 << (epic)))
#define __CLEAN_IRQ(epic)		EPIC->CLEAR = 1 << (epic)


/**
 * @brief	Вхождение прерывания
 */
extern void trap_handler();


/**
 * @brief	Инициализация блока прерываний
 */
void HAL_IRQ_Init();


/**
 * @brief	Включение прерываний
 */
void HAL_IRQ_Enable();


/**
 * @brief	Выключение блока прерываний
 */
void HAL_IRQ_Disable();


void HAL_TIMER32_0_IRQ();

void HAL_USART_0_IRQ();

void HAL_USART_1_IRQ();

void HAL_SPI_0_IRQ();

void HAL_SPI_1_IRQ();

void HAL_GPIO_IRQ_IRQ();

void HAL_I2C_0_IRQ();

void HAL_I2C_1_IRQ();

void HAL_WDT_IRQ();

void HAL_TIMER16_0_IRQ();

void HAL_TIMER16_1_IRQ();

void HAL_TIMER16_2_IRQ();

void HAL_TIMER32_1_IRQ();

void HAL_TIMER32_2_IRQ();

void HAL_EEPROM_IRQ();

void HAL_SPIFI_IRQ();

void HAL_RTC_IRQ();

void HAL_WDT_DOM3_IRQ();

void HAL_WDT_SPIFI_IRQ();

void HAL_WDT_EEPROM_IRQ();

void HAL_DMA_GLB_ERR_IRQ();

void HAL_DMA_CHANNELS_IRQ();

void HAL_FREQ_MON_IRQ();

void HAL_PVD_AVCC_UNDER_IRQ();

void HAL_PVD_AVCC_OVER_IRQ();

void HAL_PVD_VCC_UNDER_IRQ();

void HAL_PVD_VCC_OVER_IRQ();

void HAL_BATTERY_NON_GOOD_IRQ();

void HAL_BOR_IRQ();

void HAL_TSENS_IRQ();

void HAL_ADC_IRQ();


#ifdef __cplusplus
}
#endif

#endif