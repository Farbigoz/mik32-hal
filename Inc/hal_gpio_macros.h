#ifndef HAL_GPIO_MAP_H
#define HAL_GPIO_MAP_H


#define __HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_INSTANCE, PIN, TYPE, MODE)										\
																do {												\
																	HAL_GPIO_INSTANCE.PortInstance = GPIO_INSTANCE;	\
																	HAL_GPIO_INSTANCE.Pin = PIN;					\
																	HAL_GPIO_INSTANCE.Type = TYPE;					\
																	HAL_GPIO_INSTANCE.Mode = MODE;					\
																} while (0)

/* DAC */


/* ADC */
/// @note ADC channel 1 pin - PORT 1, PIN 5
#define __HAL_GPIO_CONFIGURE_ADC_CH1(HAL_GPIO_INSTANCE)			\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_1, HAL_GPIO_PIN_5, HAL_PIN_TYPE_ADC, HAL_PIN_MODE_INPUT)

/// @note ADC channel 2 pin - PORT 1, PIN 7
#define __HAL_GPIO_CONFIGURE_ADC_CH2(HAL_GPIO_INSTANCE)			\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_1, HAL_GPIO_PIN_7, HAL_PIN_TYPE_ADC, HAL_PIN_MODE_INPUT)

/// @note ADC channel 3 pin - PORT 0, PIN 2
#define __HAL_GPIO_CONFIGURE_ADC_CH3(HAL_GPIO_INSTANCE)			\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_0, HAL_GPIO_PIN_2, HAL_PIN_TYPE_ADC, HAL_PIN_MODE_INPUT)

/// @note ADC channel 4 pin - PORT 0, PIN 4
#define __HAL_GPIO_CONFIGURE_ADC_CH4(HAL_GPIO_INSTANCE)			\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_0, HAL_GPIO_PIN_4, HAL_PIN_TYPE_ADC, HAL_PIN_MODE_INPUT)

/// @note ADC channel 5 pin - PORT 0, PIN 7
#define __HAL_GPIO_CONFIGURE_ADC_CH5(HAL_GPIO_INSTANCE)			\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_0, HAL_GPIO_PIN_7, HAL_PIN_TYPE_ADC, HAL_PIN_MODE_INPUT)

/// @note ADC channel 6 pin - PORT 0, PIN 9
#define __HAL_GPIO_CONFIGURE_ADC_CH6(HAL_GPIO_INSTANCE)			\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_0, HAL_GPIO_PIN_9, HAL_PIN_TYPE_ADC, HAL_PIN_MODE_INPUT)

/// @note ADC channel 7 pin - PORT 0, PIN 11
#define __HAL_GPIO_CONFIGURE_ADC_CH7(HAL_GPIO_INSTANCE)			\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_0, HAL_GPIO_PIN_11, HAL_PIN_TYPE_ADC, HAL_PIN_MODE_INPUT)

/// @note ADC channel 8 pin - PORT 0, PIN 13
#define __HAL_GPIO_CONFIGURE_ADC_CH8(HAL_GPIO_INSTANCE)			\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_0, HAL_GPIO_PIN_13, HAL_PIN_TYPE_ADC, HAL_PIN_MODE_INPUT)


/* UART 0 */
#define __HAL_GPIO_CONFIGURE_UART0_RTS(HAL_GPIO_INSTANCE)			\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_0, HAL_GPIO_PIN_8, HAL_PIN_TYPE_INTERFACE_1, HAL_PIN_MODE_OUTPUT)

#define __HAL_GPIO_CONFIGURE_UART0_CTS(HAL_GPIO_INSTANCE)			\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_0, HAL_GPIO_PIN_7, HAL_PIN_TYPE_INTERFACE_1, HAL_PIN_MODE_INPUT)

/// @note UART 0 Tx pin - PORT 0, PIN 6
#define __HAL_GPIO_CONFIGURE_UART0_TXD(HAL_GPIO_INSTANCE)			\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_0, HAL_GPIO_PIN_6, HAL_PIN_TYPE_INTERFACE_1, HAL_PIN_MODE_OUTPUT)

/// @note UART 0 Rx pin - PORT 0, PIN 5
#define __HAL_GPIO_CONFIGURE_UART0_RXD(HAL_GPIO_INSTANCE)			\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_0, HAL_GPIO_PIN_5, HAL_PIN_TYPE_INTERFACE_1, HAL_PIN_MODE_INPUT)


/* UART 1 */
#define __HAL_GPIO_CONFIGURE_UART1_RTS(HAL_GPIO_INSTANCE)			\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_1, HAL_GPIO_PIN_11, HAL_PIN_TYPE_INTERFACE_1, HAL_PIN_MODE_OUTPUT)

#define __HAL_GPIO_CONFIGURE_UART1_CTS(HAL_GPIO_INSTANCE)			\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_1, HAL_GPIO_PIN_10, HAL_PIN_TYPE_INTERFACE_1, HAL_PIN_MODE_INPUT)

/// @note UART 1 Tx pin - PORT 1, PIN 9
#define __HAL_GPIO_CONFIGURE_UART1_TXD(HAL_GPIO_INSTANCE)			\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_1, HAL_GPIO_PIN_9, HAL_PIN_TYPE_INTERFACE_1, HAL_PIN_MODE_OUTPUT)

/// @note UART 1 Rx pin - PORT 1, PIN 8
#define __HAL_GPIO_CONFIGURE_UART1_RXD(HAL_GPIO_INSTANCE)			\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_1, HAL_GPIO_PIN_8, HAL_PIN_TYPE_INTERFACE_1, HAL_PIN_MODE_INPUT)


/* TIMER32 1 */
//
#define __HAL_GPIO_CONFIGURE_TIMER32_1_CLK(HAL_GPIO_INSTANCE)				\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_0, HAL_GPIO_PIN_4, HAL_PIN_TYPE_TIMER, HAL_PIN_MODE_INPUT)

#define __HAL_GPIO_CONFIGURE_TIMER32_1_CH4_PWM(HAL_GPIO_INSTANCE)			\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_0, HAL_GPIO_PIN_3, HAL_PIN_TYPE_TIMER, HAL_PIN_MODE_OUTPUT)

#define __HAL_GPIO_CONFIGURE_TIMER32_1_CH3_PWM(HAL_GPIO_INSTANCE)			\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_0, HAL_GPIO_PIN_2, HAL_PIN_TYPE_TIMER, HAL_PIN_MODE_OUTPUT)

#define __HAL_GPIO_CONFIGURE_TIMER32_1_CH2_PWM(HAL_GPIO_INSTANCE)			\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_0, HAL_GPIO_PIN_1, HAL_PIN_TYPE_TIMER, HAL_PIN_MODE_OUTPUT)

#define __HAL_GPIO_CONFIGURE_TIMER32_1_CH1_PWM(HAL_GPIO_INSTANCE)			\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_0, HAL_GPIO_PIN_0, HAL_PIN_TYPE_TIMER, HAL_PIN_MODE_OUTPUT)

#define __HAL_GPIO_CONFIGURE_TIMER32_1_CH4_CAPTURE(HAL_GPIO_INSTANCE)		\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_0, HAL_GPIO_PIN_3, HAL_PIN_TYPE_TIMER, HAL_PIN_MODE_INPUT)

#define __HAL_GPIO_CONFIGURE_TIMER32_1_CH3_CAPTURE(HAL_GPIO_INSTANCE)		\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_0, HAL_GPIO_PIN_2, HAL_PIN_TYPE_TIMER, HAL_PIN_MODE_INPUT)

#define __HAL_GPIO_CONFIGURE_TIMER32_1_CH2_CAPTURE(HAL_GPIO_INSTANCE)		\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_0, HAL_GPIO_PIN_1, HAL_PIN_TYPE_TIMER, HAL_PIN_MODE_INPUT)

#define __HAL_GPIO_CONFIGURE_TIMER32_1_CH1_CAPTURE(HAL_GPIO_INSTANCE)	\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_0, HAL_GPIO_PIN_0, HAL_PIN_TYPE_TIMER, HAL_PIN_MODE_INPUT)


/* TIMER32 2 */
//
#define __HAL_GPIO_CONFIGURE_TIMER32_2_CLK(HAL_GPIO_INSTANCE)				\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_1, HAL_GPIO_PIN_4, HAL_PIN_TYPE_TIMER, HAL_PIN_MODE_INPUT)

#define __HAL_GPIO_CONFIGURE_TIMER32_2_CH4_PWM(HAL_GPIO_INSTANCE)			\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_1, HAL_GPIO_PIN_3, HAL_PIN_TYPE_TIMER, HAL_PIN_MODE_OUTPUT)

#define __HAL_GPIO_CONFIGURE_TIMER32_2_CH3_PWM(HAL_GPIO_INSTANCE)			\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_1, HAL_GPIO_PIN_2, HAL_PIN_TYPE_TIMER, HAL_PIN_MODE_OUTPUT)

#define __HAL_GPIO_CONFIGURE_TIMER32_2_CH2_PWM(HAL_GPIO_INSTANCE)			\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_1, HAL_GPIO_PIN_1, HAL_PIN_TYPE_TIMER, HAL_PIN_MODE_OUTPUT)

#define __HAL_GPIO_CONFIGURE_TIMER32_2_CH1_PWM(HAL_GPIO_INSTANCE)			\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_1, HAL_GPIO_PIN_0, HAL_PIN_TYPE_TIMER, HAL_PIN_MODE_OUTPUT)

#define __HAL_GPIO_CONFIGURE_TIMER32_2_CH4_CAPTURE(HAL_GPIO_INSTANCE)		\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_1, HAL_GPIO_PIN_3, HAL_PIN_TYPE_TIMER, HAL_PIN_MODE_INPUT)

#define __HAL_GPIO_CONFIGURE_TIMER32_2_CH3_CAPTURE(HAL_GPIO_INSTANCE)		\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_1, HAL_GPIO_PIN_2, HAL_PIN_TYPE_TIMER, HAL_PIN_MODE_INPUT)

#define __HAL_GPIO_CONFIGURE_TIMER32_2_CH2_CAPTURE(HAL_GPIO_INSTANCE)		\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_1, HAL_GPIO_PIN_1, HAL_PIN_TYPE_TIMER, HAL_PIN_MODE_INPUT)

#define __HAL_GPIO_CONFIGURE_TIMER32_2_CH1_CAPTURE(HAL_GPIO_INSTANCE)	\
		__HAL_GPIO_CONFIGURE(HAL_GPIO_INSTANCE, GPIO_1, HAL_GPIO_PIN_0, HAL_PIN_TYPE_TIMER, HAL_PIN_MODE_INPUT)



#endif