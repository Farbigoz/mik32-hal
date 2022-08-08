#ifndef HAL_DMA_H
#define HAL_DMA_H

#include <dma_config.h>

#include "hal.h"


#define __DMA_CFG_DEFAULT_FIELDS	(											\
										DMA_CFG_CH_READ_SIZE_byte_M			|	\
										DMA_CFG_CH_WRITE_SIZE_byte_M		|	\
										0 << DMA_CFG_CH_READ_BURST_SIZE_S	|	\
										0 << DMA_CFG_CH_WRITE_BURST_SIZE_S	|	\
										DMA_CFG_CH_ACK_READ_M				|	\
										DMA_CFG_CH_ACK_WRITE_M				|	\
										DMA_CFG_CH_EN_IRQ_M						\
									)


typedef enum {
	HAL_DMA_CHANNEL_1		= 0x0,
	HAL_DMA_CHANNEL_2		= 0x1,
	HAL_DMA_CHANNEL_3		= 0x2,
	HAL_DMA_CHANNEL_4		= 0x3,
} HAL_DMA_Channel;


typedef enum {
	HAL_DMA_LOW_PRIORITY	= 0x0,
	HAL_DMA_MEDIUM_PRIORITY	= 0x1,
	HAL_DMA_HIGH_PRIORITY	= 0x2,
	HAL_DMA_MAX_PRIORITY	= 0x3
} HAL_DMA_Priority;


typedef enum {
	HAL_DMA_DIRECTION_PERIPHERY,
	HAL_DMA_DIRECTION_MEMORY
} HAL_DMA_Direction;


typedef enum {
	HAL_DMA_INCREMENT_DISABLE,
	HAL_DMA_INCREMENT_ENABLE
} HAL_DMA_Increment;


typedef enum {
	HAL_DMA_MEMORY		= 0x0,
	HAL_DMA_UART_0		= DMA_UART_0_INDEX,
	HAL_DMA_UART_1		= DMA_UART_1_INDEX,
	HAL_DMA_CRYPTO		= DMA_CRYPTO_INDEX,
	HAL_DMA_SPI_0		= DMA_SPI_0_INDEX,
	HAL_DMA_SPI_1		= DMA_SPI_1_INDEX,
	HAL_DMA_I2C_0		= DMA_I2C_0_INDEX,
	HAL_DMA_I2C_1		= DMA_I2C_1_INDEX,
	HAL_DMA_SPIFI		= DMA_SPIFI_INDEX,
	HAL_DMA_TIMER32_1	= DMA_TIMER32_1_INDEX,
	HAL_DMA_TIMER32_2	= DMA_TIMER32_2_INDEX,
	HAL_DMA_TIMER32_0	= DMA_TIMER32_0_INDEX
} HAL_DMA_PeripheryLine;


typedef struct {
	HAL_DMA_Channel			Channel;

	HAL_DMA_Priority		Priority;

	HAL_DMA_Direction		ReadDirection;
	HAL_DMA_Direction		WriteDirection;

	HAL_DMA_Increment		ReadIncrement;
	HAL_DMA_Increment		WriteIncrement;

	HAL_DMA_PeripheryLine	SourcePeriphery;
	HAL_DMA_PeripheryLine	DestinationPeriphery;

	uint8_t					*SrcBuffPtr;
	uint8_t					*DstBuffPtr;
	uint32_t				BuffLength;

	//DMA_CHANNEL_TypeDef	*_instance;
	uint32_t				_config;
} HAL_DMA_TypeDef;


void HAL_DMA_BaseInit(HAL_DMA_TypeDef *DmaTypeDef);

void HAL_DMA_Init(HAL_DMA_TypeDef *DmaTypeDef);

void HAL_DMA_Enable(HAL_DMA_TypeDef *DmaTypeDef);

bool HAL_DMA_Ready(HAL_DMA_TypeDef *DmaTypeDef);

bool HAL_DMA_Busy(HAL_DMA_TypeDef *DmaTypeDef);

#endif