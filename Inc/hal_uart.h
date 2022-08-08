#ifndef HAL_UART_H
#define HAL_UART_H

#include <pad_config.h>
#include <uart.h>

#include "hal.h"
#include "hal_dma.h"


typedef enum {
	UART_TX_RX_ENABLE,
	UART_ONLY_TX_ENABLE,
	UART_ONLY_RX_ENABLE,
} HAL_UART_TxRxEnable;


typedef enum {
	UART_TX_PIN_NORMAL,
	UART_TX_PIN_INVERT
} HAL_UART_TxPolarityInvert;


typedef enum {
	UART_RX_PIN_NORMAL,
	UART_RX_PIN_INVERT
} HAL_UART_RxPolarityInvert;


typedef enum {
	UART_TX_RX_PIN_NORMAL,
	UART_TX_RX_PIN_SWAP			// TX = RX, RX = TX
} HAL_UART_TxRxPinSwap;


typedef enum {
	UART_MODE_ASYNC,
	UART_MODE_SYNC
} HAL_UART_SyncMode;



typedef struct {
	uint32_t					BaudRate;

	HAL_UART_TxRxEnable			TxRxEnable;

	HAL_UART_TxPolarityInvert	TxPolarityInvert;
	HAL_UART_RxPolarityInvert	RxPolarityInvert;

	HAL_UART_TxRxPinSwap		TxRxSwap;

	HAL_UART_SyncMode			SyncMode;

} HAL_UART_InitTypeDef;


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



typedef struct {
	UART_TypeDef			*Instance;

	HAL_UART_InitTypeDef	Init;

	HAL_UART_StateTypeDef	*State;

	__WO uint32_t			*TxBuffPtr;
	__RO uint32_t			*RxBuffPtr;

	HAL_DMA_TypeDef			*TxDma;
	HAL_DMA_TypeDef			*RxDma;

	// dma
} HAL_UART_HandleTypeDef;


void HAL_UART_Init(HAL_UART_HandleTypeDef *UartTypeDef);


void HAL_UART_SetTxDma(HAL_UART_HandleTypeDef *UartTypeDef, HAL_DMA_TypeDef *DmaTypeDef);

void HAL_UART_SetRxDma(HAL_UART_HandleTypeDef *UartTypeDef, HAL_DMA_TypeDef *DmaTypeDef);


void HAL_UART_TransmitByte(HAL_UART_HandleTypeDef *UartTypeDef, uint8_t *pData);

void HAL_UART_ReceiveByte(HAL_UART_HandleTypeDef *UartTypeDef, uint8_t *pData);


void HAL_UART_Transmit(HAL_UART_HandleTypeDef *UartTypeDef, uint8_t *pData, uint16_t Size);

void HAL_UART_Receive(HAL_UART_HandleTypeDef *UartTypeDef, uint8_t *pData, uint16_t Size);


HAL_StatusTypeDef HAL_UART_Transmit_DMA(HAL_UART_HandleTypeDef *UartTypeDef, uint8_t *pData, uint16_t Size);

HAL_StatusTypeDef HAL_UART_Receive_DMA(HAL_UART_HandleTypeDef *UartTypeDef, uint8_t *pData, uint16_t Size);

#endif