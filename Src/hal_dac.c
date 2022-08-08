#include "../Inc/hal_dac.h"


void HAL_DAC_Init(HAL_DAC_TypeDef *DacTypeDef) {
	volatile DAC_TypeDef *dacInstance = __HAL_DAC_INSTANCE_FROM_CHANNEL(DacTypeDef->Channel);

	dacInstance->CFG = DAC_CFG_RESN_M | DacTypeDef->Ref | DAC_CFG_DIV(DacTypeDef->FreqDivider);
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