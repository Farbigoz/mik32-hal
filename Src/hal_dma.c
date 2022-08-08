#include "../Inc/hal_dma.h"


const uint8_t __defaultBuff[] = "\xff";


void HAL_DMA_BaseInit(HAL_DMA_TypeDef *DmaTypeDef) {
	PM->CLK_AHB_SET |= PM_CLOCK_DMA_M;

	DMA_CHANNEL_TypeDef *DmaChannel = &DMA_CONFIG->CHANNELS[DmaTypeDef->Channel];

	DmaChannel->SOURCE = (uint32_t)__defaultBuff;
	DmaChannel->DESTINATIONS = (uint32_t)__defaultBuff;
	DmaChannel->LEN = 1 - 1;

	DmaTypeDef->_config = __DMA_CFG_DEFAULT_FIELDS;
}


void HAL_DMA_Init(HAL_DMA_TypeDef *DmaTypeDef) {
	HAL_DMA_BaseInit(DmaTypeDef);

	DMA_CHANNEL_TypeDef *DmaChannel = &DMA_CONFIG->CHANNELS[DmaTypeDef->Channel];

	// Priority
	DmaTypeDef->_config |= DmaTypeDef->Priority << DMA_CFG_CH_PRIOR_S;

	// ReadDirection
	DmaTypeDef->_config |= DmaTypeDef->ReadDirection << DMA_CFG_CH_READ_MODE_S;

	// WriteDirection
	DmaTypeDef->_config |= DmaTypeDef->WriteDirection << DMA_CFG_CH_WRITE_MODE_S;

	// ReadIncrement
	DmaTypeDef->_config |= DmaTypeDef->ReadIncrement << DMA_CFG_CH_READ_INCREMENT_S;

	// WriteIncrement
	DmaTypeDef->_config |= DmaTypeDef->WriteIncrement << DMA_CFG_CH_WRITE_INCREMENT_S;

	// SourcePeriphery
	DmaTypeDef->_config |= DmaTypeDef->SourcePeriphery << DMA_CFG_CH_READ_REQ_S;

	// DestinationPeriphery
	DmaTypeDef->_config |= DmaTypeDef->DestinationPeriphery << DMA_CFG_CH_WRITE_REQ_S;

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

