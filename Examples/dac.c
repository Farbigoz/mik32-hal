#include "../lib/mik32-hal/Inc/hal.h"
#include "../lib/mik32-hal/Inc/hal_dac.h"

HAL_DAC_TypeDef dac1 = {0};


void InitAdc() {
	dac1.Channel = HAL_DAC_CHANNEL_1;
	dac1.Ref = HAL_DAC_REF_INTERNAL;
	dac1.FreqDivider = 31;

	HAL_DAC_Init(&dac1);
}



int main() {
	HAL_InitClock();

	InitAdc();

	uint16_t dacValue = 0;

	HAL_DAC_Enable(&dac1);

	while (1) {
		HAL_DAC_SetValue(&dac1, dacValue);
		dacValue += 0xf;

		HAL_Delay(10);
	}
}