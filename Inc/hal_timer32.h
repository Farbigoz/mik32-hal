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

#ifndef HAL_TIMER_32_H
#define HAL_TIMER_32_H

#ifdef __cplusplus
extern "C" {
#endif

#include <epic.h>
#include <timer32.h>

#include "hal.h"


#define TIMER32_CHANNEL_COUNT			4


#define TIMER32_IRQ_OVERFLOW			0				///< Бит прерывания по переполнению
#define TIMER32_IRQ_UNDERFLOW			1				///< Бит прерывания по опустошению
#define TIMER32_IRQ_CAPTURE(channel)	(2 + channel)	///< Бит прерывания по захвату
#define TIMER32_IRQ_COMPARE(channel)	(6 + channel)	///< Бит прерывания по сравнению


#define __TIMER32_IRQ_IS(htim, irq)		(htim->Instance->IntFlags & (1 << (irq)))
#define __TIMER32_CLEAN_IRQ(htim, irq)	htim->Instance->IntClear = 1 << (irq)


/**
 * @brief	Тип отсчёта таймера
 */
typedef enum {
	HAL_TIMER32_COUNTER_UP				= 0x0,		///< Инкремент
	HAL_TIMER32_COUNTER_DOWN			= 0x1,		///< Декремент
	HAL_TIMER32_COUNTER_BIDIRECT		= 0x2,		///< Инкремент+декремент
} HAL_TIMER32_CounterMode;


/**
 * @brief	Каналы таймера
 */
typedef enum {
	HAL_TIMER32_CHANNEL_1	= 0x0,		///< Канал 0
	HAL_TIMER32_CHANNEL_2	= 0x1,		///< Канал 1
	HAL_TIMER32_CHANNEL_3	= 0x2,		///< Канал 2
	HAL_TIMER32_CHANNEL_4	= 0x3,		///< Канал 3
} HAL_TIMER32_Channel;


/**
 * @brief	Тип канала таймера
 */
typedef enum {
	HAL_TIMER32_CHANNEL_MODE_COMPARE	= 0x1,		///< Сравнение
	HAL_TIMER32_CHANNEL_MODE_CAPTURE	= 0x2,		///< Захват
	HAL_TIMER32_CHANNEL_MODE_PWM		= 0x3,		///< ШИМ
} HAL_TIMER32_ChannelMode;


/**
 * @brief	Тип захвата канала таймера
 */
typedef enum {
	HAL_TIMER32_CHANNEL_CAPTURE_FRONT	= 0x0,		///< По фронту
	HAL_TIMER32_CHANNEL_CAPTURE_SLICE	= 0x1,		///< По срезу
} HAL_TIMER32_ChannelCaptureMode;


/**
 * @brief	Тип ШИМ-а канала таймера
 */
typedef enum {
	HAL_TIMER32_CHANNEL_PWM_NORMAL		= 0x0,		///< Обычный
	HAL_TIMER32_CHANNEL_PWM_INVERT		= 0x1,		///< Инвертированный
} HAL_TIMER32_ChannelPWMType;


/**
 * @brief	Прерывания таймера
 */
typedef enum {
	HAL_TIMER32_INTERRUPT_NONE = 0,					///< Нет прерывания
	HAL_TIMER32_INTERRUPT_OVERFLOW = 1 << 0,		///< Прерывание по переполнению счётчика
	HAL_TIMER32_INTERRUPT_UNDERFLOW = 1 << 1,		///< Прерывание по опустошению счётчика
} HAL_TIMER32_Interrupt;


/**
 * @brief	Прерывания каналов таймеров
 */
typedef enum {
	HAL_TIMER32_CHANNEL_INTERRUPT_NONE = 0,			///< Нет прерывания
	HAL_TIMER32_CHANNEL_INTERRUPT_CAPTURE = 1 << 2,	///< Прерывание по захвату
	HAL_TIMER32_CHANNEL_INTERRUPT_COMPARE = 1 << 6,	///< Прерывание по сравнению
} HAL_TIMER32_ChanelInterrupt;


/**
 * @brief	Объявление структуры инициализация таймера
 */
typedef struct {
	uint32_t						Period;
	uint32_t						Prescaler;

	// source
	HAL_TIMER32_CounterMode			CountMode;

	HAL_TIMER32_Interrupt			Interrupt;
} HAL_TIMER32_InitTypeDef;


/**
 * @brief	Объявление структуры инициализация канала таймера
 */
typedef struct {
	uint32_t						Compare;

	HAL_TIMER32_ChannelMode			Mode;

	HAL_TIMER32_ChannelCaptureMode	CaptureMode;

	HAL_TIMER32_ChannelPWMType		PwmType;

	HAL_TIMER32_ChanelInterrupt		Interrupt;
} HAL_TIMER32_ChannelTypeDef;


/**
 * @brief	Объявление структуры обработчкиа таймера
 */
typedef struct {
	TIMER32_TypeDef					*Instance;

	HAL_TIMER32_InitTypeDef			Init;

	HAL_TIMER32_ChannelTypeDef		Channel[TIMER32_CHANNEL_COUNT];
} HAL_TIMER32_TypeDef;


/**
 * @brief	Инициализация таймера
 *
 * @param	htim - Экземпляр обработчкиа таймера
 */
void HAL_TIMER32_Init(HAL_TIMER32_TypeDef *htim);


/**
 * @brief	Запуск таймера
 *
 * @param	htim - Экземпляр обработчкиа таймера
 */
void HAL_TIMER32_Start(HAL_TIMER32_TypeDef *htim);


/**
 * @brief	Остановка таймера
 *
 * @param	htim - Экземпляр обработчкиа таймера
 */
void HAL_TIMER32_Stop(HAL_TIMER32_TypeDef *htim);


/**
 * @brief	Перезапуск таймера
 *
 * @param	htim - Экземпляр обработчкиа таймера
 */
void HAL_TIMER32_Reset(HAL_TIMER32_TypeDef *htim);


/**
 * @brief	Запуск канала таймера
 *
 * @param	htim - Экземпляр обработчкиа таймера
 * @param	channel - Канал таймера
 */
void HAL_TIMER32_ChannelStart(HAL_TIMER32_TypeDef *htim, HAL_TIMER32_Channel channel);


/**
 * @brief	Остановка канала таймера
 *
 * @param	htim - Экземпляр обработчкиа таймера
 * @param	channel - Канал таймера
 */
void HAL_TIMER32_ChannelStop(HAL_TIMER32_TypeDef *htim, HAL_TIMER32_Channel channel);


/**
 * @brief	Получение значения счётчика таймера
 *
 * @param	htim - Экземпляр обработчкиа таймера
 *
 * @return	uint32_t - Значение счётчика таймера
 */
uint32_t HAL_TIMER32_GetValue(HAL_TIMER32_TypeDef *htim);


/**
 * @brief	Установка значения захвата канала таймера
 *
 * @param	htim - Экземпляр обработчкиа таймера
 * @param	channel - Канал таймера
 * @param	capture - Значение захвата
 */
void HAL_TIMER32_ChannelSetCapture(HAL_TIMER32_TypeDef *htim, HAL_TIMER32_Channel channel, uint32_t capture);


/**
 * @brief	Получение значения захвата канала таймера
 *
 * @param	htim - Экземпляр обработчкиа таймера
 * @param	channel - Канал таймера
 *
 * @return	uint32_t - Значение захвата
 */
uint32_t HAL_TIMER32_ChannelGetCapture(HAL_TIMER32_TypeDef *htim, HAL_TIMER32_Channel channel);


/**
 * @brief	Установка значения сравнения канала таймера
 *
 * @param	htim - Экземпляр обработчкиа таймера
 * @param	channel - Канал таймера
 * @param	compare - Значение сравнения
 */
void HAL_TIMER32_ChannelSetCompare(HAL_TIMER32_TypeDef *htim, HAL_TIMER32_Channel channel, uint32_t compare);


/**
 * @brief	Получение значения сравнения канала таймера
 *
 * @param	htim - Экземпляр обработчкиа таймера
 * @param	channel - Канал таймера
 *
 * @return	uint32_t - Значение сравнения
 */
uint32_t HAL_TIMER32_ChannelGetCompare(HAL_TIMER32_TypeDef *htim, HAL_TIMER32_Channel channel);


/**
 * @brief	Прерывнаие таймера по переполнению счётчика
 *
 * @param	htim - Экземпляр обработчкиа таймера
 */
void HAL_TIMER32_IRQ_OverflowCallback(HAL_TIMER32_TypeDef *htim);


/**
 * @brief	Прерывание таймера по опустошению счётчика
 *
 * @param	htim - Экземпляр обработчкиа таймера
 */
void HAL_TIMER32_IRQ_UnderflowCallback(HAL_TIMER32_TypeDef *htim);


/**
 * @brief	Прерывание канала таймера по захвату
 *
 * @param	htim - Экземпляр обработчкиа таймера
 * @param	channel - Канал таймера
 */
void HAL_TIMER32_IRQ_ChannelCaptureCallback(HAL_TIMER32_TypeDef *htim, HAL_TIMER32_Channel channel);


/**
 * @brief	Прерывание канала таймера по сравнению
 *
 * @param	htim - Экземпляр обработчкиа таймера
 * @param	channel - Канал таймера
 */
void HAL_TIMER32_IRQ_ChannelCompareCallback(HAL_TIMER32_TypeDef *htim, HAL_TIMER32_Channel channel);


/**
 * @brief	Обработчик прерываний таймера
 *
 * @param	htim - Экземпляр обработчкиа таймера
 */
void HAL_TIMER32_IRQHandler(HAL_TIMER32_TypeDef *htim);


#ifdef __cplusplus
}
#endif

#endif