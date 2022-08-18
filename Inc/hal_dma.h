#ifndef HAL_DMA_H
#define HAL_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <dma_config.h>

#include "hal.h"


// Конфигурация по-умолчанию для DMA
//	Размер считыванемых данных - байт
//	Размер записываемых данных - байт
//	Число считываемых байт за раз - 2^0
//	Число записываемых байт за раз - 2^0
//	Разрешение работы логики с откликом для адресата источника
//	Разрешение работы логики с откликом для адресата назначения
#define __DMA_CFG_DEFAULT_FIELDS	(											\
										DMA_CFG_CH_READ_SIZE_byte_M			|	\
										DMA_CFG_CH_WRITE_SIZE_byte_M		|	\
										0 << DMA_CFG_CH_READ_BURST_SIZE_S	|	\
										0 << DMA_CFG_CH_WRITE_BURST_SIZE_S	|	\
										DMA_CFG_CH_ACK_READ_M				|	\
										DMA_CFG_CH_ACK_WRITE_M					\
									)


/**
 * @brief	Канал
 */
typedef enum {
	HAL_DMA_CHANNEL_1		= 0x0,		///< Канал 1
	HAL_DMA_CHANNEL_2		= 0x1,		///< Канал 2
	HAL_DMA_CHANNEL_3		= 0x2,		///< Канал 3
	HAL_DMA_CHANNEL_4		= 0x3,		///< Канал 4
} HAL_DMA_Channel;


/**
 * @brief	Приоритет канала
 */
typedef enum {
	HAL_DMA_LOW_PRIORITY	= 0x0,		///< Низкий приоритет
	HAL_DMA_MEDIUM_PRIORITY	= 0x1,		///< Средний приоритет
	HAL_DMA_HIGH_PRIORITY	= 0x2,		///< Высокий приоритет
	HAL_DMA_MAX_PRIORITY	= 0x3		///< Максимальный приоритет
} HAL_DMA_Priority;


/**
 * @brief	Источник чтения/записи
 */
typedef enum {
	HAL_DMA_DIRECTION_PERIPHERY,		///< Периферия
	HAL_DMA_DIRECTION_MEMORY			///< Память
} HAL_DMA_Direction;


/**
 * @brief	Инкремент адреса чтения/записи
 */
typedef enum {
	HAL_DMA_INCREMENT_DISABLE,			///< Не активен
	HAL_DMA_INCREMENT_ENABLE			///< Активен
} HAL_DMA_Increment;


/**
 * @brief	Линии источников чтения/записи
 */
typedef enum {
	HAL_DMA_MEMORY		= 0x0,					///< Память
	HAL_DMA_UART_0		= DMA_UART_0_INDEX,		///< UART 0
	HAL_DMA_UART_1		= DMA_UART_1_INDEX,		///< UART 1
	HAL_DMA_CRYPTO		= DMA_CRYPTO_INDEX,		///< Криптографический блок
	HAL_DMA_SPI_0		= DMA_SPI_0_INDEX,		///< SPI 0
	HAL_DMA_SPI_1		= DMA_SPI_1_INDEX,		///< SPI 1
	HAL_DMA_I2C_0		= DMA_I2C_0_INDEX,		///< I2C 0
	HAL_DMA_I2C_1		= DMA_I2C_1_INDEX,		///< I2C 1
	HAL_DMA_SPIFI		= DMA_SPIFI_INDEX,		///< SPIFI
	HAL_DMA_TIMER32_1	= DMA_TIMER32_1_INDEX,	///< 32-ух битный таймер 1
	HAL_DMA_TIMER32_2	= DMA_TIMER32_2_INDEX,	///< 32-ух битный таймер 2
	HAL_DMA_TIMER32_0	= DMA_TIMER32_0_INDEX	///< 32-ух битный таймер 0
} HAL_DMA_PeripheryLine;


/**
 * @brief	Разрешение формирования прерывания по завершении работы канала
 */
typedef enum {
	HAL_DMA_INTERRUPT_DISABLE	= 0x0 << DMA_CFG_CH_EN_IRQ_S,	///< Отключено
	HAL_DMA_INTERRUPT_ENABLE	= 0x1 << DMA_CFG_CH_EN_IRQ_S,	///< Включено
} HAL_DMA_Interrupt;


/**
 * @brief	Объявление структуры обработчкиа DMA
 */
typedef struct {
	HAL_DMA_Channel			Channel;				///< Канал

	HAL_DMA_Priority		Priority;				///< Приоритет

	HAL_DMA_Direction		ReadDirection;			///< Источник чтения
	HAL_DMA_Direction		WriteDirection;			///< Источник записи

	HAL_DMA_Increment		ReadIncrement;			///< Инкремент адреса чтения
	HAL_DMA_Increment		WriteIncrement;			///< Инкремент адреса записи

	HAL_DMA_PeripheryLine	SourcePeriphery;		///< Линия чтения
	HAL_DMA_PeripheryLine	DestinationPeriphery;	///< Линия записи

	HAL_DMA_Interrupt		Interrupt;				///< Прерывание по завершению работы канала

	uint8_t					*SrcBuffPtr;			///< Адрес буфера чтения
	uint8_t					*DstBuffPtr;			///< Адрес буфера записи
	uint32_t				BuffLength;				///< Кол-во байт для чтения-записи

	uint32_t				_config;
} HAL_DMA_TypeDef;


/**
 * @brief	Базовая инициализация DMA
 *
 * @param	hdma - Экземпляр обработчкиа DMA
 */
void HAL_DMA_BaseInit(HAL_DMA_TypeDef *hdma);


/**
 * @brief	Инициализация DMA
 *
 * @param	hdma - Экземпляр обработчкиа DMA
 */
void HAL_DMA_Init(HAL_DMA_TypeDef *hdma);


/**
 * @brief	Включение DMA
 *
 * @param	hdma - Экземпляр обработчкиа DMA
 */
void HAL_DMA_Enable(HAL_DMA_TypeDef *hdma);


/**
 * @brief	Свободен ли DMA
 *
 * @param	hdma - Экземпляр обработчкиа DMA
 *
 * @return	bool
 */
bool HAL_DMA_Ready(HAL_DMA_TypeDef *hdma);


/**
 * @brief	Занят ли DMA
 *
 * @param	hdma - Экземпляр обработчкиа DMA
 *
 * @return	bool
 */
bool HAL_DMA_Busy(HAL_DMA_TypeDef *hdma);


#ifdef __cplusplus
}
#endif


#endif