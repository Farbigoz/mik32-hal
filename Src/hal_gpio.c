#include "../Inc/hal_gpio.h"


void HAL_GPIO_Init(HAL_GPIO_TypeDef *GpioTypeDef) {
	volatile uint32_t *gpioPadCfg;

	// Адрес конфигурации порта
	if (GpioTypeDef->PortInstance == GPIO_0)
	{
		PM->CLK_APB_P_SET |= PM_CLOCK_GPIO_0_M;
		gpioPadCfg = &PAD_CONFIG->PORT_0_CFG;
	}
	else if (GpioTypeDef->PortInstance == GPIO_1)
	{
		PM->CLK_APB_P_SET |= PM_CLOCK_GPIO_1_M;
		gpioPadCfg = &PAD_CONFIG->PORT_1_CFG;
	}
	else if (GpioTypeDef->PortInstance == GPIO_2)
	{
		PM->CLK_APB_P_SET |= PM_CLOCK_GPIO_2_M;
		gpioPadCfg = &PAD_CONFIG->PORT_2_CFG;
	}
	else {
		return;
	}

	// Очистка режима порта
	__GPIO_CLEAN_PAD_CONTROL(*gpioPadCfg, GpioTypeDef->Pin);

	// Установка режима порта
	switch (GpioTypeDef->Type) {
		case PIN_TYPE_IO:
			__GPIO_SET_PAD_CONTROL(*gpioPadCfg, GpioTypeDef->Pin, __PAD_CONTROL_1);
			break;

		case PIN_TYPE_ADC:
			__GPIO_SET_PAD_CONTROL(*gpioPadCfg, GpioTypeDef->Pin, __PAD_CONTROL_3);
			GpioTypeDef->Mode = PIN_MODE_INPUT;
			break;

		case PIN_TYPE_DAC:
			__GPIO_SET_PAD_CONTROL(*gpioPadCfg, GpioTypeDef->Pin, __PAD_CONTROL_0);
			GpioTypeDef->Mode = PIN_MODE_OUTPUT;
			break;

		case PIN_TYPE_TIMER:
			__GPIO_SET_PAD_CONTROL(*gpioPadCfg, GpioTypeDef->Pin, __PAD_CONTROL_2);
			break;

		case PIN_TYPE_INTERFACE_1:
			__GPIO_SET_PAD_CONTROL(*gpioPadCfg, GpioTypeDef->Pin, __PAD_CONTROL_0);
			break;

		case PIN_TYPE_INTERFACE_2:
			__GPIO_SET_PAD_CONTROL(*gpioPadCfg, GpioTypeDef->Pin, __PAD_CONTROL_2);
			break;
	}

	if (GpioTypeDef->Mode == PIN_MODE_INPUT)
	{
		GpioTypeDef->PortInstance->DIRECTION_IN = 1 << GpioTypeDef->Pin;
	}
	else if (GpioTypeDef->Mode == PIN_MODE_OUTPUT)
	{
		GpioTypeDef->PortInstance->DIRECTION_OUT = 1 << GpioTypeDef->Pin;
	}

	HAL_GPIO_WritePin(GpioTypeDef, false);
}


void HAL_GPIO_WritePin(HAL_GPIO_TypeDef *GpioTypeDef, bool PinState) {
	if (
			(GpioTypeDef->ActiveState == PIN_ACTIVE_HI && PinState == true) ||
			(GpioTypeDef->ActiveState == PIN_ACTIVE_LO && PinState == false)
	){
		GpioTypeDef->PortInstance->OUTPUT |= 1 << GpioTypeDef->Pin;
	} else {
		GpioTypeDef->PortInstance->OUTPUT &= ~(1 << GpioTypeDef->Pin);
	}
}


void HAL_GPIO_TogglePin(HAL_GPIO_TypeDef *GpioTypeDef) {
	GpioTypeDef->PortInstance->OUTPUT ^= 1 << GpioTypeDef->Pin;
}


bool HAL_GPIO_ReadPin(HAL_GPIO_TypeDef *GpioTypeDef) {
	bool state = (GpioTypeDef->PortInstance->SET & (1 << GpioTypeDef->Pin)) != 0;

	if (GpioTypeDef->ActiveState == PIN_ACTIVE_HI) {
		return state;
	} else {
		return !state;
	}
}
