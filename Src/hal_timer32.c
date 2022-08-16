#include "../Inc/hal_timer32.h"


void HAL_TIMER32_Init(HAL_TIMER32_TypeDef *htim) {
	uint32_t epicInterruptShift = 0;
	bool enableEpicInterrupt = false;

	if (htim->Instance == TIMER32_0)
	{
		PM->CLK_APB_M_SET |= PM_CLOCK_TIMER32_0_M;
		epicInterruptShift = EPIC_TIMER32_0_INDEX;
	}
	else if (htim->Instance == TIMER32_1)
	{
		PM->CLK_APB_P_SET |= PM_CLOCK_TIMER32_1_M;
		epicInterruptShift = EPIC_TIMER32_1_INDEX;
	}
	else if (htim->Instance == TIMER32_2)
	{
		PM->CLK_APB_P_SET |= PM_CLOCK_TIMER32_2_M;
		epicInterruptShift = EPIC_TIMER32_2_INDEX;
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

	htim->Instance->IntMask = 0x0;
	htim->Instance->IntClear = 0xffffffff;

	htim->Instance->IntMask = htim->Init.Interrupt;
	enableEpicInterrupt = htim->Init.Interrupt != HAL_TIMER32_INTERRUPT_NONE;

	for (uint8_t i = 0; i < TIMER32_CHANNEL_COUNT; i++) {
		htim->Instance->Channels[i].Control = 0x0;
		htim->Instance->Channels[i].Control |= htim->Channel[i].Mode << TIMER32_CH_CONTROL_MODE_S;

		htim->Instance->IntMask |= htim->Channel[i].Interrupt << i;
		enableEpicInterrupt |= htim->Channel[i].Interrupt != HAL_TIMER32_CHANNEL_INTERRUPT_NONE;

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

	if (enableEpicInterrupt) {
		EPIC->MASK_SET = 1 << epicInterruptShift;
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


__weak void HAL_TIMER32_IRQ_OverflowCallback(HAL_TIMER32_TypeDef *htim) {};

__weak void HAL_TIMER32_IRQ_UnderflowCallback(HAL_TIMER32_TypeDef *htim) {};

__weak void HAL_TIMER32_IRQ_ChannelCaptureCallback(HAL_TIMER32_TypeDef *htim, uint32_t channel) {};

__weak void HAL_TIMER32_IRQ_ChannelCompareCallback(HAL_TIMER32_TypeDef *htim, uint32_t channel) {};



void HAL_TIMER32_IRQHandler(HAL_TIMER32_TypeDef *htim) {
	if (__TIMER32_IRQ_IS(htim, TIMER32_IRQ_OVERFLOW))
	{
		__TIMER32_CLEAN_IRQ(htim, TIMER32_IRQ_OVERFLOW);
		HAL_TIMER32_IRQ_OverflowCallback(htim);
	}

	else if (__TIMER32_IRQ_IS(htim, TIMER32_IRQ_UNDERFLOW))
	{
		__TIMER32_CLEAN_IRQ(htim, TIMER32_IRQ_UNDERFLOW);
		HAL_TIMER32_IRQ_UnderflowCallback(htim);
	}

	else if (__TIMER32_IRQ_IS(htim, TIMER32_IRQ_CAPTURE(TIMER32_CH1)))
	{
		__TIMER32_CLEAN_IRQ(htim, TIMER32_IRQ_CAPTURE(TIMER32_CH1));
		HAL_TIMER32_IRQ_ChannelCaptureCallback(htim, TIMER32_CH1);
	}
	else if (__TIMER32_IRQ_IS(htim, TIMER32_IRQ_CAPTURE(TIMER32_CH2)))
	{
		__TIMER32_CLEAN_IRQ(htim, TIMER32_IRQ_CAPTURE(TIMER32_CH2));
		HAL_TIMER32_IRQ_ChannelCaptureCallback(htim, TIMER32_CH2);
	}
	else if (__TIMER32_IRQ_IS(htim, TIMER32_IRQ_CAPTURE(TIMER32_CH3)))
	{
		__TIMER32_CLEAN_IRQ(htim, TIMER32_IRQ_CAPTURE(TIMER32_CH3));
		HAL_TIMER32_IRQ_ChannelCaptureCallback(htim, TIMER32_CH3);
	}
	else if (__TIMER32_IRQ_IS(htim, TIMER32_IRQ_CAPTURE(TIMER32_CH4)))
	{
		__TIMER32_CLEAN_IRQ(htim, TIMER32_IRQ_CAPTURE(TIMER32_CH4));
		HAL_TIMER32_IRQ_ChannelCaptureCallback(htim, TIMER32_CH4);
	}

	else if (__TIMER32_IRQ_IS(htim, TIMER32_IRQ_COMPARE(TIMER32_CH1)))
	{
		__TIMER32_CLEAN_IRQ(htim, TIMER32_IRQ_COMPARE(TIMER32_CH1));
		HAL_TIMER32_IRQ_ChannelCompareCallback(htim, TIMER32_CH1);
	}
	else if (__TIMER32_IRQ_IS(htim, TIMER32_IRQ_COMPARE(TIMER32_CH2)))
	{
		__TIMER32_CLEAN_IRQ(htim, TIMER32_IRQ_COMPARE(TIMER32_CH2));
		HAL_TIMER32_IRQ_ChannelCompareCallback(htim, TIMER32_CH2);
	}
	else if (__TIMER32_IRQ_IS(htim, TIMER32_IRQ_COMPARE(TIMER32_CH3)))
	{
		__TIMER32_CLEAN_IRQ(htim, TIMER32_IRQ_COMPARE(TIMER32_CH3));
		HAL_TIMER32_IRQ_ChannelCompareCallback(htim, TIMER32_CH3);
	}
	else if (__TIMER32_IRQ_IS(htim, TIMER32_IRQ_COMPARE(TIMER32_CH4)))
	{
		__TIMER32_CLEAN_IRQ(htim, TIMER32_IRQ_COMPARE(TIMER32_CH4));
		HAL_TIMER32_IRQ_ChannelCompareCallback(htim, TIMER32_CH4);
	}
}