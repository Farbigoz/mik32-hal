#include <stdlib.h>
#include <string.h>

#include "../lib/mik32-hal/Inc/hal.h"
#include "../lib/mik32-hal/Inc/hal_dma.h"
#include "../lib/mik32-hal/Inc/hal_uart.h"
#include "../lib/mik32-hal/Inc/hal_gpio.h"
#include "../lib/mik32-hal/Inc/hal_gpio_macros.h"

HAL_UART_HandleTypeDef huart1 = {0};
HAL_DMA_TypeDef huart1TxDma = {0};
HAL_DMA_TypeDef huart1RxDma = {0};


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


void InitUartDma() {
	huart1TxDma.Channel = HAL_DMA_CHANNEL_1;
	huart1TxDma.Priority = HAL_DMA_HIGH_PRIORITY;

	HAL_UART_SetTxDma(&huart1, &huart1TxDma);

	huart1RxDma.Channel = HAL_DMA_CHANNEL_2;
	huart1RxDma.Priority = HAL_DMA_MAX_PRIORITY;

	HAL_UART_SetRxDma(&huart1, &huart1RxDma);
}


void InitGpio() {
	HAL_GPIO_TypeDef uartTxPin;
	HAL_GPIO_TypeDef uartRxPin;

	/* Configure UART 1 Tx pin */
	__HAL_GPIO_CONFIGURE_UART1_TXD(uartTxPin);		// PORT 1, PIN 9
	HAL_GPIO_Init(&uartTxPin);

	/* Configure UART 1 Rx pin */
	__HAL_GPIO_CONFIGURE_UART1_RXD(uartRxPin);		// PORT 1, PIN 8
	HAL_GPIO_Init(&uartRxPin);
}


int main() {
	HAL_InitClock();

	InitUart();
	InitUartDma();
	InitGpio();

	char receiveBuffer[10] = {0};
	char sendBuffer[10] = {0};
	uint8_t value = 0;

	HAL_UART_Receive_DMA(&huart1, (uint8_t *)receiveBuffer, 2);

	while (1) {
		if (HAL_DMA_Ready(&huart1RxDma)) {

			value = atoi(receiveBuffer);			// Chars to int
			value = value * value;						// Value square
			itoa(value, sendBuffer, 10);				// Value to chars
			sendBuffer[strlen(sendBuffer)] = '\n';		// Add 'new line' to chars

			HAL_UART_Transmit_DMA(&huart1, (uint8_t *)sendBuffer, strlen(sendBuffer));

			HAL_Delay(10);

			for (uint8_t i = 0; i < 10; i++) { receiveBuffer[i] = 0; }	// Clean buff
			for (uint8_t i = 0; i < 10; i++) { sendBuffer[i] = 0; }		// Clean buff

			HAL_UART_Receive_DMA(&huart1, (uint8_t *)receiveBuffer, 2);
		}
	}
}