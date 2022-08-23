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

#ifndef HAL_UART_H
#define HAL_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include <pad_config.h>
#include <uart.h>

#include "hal.h"
#include "hal_dma.h"



/**
 * @brief	Режим передачи
 */
typedef enum {
	HAL_UART_TX_DISABLE	= 0x0 << UART_CONTROL1_TE_S,		///< Передача отключена
	HAL_UART_TX_ENABLE	= 0x1 << UART_CONTROL1_TE_S,		///< Передача включена
} HAL_UART_TxState;


/**
 * @brief	Режим приёма
 */
typedef enum {
	HAL_UART_RX_DISABLE	= 0x0 << UART_CONTROL1_RE_S,		///< Приём отключён
	HAL_UART_RX_ENABLE	= 0x1 << UART_CONTROL1_RE_S,		///< Приём включён
} HAL_UART_RxState;


/**
 * @brief	Полярность пина передачи
 */
typedef enum {
	HAL_UART_TX_PIN_NORMAL = 0x0 << UART_CONTROL2_TXINV_S,	///< Нормальная полярность
	HAL_UART_TX_PIN_INVERT = 0x1 << UART_CONTROL2_TXINV_S,	///< Инвертированная полярность
} HAL_UART_TxPolarity;


/**
 * @brief	Полярность пина приёма
 */
typedef enum {
	HAL_UART_RX_PIN_NORMAL = 0x0 << UART_CONTROL2_RXINV_S,	///< Нормальная полярность
	HAL_UART_RX_PIN_INVERT = 0x1 << UART_CONTROL2_RXINV_S,	///< Инвертированная полярность
} HAL_UART_RxPolarity;


/**
 * @brief	Смена назначения пинов приёма и передачи
 */
typedef enum {
	HAL_UART_DATA_PIN_NORMAL = 0x0 << UART_CONTROL2_SWAP_S,	///< Нормальное состояние
	HAL_UART_DATA_PIN_SWAP	 = 0x1 << UART_CONTROL2_SWAP_S,	///< TX => RX, RX => TX
} HAL_UART_DataPinSwap;


/**
 * @brief	Режим работы UART
 */
typedef enum {
	HAL_UART_MODE_ASYNC	= 0x0 << UART_CONTROL2_CLKEN_S,		///< Асинхронный
	HAL_UART_MODE_SYNC	= 0x1 << UART_CONTROL2_CLKEN_S,		///< Синхронный
} HAL_UART_Mode;


/**
 * @brief	Объявление структуры инициализации UART
 */
typedef struct {
	uint32_t				BaudRate;			///< БОД-овая скорость UART

	HAL_UART_TxState		TxState;			///< Режим передачи
	HAL_UART_RxState		RxState;			///< Режим приёма

	HAL_UART_TxPolarity		TxPolarityInvert;	///< Полярность пина передачи
	HAL_UART_RxPolarity		RxPolarityInvert;	///< Полярность пина приёма

	HAL_UART_DataPinSwap	DataPinSwap;		///< Смена пинов передачи и приёма местами

	HAL_UART_Mode			Mode;				///< Режим работы UART

} HAL_UART_InitTypeDef;


/**
 * @brief	Объявление структуры состояния UART
 */
typedef struct {
	__RW uint32_t		RxParityBitError	:1;			// PE
	__RW uint32_t		RxStopBitError		:1;			// FE
	__RW uint32_t		RxNoise				:1;			// NF
	__RW uint32_t		RxOverwriting		:1;			// ORE
	__RW uint32_t		RxIdle				:1;			// IDLE
	__RW uint32_t		DataReceived		:1;			// RXNE
	__RW uint32_t		DataSent			:1;			// TC
	__RW uint32_t							:1;			// TXE
	__RW uint32_t		RxBreak				:1;			// LBDF
	__RW uint32_t		CtsSignalChanged	:1;			// CTSIF
	__RO uint32_t		CtsSignalState		:1;			// CTS
		 uint32_t							:5;			// -
	__RO uint32_t		RxBusy				:1;			// BUSY
		 uint32_t							:4;			// -
	__RO uint32_t		TxEnable			:1;			// TEACK
	__RO uint32_t		RxEnable			:1;			// REACK
		 uint32_t							:10;		// -
} HAL_UART_StateTypeDef;


/**
 * @brief	Объявление структуры обработчика UART
 */
typedef struct {
	UART_TypeDef			*Instance;		///< Экземпляр UART

	HAL_UART_InitTypeDef	Init;			///< Структура инициализация UART

	HAL_UART_StateTypeDef	*State;			///< Указатель на структуру состояния UART

	__WO uint32_t			*TxBuffPtr;		///< Указатель на буфер отправки
	__RO uint32_t			*RxBuffPtr;		///< Указатель на буфер приёма

	HAL_DMA_TypeDef			*TxDma;			///< Экземпляр обработчкика DMA на отправку
	HAL_DMA_TypeDef			*RxDma;			///< Экземпляр обработчкика DMA на приём
} HAL_UART_HandleTypeDef;


/**
 * @brief	Инициализация UART
 *
 * @param	huart - Экземпляр обработчкиа UART
 */
void HAL_UART_Init(HAL_UART_HandleTypeDef *huart);


/**
 * @brief	Установка DMA на передачу
 *
 * @param	huart - Экземпляр обработчкиа UART
 * @param	hdma  - Экземпляр обработчкиа DMA
 */
void HAL_UART_SetTxDma(HAL_UART_HandleTypeDef *huart, HAL_DMA_TypeDef *hdma);


/**
 * @brief	Установка DMA на приём
 *
 * @param	huart - Экземпляр обработчкиа UART
 * @param	hdma  - Экземпляр обработчкиа DMA
 */
void HAL_UART_SetRxDma(HAL_UART_HandleTypeDef *huart, HAL_DMA_TypeDef *hdma);


/**
 * @brief	Отправка байта в UART
 *
 * @param	huart - Экземпляр обработчкиа UART
 * @param	pData - Указатель на байт
 */
void HAL_UART_TransmitByte(HAL_UART_HandleTypeDef *huart, uint8_t *pData);


/**
 * @brief	Чтение байта из UART
 *
 * @param	huart - Экземпляр обработчкиа UART
 * @param	pData - Указатель для записи байта
 */
void HAL_UART_ReceiveByte(HAL_UART_HandleTypeDef *huart, uint8_t *pData);


/**
 * @brief	Отправка в UART
 *
 * @param	huart - Экземпляр обработчкиа UART
 * @param	pData - Указатель на буфер
 * @param	size  - Размер буфера
 */
void HAL_UART_Transmit(HAL_UART_HandleTypeDef *huart, uint8_t *pData, uint16_t size);


/**
 * @brief	Чтение из UART
 *
 * @param	huart - Экземпляр обработчкиа UART
 * @param	pData - Указатель на буфер
 * @param	size  - Размер буфера
 */
void HAL_UART_Receive(HAL_UART_HandleTypeDef *huart, uint8_t *pData, uint16_t size);


/**
 * @brief	Отправка в UART через DMA
 *
 * @param	huart - Экземпляр обработчкиа UART
 * @param	pData - Указатель на буфер
 * @param	size  - Размер буфера
 */
HAL_StatusTypeDef HAL_UART_Transmit_DMA(HAL_UART_HandleTypeDef *huart, uint8_t *pData, uint16_t size);


/**
 * @brief	Чтение из UART через DMA
 *
 * @param	huart - Экземпляр обработчкиа UART
 * @param	pData - Указатель на буфер
 * @param	size  - Размер буфера
 */
HAL_StatusTypeDef HAL_UART_Receive_DMA(HAL_UART_HandleTypeDef *huart, uint8_t *pData, uint16_t size);


#ifdef __cplusplus
}
#endif

#endif