#ifndef HAL_TIMER_32_H
#define HAL_TIMER_32_H

#ifdef __cplusplus
extern "C" {
#endif

#include <epic.h>
#include <timer32.h>

#include "hal.h"


#define TIMER32_CHANNEL_COUNT			4

#define TIMER32_CH1						0x0
#define TIMER32_CH2						0x1
#define TIMER32_CH3						0x2
#define TIMER32_CH4						0x3


#define TIMER32_IRQ_OVERFLOW            0
#define TIMER32_IRQ_UNDERFLOW            1
#define TIMER32_IRQ_CAPTURE(channel)    (2 + channel)
#define TIMER32_IRQ_COMPARE(channel)    (6 + channel)


#define __TIMER32_IRQ_IS(htim, irq)        (htim->Instance->IntFlags & (1 << (irq)))
#define __TIMER32_CLEAN_IRQ(htim, irq)    htim->Instance->IntClear = 1 << (irq)


typedef enum {
	HAL_TIMER32_COUNTER_UP				= 0x0,
	HAL_TIMER32_COUNTER_DOWN			= 0x1,
	HAL_TIMER32_COUNTER_BIDIRECT		= 0x2,
} HAL_TIMER32_CounterMode;


typedef enum {
	HAL_TIMER32_CHANNEL_MODE_COMPARE	= 0x1,
	HAL_TIMER32_CHANNEL_MODE_CAPTURE	= 0x2,
	HAL_TIMER32_CHANNEL_MODE_PWM		= 0x3,
} HAL_TIMER32_ChannelMode;


typedef enum {
	HAL_TIMER32_CHANNEL_CAPTURE_FRONT	= 0x0,
	HAL_TIMER32_CHANNEL_CAPTURE_SLICE	= 0x1,
} HAL_TIMER32_ChannelCaptureMode;


typedef enum {
	HAL_TIMER32_CHANNEL_PWM_NORMAL		= 0x0,
	HAL_TIMER32_CHANNEL_PWM_INVERT		= 0x1,
} HAL_TIMER32_ChannelPWMType;


typedef enum {
	HAL_TIMER32_INTERRUPT_NONE = 0,
	HAL_TIMER32_INTERRUPT_OVERFLOW = 1 << 0,
	HAL_TIMER32_INTERRUPT_UNDERFLOW = 1 << 1,
} HAL_TIMER32_Interrupt;


typedef enum {
	HAL_TIMER32_CHANNEL_INTERRUPT_NONE = 0,
	HAL_TIMER32_CHANNEL_INTERRUPT_CAPTURE = 1 << 2,
	HAL_TIMER32_CHANNEL_INTERRUPT_COMPARE = 1 << 6,
} HAL_TIMER32_ChanelInterrupt;


typedef struct {
	uint32_t						Period;
	uint32_t						Prescaler;

	// source
	HAL_TIMER32_CounterMode			CountMode;

	HAL_TIMER32_Interrupt			Interrupt;
} HAL_TIMER32_InitTypeDef;


typedef struct {
	uint32_t						Compare;

	HAL_TIMER32_ChannelMode			Mode;

	HAL_TIMER32_ChannelCaptureMode	CaptureMode;

	HAL_TIMER32_ChannelPWMType		PwmType;

	HAL_TIMER32_ChanelInterrupt		Interrupt;
} HAL_TIMER32_ChannelTypeDef;


typedef struct {
	TIMER32_TypeDef					*Instance;

	HAL_TIMER32_InitTypeDef			Init;

	HAL_TIMER32_ChannelTypeDef		Channel[TIMER32_CHANNEL_COUNT];
} HAL_TIMER32_TypeDef;


void HAL_TIMER32_Init(HAL_TIMER32_TypeDef *htim);


void HAL_TIMER32_Start(HAL_TIMER32_TypeDef *htim);


void HAL_TIMER32_Stop(HAL_TIMER32_TypeDef *htim);


void HAL_TIMER32_Reset(HAL_TIMER32_TypeDef *htim);


void HAL_TIMER32_ChannelStart(HAL_TIMER32_TypeDef *htim, uint32_t channel);


void HAL_TIMER32_ChannelStop(HAL_TIMER32_TypeDef *htim, uint32_t channel);


uint32_t HAL_TIMER32_GetValue(HAL_TIMER32_TypeDef *htim);


void HAL_TIMER32_ChannelSetCompare(HAL_TIMER32_TypeDef *htim, uint32_t channel, uint32_t compare);


uint32_t HAL_TIMER32_ChannelGetCompare(HAL_TIMER32_TypeDef *htim, uint32_t channel);


void HAL_TIMER32_IRQ_OverflowCallback(HAL_TIMER32_TypeDef *htim);

void HAL_TIMER32_IRQ_UnderflowCallback(HAL_TIMER32_TypeDef *htim);

void HAL_TIMER32_IRQ_ChannelCaptureCallback(HAL_TIMER32_TypeDef *htim, uint32_t channel);

void HAL_TIMER32_IRQ_ChannelCompareCallback(HAL_TIMER32_TypeDef *htim, uint32_t channel);


void HAL_TIMER32_IRQHandler(HAL_TIMER32_TypeDef *htim);


#ifdef __cplusplus
}
#endif

#endif