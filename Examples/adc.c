#include <stdlib.h>
#include <string.h>

#include "../lib/mik32-hal/Inc/hal.h"
#include "../lib/mik32-hal/Inc/hal_adc.h"
#include "../lib/mik32-hal/Inc/hal_uart.h"
#include "../lib/mik32-hal/Inc/hal_gpio.h"
#include "../lib/mik32-hal/Inc/hal_gpio_macros.h"

HAL_UART_HandleTypeDef huart1 = {0};
HAL_ADC_TypeDef hadc = {0};


void InitAdc() {
	hadc.Channel = HAL_ADC_CHANNEL_1;
	hadc.Ref = HAL_ADC_REF_INTERNAL;

	HAL_ADC_Init(&hadc);
}


void InitUart() {
	huart1.Instance = UART_1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.TxRxEnable = UART_TX_RX_ENABLE;
	huart1.Init.TxPolarityInvert = UART_TX_PIN_NORMAL;
	huart1.Init.RxPolarityInvert = UART_RX_PIN_NORMAL;
	huart1.Init.TxRxSwap = UART_TX_RX_PIN_NORMAL;
	huart1.Init.SyncMode = UART_MODE_ASYNC;

	HAL_UART_Init(&huart1);
}


void InitGpio() {
	HAL_GPIO_TypeDef adcPin;
	HAL_GPIO_TypeDef uartTxPin;
	HAL_GPIO_TypeDef uartRxPin;

	/* Configure ADC channel 1 pin */
	__HAL_GPIO_INIT_ADC_CH1(&adcPin);			// PORT 1, PIN 5

	/* Configure UART 1 Tx pin */
	__HAL_GPIO_INIT_UART1_TXD(&uartTxPin);		// PORT 1, PIN 9

	/* Configure UART 1 Rx pin */
	__HAL_GPIO_INIT_UART1_RXD(&uartRxPin);		// PORT 1, PIN 8
}


int main() {
	HAL_InitClock();

	InitAdc();
	InitUart();
	InitGpio();

	HAL_ADC_Start_Continuous(&hadc);

	char sendBuff[10] = {0};
	uint16_t adcValue = 0;

	while (1) {
		if (HAL_ADC_ValueAvailable(&hadc)) {
			adcValue = HAL_ADC_GetValue(&hadc);

			itoa(adcValue, sendBuff, 10);			// Add value to send buffer
			sendBuff[strlen(sendBuff)] = '\n';		// Add 'new line' to send buffer

			HAL_UART_Transmit(&huart1, (uint8_t *)sendBuff, strlen(sendBuff));

			HAL_Delay(10);
		}
	}
}