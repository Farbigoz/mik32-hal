#ifndef HAL_ADC_H
#define HAL_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <pad_config.h>
#include <analog_reg.h>

#include "hal.h"


/**
 * @brief	Каналы АЦП
 */
typedef enum {
	HAL_ADC_CHANNEL_1		= 0x0,		///< Канал 1
	HAL_ADC_CHANNEL_2		= 0x1,		///< Канал 2
	HAL_ADC_CHANNEL_3		= 0x2,		///< Канал 3
	HAL_ADC_CHANNEL_4		= 0x3,		///< Канал 4
	HAL_ADC_CHANNEL_5		= 0x4,		///< Канал 5
	HAL_ADC_CHANNEL_6		= 0x5,		///< Канал 6
	HAL_ADC_CHANNEL_7		= 0x6,		///< Канал 7
	HAL_ADC_CHANNEL_8		= 0x7,		///< Канал 8
} HAL_ADC_Channel;


/**
 * @brief	Опорное напряжение АЦП
 */
typedef enum {
	HAL_ADC_REF_INTERNAL	= 0x0,		///< Внутреннее опорное напряжение
	HAL_ADC_REF_EXTERNAL	= 0x1,		///< Внешнее опорное напряжение
} HAL_ADC_RefSource;


/**
 * @brief	Объявление структуры обработчкиа АЦП
 */
typedef struct {
	HAL_ADC_Channel		Channel;		///< Канал

	HAL_ADC_RefSource	Ref;			///< Опорное напряжение
} HAL_ADC_TypeDef;


/**
 * @brief	Инициализация АЦП
 *
 * @param	hadc - Экземпляр обработчкиа АЦП
 */
void HAL_ADC_Init(HAL_ADC_TypeDef *hadc);


/**
 * @brief	Включение блока АЦП
 *
 * @param	hadc - Экземпляр обработчкиа АЦП
 */
void HAL_ADC_Enable(HAL_ADC_TypeDef *AdcTypeDef);


/**
 * @brief	Выключение блока АЦП
 *
 * @param	hadc - Экземпляр обработчкиа АЦП
 */
void HAL_ADC_Disable(HAL_ADC_TypeDef *AdcTypeDef);


/**
 * @brief	Запустить единичное измерение входного уровня сигнала АЦП
 *
 * @param	hadc - Экземпляр обработчкиа АЦП
 */
void HAL_ADC_Start(HAL_ADC_TypeDef *hadc);


/**
 * @brief	Остановка единичного измерения входного уровня сигнала АЦП
 *
 * @param	hadc - Экземпляр обработчкиа АЦП
 */
void HAL_ADC_Stop(HAL_ADC_TypeDef *hadc);


/**
 * @brief	Запуск циклического измерения АЦП
 *
 * @param	hadc - Экземпляр обработчкиа АЦП
 */
void HAL_ADC_Start_Continuous(HAL_ADC_TypeDef *hadc);


/**
 * @brief	Остановка циклического измерения АЦП
 *
 * @param	hadc - Экземпляр обработчкиа АЦП
 */
void HAL_ADC_Stop_Continuous(HAL_ADC_TypeDef *hadc);


/**
 * @brief	Значение считано и записано в регистр
 *
 * @param	hadc - Экземпляр обработчкиа АЦП
 *
 * @return	bool
 */
bool HAL_ADC_ValueAvailable(HAL_ADC_TypeDef *hadc);


/**
 * @brief	Считывание значения АЦП
 *
 * @param	hadc - Экземпляр обработчкиа АЦП
 *
 * @return	uint16_t - 12-битное значение входного уровня сигнала на АЦП
 */
uint16_t HAL_ADC_GetValue(HAL_ADC_TypeDef *hadc);


#ifdef __cplusplus
}
#endif


#endif