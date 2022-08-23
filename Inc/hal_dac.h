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