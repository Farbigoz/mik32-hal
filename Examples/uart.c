#include <stdlib.h>
#include <string.h>

#include "../lib/mik32-hal/Inc/hal.h"
#include "../lib/mik32-hal/Inc/hal_uart.h"
#include "../lib/mik32-hal/Inc/hal_gpio.h"
#include "../lib/mik32-hal/Inc/hal_gpio_macros.h"

HAL_UART_HandleTypeDef huart1 = {0};


void InitUart() {
	huart1.Instance = UART_1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.TxState = HAL_UART_TX_ENABLE;
	huart1.Init.RxState = HAL_UART_RX_ENABLE;
	huart1.Init.TxPolarityInvert = HAL_UART_TX_PIN_NORMAL;
	huart1.Init.RxPolarityInvert = HAL_UART_RX_PIN_NORMAL;
	huart1.Init.DataPinSwap = HAL_UART_DATA_PIN_NORMAL;
	huart1.Init.Mode = HAL_UART_MODE_ASYNC;

	HAL_UART_Init(&huart1);
}


void InitGpio() {
	HAL_GPIO_TypeDef uartTxPin;
	HAL_GPIO_TypeDef uartRxPin;

	/* Configure UART 1 Tx pin */
	__HAL_GPIO_INIT_UART1_TXD(&uartTxPin);		// PORT 1, PIN 9
	HAL_GPIO_Init(&uartTxPin);

	/* Configure UART 1 Rx pin */
	__HAL_GPIO_INIT_UART1_RXD(&uartRxPin);		// PORT 1, PIN 8
	HAL_GPIO_Init(&uartRxPin);
}


int main() {
	HAL_InitClock();

	InitUart();
	InitGpio();

	char sendBuff[10];
	uint16_t value = 0;

	while (1) {
		for (uint8_t i = 0; i < 10; i++) { sendBuff[i] = 0; }	// Clean send buff
		itoa(value, sendBuff, 10);								// Write number to send buff
		sendBuff[strlen(sendBuff)] = '\n';						// Add 'new line' to send buff

		HAL_UART_Transmit(&huart1, (uint8_t *)sendBuff, strlen(sendBuff));

		if (++value == 1000) {
			value = 0;
		}

		HAL_Delay(10);
	}
}