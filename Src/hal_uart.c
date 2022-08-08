#include "../Inc/hal_uart.h"



void HAL_UART_Init(HAL_UART_HandleTypeDef *UartTypeDef) {
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

	// Init.TxRxEnable
	if (UartTypeDef->Init.TxRxEnable == UART_TX_RX_ENABLE)
	{
		UartTypeDef->Instance->CONTROL1 |= UART_CONTROL1_RE_M | UART_CONTROL1_TE_M;
	}
	else if (UartTypeDef->Init.TxRxEnable == UART_ONLY_TX_ENABLE)
	{
		UartTypeDef->Instance->CONTROL1 |= UART_CONTROL1_TE_M;
	}
	else if (UartTypeDef->Init.TxRxEnable == UART_ONLY_RX_ENABLE)
	{
		UartTypeDef->Instance->CONTROL1 |= UART_CONTROL1_RE_M;
	}

	// Init.TxPolarityInvert
	if (UartTypeDef->Init.TxPolarityInvert == UART_TX_PIN_INVERT) {
		UartTypeDef->Instance->CONTROL2 |= UART_CONTROL2_TXINV_M;
	}

	// Init.RxPolarityInvert
	if (UartTypeDef->Init.RxPolarityInvert == UART_RX_PIN_INVERT) {
		UartTypeDef->Instance->CONTROL2 |= UART_CONTROL2_RXINV_M;
	}

	// Init.TxRxSwap
	if (UartTypeDef->Init.TxRxSwap == UART_TX_RX_PIN_SWAP) {
		UartTypeDef->Instance->CONTROL2 |= UART_CONTROL2_SWAP_M;
	}

	// Init.SyncMode
	if (UartTypeDef->Init.SyncMode == UART_MODE_SYNC) {
		UartTypeDef->Instance->CONTROL2 |= UART_CONTROL2_CLKEN_M;
	}

	// Enable uart
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