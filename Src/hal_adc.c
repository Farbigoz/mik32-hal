#include "../Inc/hal_adc.h"


void HAL_ADC_Init(HAL_ADC_TypeDef *AdcTypeDef) {
	// Включение тактирования аналоговых блоков
	PM->CLK_APB_P_SET |= 1 << 15;

	// Конфигурация АЦП

	// Управление перезапуском АЦП
	// Источник опорного напряжения
	// Источник опорного напряжения
	// Канал АЦП
	ANALOG_REG->ADC_CONFIG =	1 << ADC_RESETn_S				|	\
								AdcTypeDef->Ref << ADC_EXTREF_S	|	\
								1 << ADC_EXTPAD_EN_S			|	\
								AdcTypeDef->Channel << ADC_SEL_S;
}


inline void HAL_ADC_Enable(HAL_ADC_TypeDef *AdcTypeDef) {
	ANALOG_REG->ADC_CONFIG |= 1 << ADC_EN_S;
}


inline void HAL_ADC_Disable(HAL_ADC_TypeDef *AdcTypeDef) {
	ANALOG_REG->ADC_CONFIG &= ~(1 << ADC_EN_S);
}


inline void HAL_ADC_Start(HAL_ADC_TypeDef *AdcTypeDef) {
	ANALOG_REG->ADC_SINGLE = 1;
}

inline void HAL_ADC_Stop(HAL_ADC_TypeDef *AdcTypeDef) {
	ANALOG_REG->ADC_SINGLE = 0;
}


inline void HAL_ADC_Start_Continuous(HAL_ADC_TypeDef *AdcTypeDef) {
	ANALOG_REG->ADC_CONTINIUS = 1;
}

inline void HAL_ADC_Stop_Continuous(HAL_ADC_TypeDef *AdcTypeDef) {
	ANALOG_REG->ADC_CONTINIUS = 0;
}


inline bool HAL_ADC_ValueAvailable(HAL_ADC_TypeDef *AdcTypeDef) {
	return ANALOG_REG->ADC_VALID != 0;
}


inline uint16_t HAL_ADC_GetValue(HAL_ADC_TypeDef *AdcTypeDef) {
	return ANALOG_REG->ADC_VALUE & 0xFFF;
}
