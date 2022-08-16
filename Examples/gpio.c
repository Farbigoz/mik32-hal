#include "../lib/mik32-hal/Inc/hal.h"
#include "../lib/mik32-hal/Inc/hal_gpio.h"
#include "../lib/mik32-hal/Inc/hal_gpio_macros.h"




HAL_GPIO_TypeDef LED_1;
HAL_GPIO_TypeDef LED_2;


void InitGpio() {
	/* Configure LED_1 */
	LED_1.PortInstance = GPIO_0;
	LED_1.Pin = HAL_GPIO_PIN_0;
	LED_1.Type = HAL_PIN_TYPE_IO;
	LED_1.Mode = HAL_PIN_MODE_OUTPUT;
	LED_1.ActiveState = HAL_PIN_ACTIVE_LO;

	HAL_GPIO_Init(&LED_1);

	/* Configure LED_2 */
	LED_2.PortInstance = GPIO_1;
	LED_2.Pin = HAL_GPIO_PIN_0;
	LED_2.Type = HAL_PIN_TYPE_IO;
	LED_2.Mode = HAL_PIN_MODE_OUTPUT;
	LED_2.ActiveState = HAL_PIN_ACTIVE_HI;

	HAL_GPIO_Init(&LED_2);

	/* OR */

	/* Configure LED_1 */
	// LED_1.ActiveState = PIN_ACTIVE_LO;
	// __HAL_INIT_GPIO(&LED_1, GPIO_0, GPIO_PIN_0, PIN_TYPE_IO, PIN_MODE_OUTPUT);

	/* Configure LED_2 */
	// __HAL_INIT_GPIO(&LED_1, GPIO_1, GPIO_PIN_0, PIN_TYPE_IO, PIN_MODE_OUTPUT);
}


int _main_gpio() {
	HAL_InitClock();

	InitGpio();

	while (1) {
		HAL_GPIO_WritePin(&LED_1, true);
		HAL_GPIO_WritePin(&LED_2, true);

		HAL_Delay(100);

		HAL_GPIO_WritePin(&LED_1, false);
		HAL_GPIO_WritePin(&LED_2, false);

		HAL_Delay(100);
	}
}

