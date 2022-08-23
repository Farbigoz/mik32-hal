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

#include "../Inc/hal_dac.h"


void HAL_DAC_Init(HAL_DAC_TypeDef *DacTypeDef) {
	volatile DAC_TypeDef *dacInstance;

	// Включение тактирования аналоговых блоков
	PM->CLK_APB_P_SET |= 1 << 15;

	// Получение экземпляра ЦАП
	dacInstance = __HAL_DAC_INSTANCE_FROM_CHANNEL(DacTypeDef->Channel);

	// Конфигурация ЦАП
	dacInstance->CFG =	DAC_CFG_RESN_M					|	\
						DacTypeDef->Ref					|	\
						DAC_CFG_DIV(DacTypeDef->FreqDivider);
}


void HAL_DAC_Enable(HAL_DAC_TypeDef *DacTypeDef) {
	volatile DAC_TypeDef *dacInstance = __HAL_DAC_INSTANCE_FROM_CHANNEL(DacTypeDef->Channel);

	dacInstance->CFG |= DAC_CFG_EN18_M;
}


void HAL_DAC_Disable(HAL_DAC_TypeDef *DacTypeDef) {
	volatile DAC_TypeDef *dacInstance = __HAL_DAC_INSTANCE_FROM_CHANNEL(DacTypeDef->Channel);

	dacInstance->CFG &= ~DAC_CFG_EN18_M;
}


void HAL_DAC_SetValue(HAL_DAC_TypeDef *DacTypeDef, uint16_t value) {
	volatile DAC_TypeDef *dacInstance = __HAL_DAC_INSTANCE_FROM_CHANNEL(DacTypeDef->Channel);

	dacInstance->VALUE = value;
}