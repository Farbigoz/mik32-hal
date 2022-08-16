#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <pad_config.h>
#include <gpio.h>

#include "hal.h"


#define __PAD_CONTROL_0		0x0
#define __PAD_CONTROL_1		0x1
#define __PAD_CONTROL_2		0x2
#define __PAD_CONTROL_3		0x3


#define __GPIO_CLEAN_PAD_CONTROL(padCfg, pinNum)				(padCfg &= ~(0b11 << (2 * pinNum)))
#define __GPIO_SET_PAD_CONTROL(padCfg, pinNum, control)			(padCfg |= control << (2 * pinNum))



/**
 * @brief	Номер пина
 */
typedef enum {
	HAL_GPIO_PIN_0		= 0x0,		///< Пин 0
	HAL_GPIO_PIN_1		= 0x1,		///< Пин 1
	HAL_GPIO_PIN_2		= 0x2,		///< Пин 2
	HAL_GPIO_PIN_3		= 0x3,		///< Пин 3
	HAL_GPIO_PIN_4		= 0x4,		///< Пин 4
	HAL_GPIO_PIN_5		= 0x5,		///< Пин 5
	HAL_GPIO_PIN_6		= 0x6,		///< Пин 6
	HAL_GPIO_PIN_7		= 0x7,		///< Пин 7
	HAL_GPIO_PIN_8		= 0x8,		///< Пин 8
	HAL_GPIO_PIN_9		= 0x9,		///< Пин 9
	HAL_GPIO_PIN_10		= 0xA,		///< Пин 10
	HAL_GPIO_PIN_11		= 0xB,		///< Пин 11
	HAL_GPIO_PIN_12		= 0xC,		///< Пин 12
	HAL_GPIO_PIN_13		= 0xD,		///< Пин 13
	HAL_GPIO_PIN_14		= 0xE,		///< Пин 14
	HAL_GPIO_PIN_15		= 0xF,		///< Пин 15
} HAL_GPIO_Pin;


/**
 * @brief	Режим работы пина
 */
typedef enum {
	HAL_PIN_MODE_INPUT,				///< Вход
	HAL_PIN_MODE_OUTPUT,			///< Выход
} HAL_GPIO_PinMode;


/**
 * @brief	Тип пина
 */
typedef enum {
	HAL_PIN_TYPE_IO,				///< Ввод/Вывол
	HAL_PIN_TYPE_ADC,				///< АЦП
	HAL_PIN_TYPE_TIMER,				///< Выходы/Входы таймеров (ШИМ, Захват)
	HAL_PIN_TYPE_INTERFACE_1,		///< Интерфейсы (UART, I2C, SPI)
	HAL_PIN_TYPE_INTERFACE_2,		///< Интерфейсы (UART, I2C, SPI)
} HAL_GPIO_PinType;


/* В документации есть, в SDK на микроконтроллер этих регистров нет

/// Нагрузочная возможность выхода
typedef enum {
	PIN_CURRENT_2_mA	= 0x0,		///< Макс нагрузка: 2 мА
	PIN_CURRENT_4_mA	= 0x1,		///< Макс нагрузка: 4 мА
	PIN_CURRENT_8_mA	= 0x2,		///< Макс нагрузка: 8 мА
} HAL_GPIO_PinCurrent;


/// Резисторная подтяжка порта
typedef enum {
	PIN_RESISTOR_NONE		= 0x0,		///< Резистор подтяжки не подключён
	PIN_RESISTOR_PULLUP		= 0x1,		///< Резистор подтяжки подключён к питанию (50 кОм)
	PIN_RESISTOR_PULLDOWN	= 0x2,		///< Резистор подтяжки подключён к земле (50 кОм)
} HAL_GPIO_PinResistor;

*/


/**
 * @brief	Активный уровень сигнала
 */
typedef enum {
	HAL_PIN_ACTIVE_HI,			///< Активный уровень - высокий
	HAL_PIN_ACTIVE_LO,			///< Активный уровень - низкий
} HAL_GPIO_PinActiveState;


/**
 * @brief	Объявление структуры обработчкиа GPIO
 */
typedef struct
{
	GPIO_TypeDef			*PortInstance;		///< Экземпляр порта ввода/вывода
	HAL_GPIO_Pin			Pin;				///< Пин
	HAL_GPIO_PinType		Type;				///< Тип пина
	HAL_GPIO_PinMode		Mode;				///< Режим пина
	//HAL_GPIO_PinCurrent	Current;
	//HAL_GPIO_PinResistor	Resistor;
	HAL_GPIO_PinActiveState	ActiveState;		///< Активный уровень пина (Только для режима Ввод/Вывод)
} HAL_GPIO_TypeDef;


/**
 * @brief	Инициализация GPIO
 *
 * @param	hgpio - Экземпляр обработчкиа GPIO
 */
void HAL_GPIO_Init(HAL_GPIO_TypeDef *hgpio);


/**
 * @brief	Укороченная инициализация GPIO (Используется в hal_gpio_macros.h)
 *
 * @param	hgpio			- Экземпляр обработчкиа GPIO
 * @param	portInstance	- Экземпляр порта ввода/вывода
 * @param	pin				- Пин
 * @param	mode			- Режим пина
 * @param	type			- Тип пина
 */
void HAL_GPIO_ConfigInit(HAL_GPIO_TypeDef *hgpio, GPIO_TypeDef *portInstance, HAL_GPIO_Pin pin, HAL_GPIO_PinType type, HAL_GPIO_PinMode mode);


/**
 * @brief	Установка выхода пина
 *
 * @param	hgpio - Экземпляр обработчкиа GPIO
 * @param	state
 */
void HAL_GPIO_WritePin(HAL_GPIO_TypeDef *hgpio, bool state);


/**
 * @brief	Переключение выхода пина (вкл->выкл, выкл->вкл)
 *
 * @param	hgpio - Экземпляр обработчкиа GPIO
 */
void HAL_GPIO_TogglePin(HAL_GPIO_TypeDef *hgpio);


/**
 * @brief	Считывание пина
 *
 * @param	hgpio - Экземпляр обработчкиа GPIO
 *
 * @return	bool
 */
bool HAL_GPIO_ReadPin(HAL_GPIO_TypeDef *hgpio);


#ifdef __cplusplus
}
#endif


#endif