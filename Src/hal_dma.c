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

#include "../Inc/hal_dma.h"


const uint8_t __defaultBuff[] = "\xff";


void HAL_DMA_BaseInit(HAL_DMA_TypeDef *DmaTypeDef) {
	// Включение тактирования блока DMA
	PM->CLK_AHB_SET |= PM_CLOCK_DMA_M;

	// Получение экземпляра DMA
	DMA_CHANNEL_TypeDef *DmaChannel = &DMA_CONFIG->CHANNELS[DmaTypeDef->Channel];

	// Установка значений по-умолчанию (Без этого не работает DMA)
	DmaChannel->SOURCE = (uint32_t)__defaultBuff;
	DmaChannel->DESTINATIONS = (uint32_t)__defaultBuff;
	DmaChannel->LEN = 1 - 1;

	// Установка конфигурации по-умолчанию
	DmaTypeDef->_config = __DMA_CFG_DEFAULT_FIELDS;
}


void HAL_DMA_Init(HAL_DMA_TypeDef *DmaTypeDef) {
	HAL_DMA_BaseInit(DmaTypeDef);

	// Получение канала DMA
	DMA_CHANNEL_TypeDef *DmaChannel = &DMA_CONFIG->CHANNELS[DmaTypeDef->Channel];

	// Приоритет
	DmaTypeDef->_config |= DmaTypeDef->Priority << DMA_CFG_CH_PRIOR_S;

	// Режим адреса источника: периферия/память
	DmaTypeDef->_config |= DmaTypeDef->ReadDirection << DMA_CFG_CH_READ_MODE_S;

	// Режим адреса назначения: периферия/память
	DmaTypeDef->_config |= DmaTypeDef->WriteDirection << DMA_CFG_CH_WRITE_MODE_S;

	// Инкрементирование адреса источника
	DmaTypeDef->_config |= DmaTypeDef->ReadIncrement << DMA_CFG_CH_READ_INCREMENT_S;

	// Инкрементирование адреса назначения
	DmaTypeDef->_config |= DmaTypeDef->WriteIncrement << DMA_CFG_CH_WRITE_INCREMENT_S;

	// Периферийная линия источника
	DmaTypeDef->_config |= DmaTypeDef->SourcePeriphery << DMA_CFG_CH_READ_REQ_S;

	// Перефирийная линия назначения
	DmaTypeDef->_config |= DmaTypeDef->DestinationPeriphery << DMA_CFG_CH_WRITE_REQ_S;

	// Прерывание
	DmaTypeDef->_config |= DmaTypeDef->Interrupt;

	// Configure DMA
	DmaChannel->CONFIG = DMA_CFG_CH_DISABLE_M | DmaTypeDef->_config;
}


void HAL_DMA_Enable(HAL_DMA_TypeDef *DmaTypeDef) {
	DMA_CHANNEL_TypeDef *DmaChannel = &DMA_CONFIG->CHANNELS[DmaTypeDef->Channel];

	DmaChannel->SOURCE			= (uint32_t)DmaTypeDef->SrcBuffPtr;
	DmaChannel->DESTINATIONS	= (uint32_t)DmaTypeDef->DstBuffPtr;
	DmaChannel->LEN				= DmaTypeDef->BuffLength - 1;

	DmaChannel->CONFIG = DMA_CFG_CH_ENABLE_M | DmaTypeDef->_config;
}


bool HAL_DMA_Ready(HAL_DMA_TypeDef *DmaTypeDef) {
	return (DMA_CONFIG->ConfigStatus & (1 << (DMA_STATUS_READY_S + DmaTypeDef->Channel))) != 0;
}


bool HAL_DMA_Busy(HAL_DMA_TypeDef *DmaTypeDef) {
	return (DMA_CONFIG->ConfigStatus & (1 << (DMA_STATUS_READY_S + DmaTypeDef->Channel))) == 0;
}

