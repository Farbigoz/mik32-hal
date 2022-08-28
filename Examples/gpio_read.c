#include <hal.h>
#include <hal_gpio.h>
#include <hal_gpio_macros.h>


HAL_GPIO_TypeDef LED;
HAL_GPIO_TypeDef INPUT;


void InitGpio() {
	/* Configure LED_1 */
	LED.PortInstance = GPIO_1;
	LED.Pin = HAL_GPIO_PIN_0;
	LED.Type = HAL_PIN_TYPE_IO;
	LED.Mode = HAL_PIN_MODE_OUTPUT;
	LED.ActiveState = HAL_PIN_ACTIVE_LO;

	HAL_GPIO_Init(&LED);

	/* Configure LED_2 */
	INPUT.PortInstance = GPIO_1;
	INPUT.Pin = HAL_GPIO_PIN_1;
	INPUT.Type = HAL_PIN_TYPE_IO;
	INPUT.Mode = HAL_PIN_MODE_INPUT;

	HAL_GPIO_Init(&INPUT);

	/* OR */

	/* Configure LED_1 */
	// LED.ActiveState = PIN_ACTIVE_LO;
	// __HAL_INIT_GPIO(&LED, GPIO_1, GPIO_PIN_0, PIN_TYPE_IO, PIN_MODE_OUTPUT);

	/* Configure LED_2 */
	// __HAL_INIT_GPIO(&INPUT, GPIO_1, GPIO_PIN_1, PIN_TYPE_IO, PIN_MODE_INPUT);
}


int _main_gpio_read() {
	HAL_InitClock();

	InitGpio();

	while (1) {
		if (HAL_GPIO_ReadPin(&INPUT)) {
			HAL_GPIO_WritePin(&LED, true);
		} else {
			HAL_GPIO_WritePin(&LED, false);
		}
	}
}

