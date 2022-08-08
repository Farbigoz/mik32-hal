#ifndef HAL_ADC_H
#define HAL_ADC_H

#include <pad_config.h>
#include <analog_reg.h>

#include "hal.h"


typedef enum {
	HAL_ADC_CHANNEL_1		= 0x0,
	HAL_ADC_CHANNEL_2		= 0x1,
	HAL_ADC_CHANNEL_3		= 0x2,
	HAL_ADC_CHANNEL_4		= 0x3,
	HAL_ADC_CHANNEL_5		= 0x4,
	HAL_ADC_CHANNEL_6		= 0x5,
	HAL_ADC_CHANNEL_7		= 0x6,
	HAL_ADC_CHANNEL_8		= 0x7,
} HAL_ADC_Channel;


typedef enum {
	HAL_ADC_REF_INTERNAL	= 0x0,
	HAL_ADC_REF_EXTERNAL	= 0x1,
} HAL_ADC_RefSource;


typedef struct {
	ANALOG_REG_TypeDef	*Instance;

	HAL_ADC_Channel		Channel;

	HAL_ADC_RefSource	Ref;
} HAL_ADC_TypeDef;


void HAL_ADC_Init(HAL_ADC_TypeDef *AdcTypeDef);


void HAL_ADC_Start(HAL_ADC_TypeDef *AdcTypeDef);

void HAL_ADC_Stop(HAL_ADC_TypeDef *AdcTypeDef);


void HAL_ADC_Start_Continuous(HAL_ADC_TypeDef *AdcTypeDef);

void HAL_ADC_Stop_Continuous(HAL_ADC_TypeDef *AdcTypeDef);


bool HAL_ADC_ValueAvailable(HAL_ADC_TypeDef *AdcTypeDef);


uint16_t HAL_ADC_GetValue(HAL_ADC_TypeDef *AdcTypeDef);


#endif