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

#include "../Inc/hal_uart.h"

/**
 * @brief	Режим передачи
 */
void HAL_UART_Init(HAL_UART_HandleTypeDef *UartTypeDef) {
	uint32_t cfg;

	// Init UART clock
	if (UartTypeDef->Instance == UART_0)
	{
		PM->CLK_APB_P_SET |= PM_CLOCK_UART_0_M;
	}
	else if (UartTypeDef->Instance == UART_1)
	{
		PM->CLK_APB_P_SET |= PM_CLOCK_UART_1_M;
	}

	UartTypeDef->State = (HAL_UART_StateTypeDef *)(&UartTypeDef->Instance->FLAGS);

	UartTypeDef->RxBuffPtr = &UartTypeDef->Instance->RXDATA;
	UartTypeDef->TxBuffPtr = &UartTypeDef->Instance->TXDATA;

	// Disable uart
	UartTypeDef->Instance->CONTROL1 = 0 << UART_CONTROL1_UE_S;

	// Init.BaudRate
	UartTypeDef->Instance->DIVIDER = (CPU_CLOCK_MHZ*1000*1000) / UartTypeDef->Init.BaudRate;

	cfg =	UartTypeDef->Init.TxState			|	\
			UartTypeDef->Init.RxState;
	UartTypeDef->Instance->CONTROL1 = cfg;

	cfg =	UartTypeDef->Init.TxPolarityInvert	|	\
			UartTypeDef->Init.RxPolarityInvert	|	\

			UartTypeDef->Init.DataPinSwap		|	\
			UartTypeDef->Init.Mode;
	UartTypeDef->Instance->CONTROL2 = cfg;

	// Enable
	UartTypeDef->Instance->CONTROL1 |= 1 << UART_CONTROL1_UE_S;

	// Wait to enable
	while (!(UartTypeDef->State->TxEnable)
		   && !(UartTypeDef->State->RxEnable));
}



void HAL_UART_SetTxDma(HAL_UART_HandleTypeDef *UartTypeDef, HAL_DMA_TypeDef *DmaTypeDef) {
	HAL_DMA_BaseInit(DmaTypeDef);

	UartTypeDef->Instance->CONTROL3 |= UART_CONTROL3_DMAT_M;
	UartTypeDef->TxDma = DmaTypeDef;

	DmaTypeDef->DstBuffPtr = (uint8_t *)UartTypeDef->TxBuffPtr;

	DmaTypeDef->ReadDirection = HAL_DMA_DIRECTION_MEMORY;
	DmaTypeDef->WriteDirection = HAL_DMA_DIRECTION_PERIPHERY;

	DmaTypeDef->ReadIncrement = HAL_DMA_INCREMENT_ENABLE;
	DmaTypeDef->WriteIncrement = HAL_DMA_INCREMENT_DISABLE;

	DmaTypeDef->SourcePeriphery = HAL_DMA_MEMORY;
	if (UartTypeDef->Instance == UART_0)
	{
		DmaTypeDef->DestinationPeriphery = HAL_DMA_UART_0;
	}
	else if (UartTypeDef->Instance == UART_1)
	{
		DmaTypeDef->DestinationPeriphery = HAL_DMA_UART_1;
	}

	HAL_DMA_Init(DmaTypeDef);
}


void HAL_UART_SetRxDma(HAL_UART_HandleTypeDef *UartTypeDef, HAL_DMA_TypeDef *DmaTypeDef) {
	HAL_DMA_BaseInit(DmaTypeDef);

	UartTypeDef->Instance->CONTROL3 |= UART_CONTROL3_DMAR_M;
	UartTypeDef->RxDma = DmaTypeDef;

	DmaTypeDef->SrcBuffPtr = (uint8_t *)UartTypeDef->RxBuffPtr;

	DmaTypeDef->ReadDirection = HAL_DMA_DIRECTION_PERIPHERY;
	DmaTypeDef->WriteDirection = HAL_DMA_DIRECTION_MEMORY;

	DmaTypeDef->ReadIncrement = HAL_DMA_INCREMENT_DISABLE;
	DmaTypeDef->WriteIncrement = HAL_DMA_INCREMENT_ENABLE;

	if (UartTypeDef->Instance == UART_0)
	{
		DmaTypeDef->SourcePeriphery = HAL_DMA_UART_0;
	}
	else if (UartTypeDef->Instance == UART_1)
	{
		DmaTypeDef->SourcePeriphery = HAL_DMA_UART_1;
	}
	DmaTypeDef->DestinationPeriphery = HAL_DMA_MEMORY;

	HAL_DMA_Init(DmaTypeDef);
}



void HAL_UART_TransmitByte(HAL_UART_HandleTypeDef *UartTypeDef, uint8_t *pData) {
	*UartTypeDef->TxBuffPtr = *pData;
	while (!(UartTypeDef->State->DataSent));
}


void HAL_UART_ReceiveByte(HAL_UART_HandleTypeDef *UartTypeDef, uint8_t *pData) {
	while (!(UartTypeDef->State->DataReceived));
	*pData = *UartTypeDef->RxBuffPtr;
}



void HAL_UART_Transmit(HAL_UART_HandleTypeDef *UartTypeDef, uint8_t *pData, uint16_t Size) {
	for (int i = 0; i < Size; i++) {
		HAL_UART_TransmitByte(UartTypeDef, &pData[i]);
	}
}


void HAL_UART_Receive(HAL_UART_HandleTypeDef *UartTypeDef, uint8_t *pData, uint16_t Size) {
	for (int i = 0; i < Size; i++) {
		HAL_UART_ReceiveByte(UartTypeDef, &pData[i]);
	}
}



HAL_StatusTypeDef HAL_UART_Transmit_DMA(HAL_UART_HandleTypeDef *UartTypeDef, uint8_t *pData, uint16_t Size) {
	if (UartTypeDef->TxDma == NULL) {
		return HAL_ERROR;
	}

	if (HAL_DMA_Busy(UartTypeDef->TxDma)) {
		return HAL_BUSY;
	}

	UartTypeDef->TxDma->SrcBuffPtr = pData;
	UartTypeDef->TxDma->BuffLength = Size;

	HAL_DMA_Enable(UartTypeDef->TxDma);

	return HAL_OK;
}


HAL_StatusTypeDef HAL_UART_Receive_DMA(HAL_UART_HandleTypeDef *UartTypeDef, uint8_t *pData, uint16_t Size) {
	if (UartTypeDef->RxDma == NULL) {
		return HAL_ERROR;
	}

	if (HAL_DMA_Busy(UartTypeDef->RxDma)) {
		return HAL_BUSY;
	}

	UartTypeDef->RxDma->DstBuffPtr = pData;
	UartTypeDef->RxDma->BuffLength = Size;

	HAL_DMA_Enable(UartTypeDef->RxDma);

	return HAL_OK;
}