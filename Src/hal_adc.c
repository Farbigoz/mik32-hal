#include "../Inc/hal_adc.h"


void HAL_ADC_Init(HAL_ADC_TypeDef *AdcTypeDef) {
	PM->CLK_APB_P_SET |= 1 << 15;

	AdcTypeDef->Instance->ADC_CONFIG = 0x0;
	AdcTypeDef->Instance->ADC_CONFIG |= 1 << ADC_EN_S;
	AdcTypeDef->Instance->ADC_CONFIG |= 1 << ADC_RESETn_S;
	AdcTypeDef->Instance->ADC_CONFIG |= AdcTypeDef->Ref << ADC_EXTREF_S;
	AdcTypeDef->Instance->ADC_CONFIG |= 1 << ADC_EXTPAD_EN_S;
	AdcTypeDef->Instance->ADC_CONFIG |= AdcTypeDef->Channel << ADC_SEL_S;
}


void HAL_ADC_Start(HAL_ADC_TypeDef *AdcTypeDef) {
	AdcTypeDef->Instance->ADC_SINGLE = 1;
}

void HAL_ADC_Stop(HAL_ADC_TypeDef *AdcTypeDef) {
	AdcTypeDef->Instance->ADC_SINGLE = 0;
}


void HAL_ADC_Start_Continuous(HAL_ADC_TypeDef *AdcTypeDef) {
	AdcTypeDef->Instance->ADC_CONTINIUS = 1;
}

void HAL_ADC_Stop_Continuous(HAL_ADC_TypeDef *AdcTypeDef) {
	AdcTypeDef->Instance->ADC_CONTINIUS = 0;
}


bool HAL_ADC_ValueAvailable(HAL_ADC_TypeDef *AdcTypeDef) {
	return AdcTypeDef->Instance->ADC_VALID != 0;
}


uint16_t HAL_ADC_GetValue(HAL_ADC_TypeDef *AdcTypeDef) {
	return AdcTypeDef->Instance->ADC_VALUE & 0xFFF;
}