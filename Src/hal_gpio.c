#include "../Inc/hal_gpio.h"


void HAL_GPIO_Init(HAL_GPIO_TypeDef *hgpio) {
	volatile uint32_t *gpioPadCfg;

	// Адрес конфигурации порта
	if (hgpio->PortInstance == GPIO_0)
	{
		PM->CLK_APB_P_SET |= PM_CLOCK_GPIO_0_M;
		gpioPadCfg = &PAD_CONFIG->PORT_0_CFG;
	}
	else if (hgpio->PortInstance == GPIO_1)
	{
		PM->CLK_APB_P_SET |= PM_CLOCK_GPIO_1_M;
		gpioPadCfg = &PAD_CONFIG->PORT_1_CFG;
	}
	else if (hgpio->PortInstance == GPIO_2)
	{
		PM->CLK_APB_P_SET |= PM_CLOCK_GPIO_2_M;
		gpioPadCfg = &PAD_CONFIG->PORT_2_CFG;
	}
	else {
		return;
	}

	// Очистка режима порта
	__GPIO_CLEAN_PAD_CONTROL(*gpioPadCfg, hgpio->Pin);

	// Установка режима порта
	switch (hgpio->Type) {
		case HAL_PIN_TYPE_IO:
			__GPIO_SET_PAD_CONTROL(*gpioPadCfg, hgpio->Pin, __PAD_CONTROL_1);
			break;

		case HAL_PIN_TYPE_ADC:
			__GPIO_SET_PAD_CONTROL(*gpioPadCfg, hgpio->Pin, __PAD_CONTROL_3);
			hgpio->Mode = HAL_PIN_MODE_INPUT;
			break;

		case HAL_PIN_TYPE_TIMER:
			__GPIO_SET_PAD_CONTROL(*gpioPadCfg, hgpio->Pin, __PAD_CONTROL_2);
			break;

		case HAL_PIN_TYPE_INTERFACE_1:
			__GPIO_SET_PAD_CONTROL(*gpioPadCfg, hgpio->Pin, __PAD_CONTROL_0);
			break;

		case HAL_PIN_TYPE_INTERFACE_2:
			__GPIO_SET_PAD_CONTROL(*gpioPadCfg, hgpio->Pin, __PAD_CONTROL_2);
			break;
	}

	if (hgpio->Mode == HAL_PIN_MODE_INPUT)
	{
		hgpio->PortInstance->DIRECTION_IN = 1 << hgpio->Pin;
	}
	else if (hgpio->Mode == HAL_PIN_MODE_OUTPUT)
	{
		hgpio->PortInstance->DIRECTION_OUT = 1 << hgpio->Pin;
	}

	HAL_GPIO_WritePin(hgpio, false);
}


void HAL_GPIO_ConfigInit(HAL_GPIO_TypeDef *hgpio, GPIO_TypeDef *portInstance, HAL_GPIO_Pin pin, HAL_GPIO_PinType type, HAL_GPIO_PinMode mode) {
	hgpio->PortInstance = portInstance;
	hgpio->Pin = pin;
	hgpio->Type = type;
	hgpio->Mode = mode;
	HAL_GPIO_Init(hgpio);
}


void HAL_GPIO_WritePin(HAL_GPIO_TypeDef *hgpio, bool PinState) {
	if (
			(hgpio->ActiveState == HAL_PIN_ACTIVE_HI && PinState == true) ||
			(hgpio->ActiveState == HAL_PIN_ACTIVE_LO && PinState == false)
	){
		hgpio->PortInstance->OUTPUT |= 1 << hgpio->Pin;
	} else {
		hgpio->PortInstance->OUTPUT &= ~(1 << hgpio->Pin);
	}
}


void HAL_GPIO_TogglePin(HAL_GPIO_TypeDef *hgpio) {
	hgpio->PortInstance->OUTPUT ^= 1 << hgpio->Pin;
}


bool HAL_GPIO_ReadPin(HAL_GPIO_TypeDef *hgpio) {
	bool state = (hgpio->PortInstance->SET & (1 << hgpio->Pin)) != 0;

	if (hgpio->ActiveState == HAL_PIN_ACTIVE_HI) {
		return state;
	} else {
		return !state;
	}
}
