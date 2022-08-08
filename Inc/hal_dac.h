#ifndef HAL_DAC_H
#define HAL_DAC_H

#include <analog_reg.h>

#include "hal.h"


#define __HAL_DAC_INSTANCE_FROM_CHANNEL(channel)	((channel == HAL_DAC_CHANNEL_1) ? (&ANALOG_REG->DAC0) : (&ANALOG_REG->DAC1))


typedef enum {
	HAL_DAC_CHANNEL_1,
	HAL_DAC_CHANNEL_2,
} HAL_DAC_Channel;


typedef enum {
	HAL_DAC_REF_INTERNAL	= (0 << DAC_CFG_EXTEN_S),
	HAL_DAC_REF_EXTERNAL	= (11 << DAC_CFG_EXTEN_S),
} HAL_DAC_RefSource;


typedef struct {
	HAL_DAC_Channel		Channel;

	HAL_DAC_RefSource	Ref;

	uint8_t				FreqDivider;
} HAL_DAC_TypeDef;


void HAL_DAC_Init(HAL_DAC_TypeDef *DacTypeDef);


void HAL_DAC_Enable(HAL_DAC_TypeDef *DacTypeDef);


void HAL_DAC_Disable(HAL_DAC_TypeDef *DacTypeDef);


void HAL_DAC_SetValue(HAL_DAC_TypeDef *DacTypeDef, uint16_t value);


#endif