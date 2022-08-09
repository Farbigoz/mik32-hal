#include "../Inc/hal_timer32.h"


void HAL_TIMER32_Init(HAL_TIMER32_TypeDef *htim) {
	if (htim->Instance == TIMER32_0)
	{
		PM->CLK_APB_M_SET |= PM_CLOCK_TIMER32_0_M;
	}
	else if (htim->Instance == TIMER32_1)
	{
		PM->CLK_APB_P_SET |= PM_CLOCK_TIMER32_1_M;
	}
	else if (htim->Instance == TIMER32_2)
	{
		PM->CLK_APB_P_SET |= PM_CLOCK_TIMER32_2_M;
	}
	else
	{
		return;
	}

	htim->Instance->Enable = TIMER32_RESET_VALUE_M;

	htim->Instance->Prescaler = htim->Init.Prescaler;
	htim->Instance->Top = htim->Init.Period;

	htim->Instance->Control = 0x0;
	htim->Instance->Control |= htim->Init.CountMode << TIMER32_CONTROL_MODE_S;

	for (uint8_t i = 0; i < TIMER32_CHANNEL_COUNT; i++) {
		htim->Instance->Channels[i].Control = 0x0;
		htim->Instance->Channels[i].Control |= htim->Channel[i].Mode << TIMER32_CH_CONTROL_MODE_S;

		switch (htim->Channel[i].Mode) {
			case HAL_TIMER32_CHANNEL_MODE_CAPTURE:
				htim->Instance->Channels[i].Control |= htim->Channel[i].CaptureMode << TIMER32_CH_CONTROL_CAPTURE_EDGE_S;
				break;

			case HAL_TIMER32_CHANNEL_MODE_PWM:
				htim->Instance->Channels[i].Control |= htim->Channel[i].PwmType << TIMER32_CH_CONTROL_INVERTED_PWM_S;

			case HAL_TIMER32_CHANNEL_MODE_COMPARE:
				htim->Instance->Channels[i].OCR = htim->Channel[i].Compare;
				break;
		}
	}
}


inline  void HAL_TIMER32_Start(HAL_TIMER32_TypeDef *htim) {
	htim->Instance->Enable = TIMER32_ENABLE_M;
}


inline  void HAL_TIMER32_Stop(HAL_TIMER32_TypeDef *htim) {
	htim->Instance->Enable = TIMER32_DISABLE_M;
}


inline  void HAL_TIMER32_Reset(HAL_TIMER32_TypeDef *htim) {
	htim->Instance->Enable |= TIMER32_RESET_VALUE_M;
}


inline void HAL_TIMER32_ChannelStart(HAL_TIMER32_TypeDef *htim, uint32_t channel) {
	if (channel > TIMER32_CHANNEL_COUNT) { return; }
	htim->Instance->Channels[channel].Control |= TIMER32_CH_CONTROL_ENABLE_M;
}


inline void HAL_TIMER32_ChannelStop(HAL_TIMER32_TypeDef *htim, uint32_t channel) {
	if (channel > TIMER32_CHANNEL_COUNT) { return; }
	htim->Instance->Channels[channel].Control |= TIMER32_CH_CONTROL_DISABLE_M;
}


inline uint32_t HAL_TIMER32_GetValue(HAL_TIMER32_TypeDef *htim) {
	return htim->Instance->Value;
}


inline void HAL_TIMER32_ChannelSetCompare(HAL_TIMER32_TypeDef *htim, uint32_t channel, uint32_t compare) {
	if (channel > TIMER32_CHANNEL_COUNT) { return; }
	htim->Instance->Channels[channel].OCR = compare;
}


inline uint32_t HAL_TIMER32_ChannelGetCompare(HAL_TIMER32_TypeDef *htim, uint32_t channel) {
	if (channel > TIMER32_CHANNEL_COUNT) { return 0; }
	return htim->Instance->Channels[channel].OCR;
}
