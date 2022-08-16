#include "../lib/mik32-hal/Inc/hal.h"
#include "../lib/mik32-hal/Inc/hal_gpio.h"
#include "../lib/mik32-hal/Inc/hal_timer32.h"
#include "../lib/mik32-hal/Inc/hal_gpio_macros.h"


HAL_TIMER32_TypeDef htim1 = {0};


void InitTimer() {
	htim1.Instance = TIMER32_2;
	htim1.Init.CountMode = HAL_TIMER32_COUNTER_UP;
	htim1.Init.Prescaler = 0;
	htim1.Init.Period = (CPU_CLOCK_MHZ * 1000000) / 32000;					// = 1000 ticks, 32 kHz

	htim1.Channel[HAL_TIMER32_CHANNEL_1].Mode = HAL_TIMER32_CHANNEL_MODE_PWM;
	htim1.Channel[HAL_TIMER32_CHANNEL_1].Compare = 0;

	htim1.Channel[HAL_TIMER32_CHANNEL_2].Mode = HAL_TIMER32_CHANNEL_MODE_PWM;
	htim1.Channel[HAL_TIMER32_CHANNEL_2].PwmType = HAL_TIMER32_CHANNEL_PWM_INVERT;
	htim1.Channel[HAL_TIMER32_CHANNEL_2].Compare = 0;

	HAL_TIMER32_Init(&htim1);
}



void InitGpio() {
	HAL_GPIO_TypeDef htim1_ch1_Gpio = {0};
	HAL_GPIO_TypeDef htim1_ch2_Gpio = {0};

	__HAL_GPIO_INIT_TIMER32_2_CH1_PWM(&htim1_ch1_Gpio);
	HAL_GPIO_Init(&htim1_ch1_Gpio);

	__HAL_GPIO_INIT_TIMER32_2_CH2_PWM(&htim1_ch2_Gpio);
	HAL_GPIO_Init(&htim1_ch2_Gpio);
}


int main() {
	HAL_InitClock();

	InitTimer();
	InitGpio();

	HAL_TIMER32_Start(&htim1);
	HAL_TIMER32_ChannelStart(&htim1, HAL_TIMER32_CHANNEL_1);
	HAL_TIMER32_ChannelStart(&htim1, HAL_TIMER32_CHANNEL_2);

	uint32_t compare = 0;

	while (1) {
		HAL_TIMER32_ChannelSetCompare(&htim1, HAL_TIMER32_CHANNEL_1, compare);
		HAL_TIMER32_ChannelSetCompare(&htim1, HAL_TIMER32_CHANNEL_2, compare);

		if (++compare == htim1.Init.Period){
			compare = 0;
		}

		HAL_Delay(1);
	}
}

