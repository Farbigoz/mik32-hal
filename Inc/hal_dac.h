#ifndef HAL_DAC_H
#define HAL_DAC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <analog_reg.h>

#include "hal.h"

/// Экземпляр ЦАП исходя из перечисления 'HAL_DAC_Channel'
#define __HAL_DAC_INSTANCE_FROM_CHANNEL(channel)	((channel == HAL_DAC_CHANNEL_1) ? (&ANALOG_REG->DAC0) : (&ANALOG_REG->DAC1))


/**
* @brief	Каналы ЦАП
*/
typedef enum {
	HAL_DAC_CHANNEL_1,
	HAL_DAC_CHANNEL_2,
} HAL_DAC_Channel;


/**
 * @brief	Опорное напряжение ЦАП
 */
typedef enum {
	HAL_DAC_REF_INTERNAL	= (0 << DAC_CFG_EXTEN_S),		///< Внутреннее опорное напряжение
	HAL_DAC_REF_EXTERNAL	= (11 << DAC_CFG_EXTEN_S),		///< Внешнее опорное напряжение
} HAL_DAC_RefSource;


/**
 * @brief	Объявление структуры обработчкиа ЦАП
 */
typedef struct {
	HAL_DAC_Channel		Channel;		///< Канал

	HAL_DAC_RefSource	Ref;			///< Опорное напряжение

	uint8_t				FreqDivider;	///< Делитель тактового сигнала
} HAL_DAC_TypeDef;


/**
 * @brief	Инициализация ЦАП
 *
 * @param	hdac - Экземпляр обработчкиа ЦАП
 */
void HAL_DAC_Init(HAL_DAC_TypeDef *hdac);


/**
 * @brief	Включение ЦАП
 *
 * @param	hdac - Экземпляр обработчкиа ЦАП
 */
void HAL_DAC_Enable(HAL_DAC_TypeDef *hdac);


/**
 * @brief	Выключение ЦАП
 *
 * @param	hdac - Экземпляр обработчкиа ЦАП
 */
void HAL_DAC_Disable(HAL_DAC_TypeDef *hdac);


/**
 * @brief	Установка уровня выходного уровня ЦАП
 *
 * @param	hdac - Экземпляр обработчкиа ЦАП
 * @param	value - 12-битное значение уровня
 */
void HAL_DAC_SetValue(HAL_DAC_TypeDef *hdac, uint16_t value);


#ifdef __cplusplus
}
#endif


#endif