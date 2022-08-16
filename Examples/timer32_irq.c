#include "../lib/mik32-hal/Inc/hal.h"
#include "../lib/mik32-hal/Inc/hal_irq.h"
#include "../lib/mik32-hal/Inc/hal_gpio.h"
#include "../lib/mik32-hal/Inc/hal_timer32.h"
#include "../lib/mik32-hal/Inc/hal_gpio_macros.h"


HAL_TIMER32_TypeDef htim1 = {0};

HAL_GPIO_TypeDef LedPin = {0};


void InitTimer() {
	htim1.Instance = TIMER32_0;
	htim1.Init.CountMode = HAL_TIMER32_COUNTER_UP;
	htim1.Init.Prescaler = 0;
	htim1.Init.Period = (CPU_CLOCK_MHZ * 1000000) / 10;					// = 10 Hz
	htim1.Init.Interrupt = HAL_TIMER32_INTERRUPT_OVERFLOW;

	HAL_TIMER32_Init(&htim1);
}


void InitGpio() {
	HAL_GPIO_ConfigInit(&LedPin, GPIO_1, HAL_GPIO_PIN_0, HAL_PIN_TYPE_IO, HAL_PIN_MODE_OUTPUT);
}


void HAL_TIMER32_0_IRQ() {
	HAL_TIMER32_IRQHandler(&htim1);
}


void HAL_TIMER32_IRQ_OverflowCallback(HAL_TIMER32_TypeDef *htim) {
	HAL_GPIO_TogglePin(&LedPin);
}


int main() {
	HAL_InitClock();
	HAL_IRQ_Init();

	InitTimer();
	InitGpio();

	HAL_TIMER32_Start(&htim1);
	HAL_IRQ_Enable();

	while (1);
}

