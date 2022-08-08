#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include <pad_config.h>
#include <gpio.h>

#include "hal.h"


#define __PAD_CONTROL_0		0x0
#define __PAD_CONTROL_1		0x1
#define __PAD_CONTROL_2		0x2
#define __PAD_CONTROL_3		0x3


#define __GPIO_CLEAN_PAD_CONTROL(padCfg, pinNum)				(padCfg &= ~(0b11 << (2 * pinNum)))
#define __GPIO_SET_PAD_CONTROL(padCfg, pinNum, control)			(padCfg |= control << (2 * pinNum))


// Константы
/*
/// Порты ввода/вывода
typedef enum {
	GPIO_PORT_0,				///< Порт 0
	GPIO_PORT_1,				///< Порт 1
	GPIO_PORT_2,				///< Порт 2
} HAL_GPIO_Port;
*/


/// Номер пинов
typedef enum {
	GPIO_PIN_0		= 0x0,		///< Пин 0
	GPIO_PIN_1		= 0x1,		///< Пин 1
	GPIO_PIN_2		= 0x2,		///< Пин 2
	GPIO_PIN_3		= 0x3,		///< Пин 3
	GPIO_PIN_4		= 0x4,		///< Пин 4
	GPIO_PIN_5		= 0x5,		///< Пин 5
	GPIO_PIN_6		= 0x6,		///< Пин 6
	GPIO_PIN_7		= 0x7,		///< Пин 7
	GPIO_PIN_8		= 0x8,		///< Пин 8
	GPIO_PIN_9		= 0x9,		///< Пин 9
	GPIO_PIN_10		= 0xA,		///< Пин 10
	GPIO_PIN_11		= 0xB,		///< Пин 11
	GPIO_PIN_12		= 0xC,		///< Пин 12
	GPIO_PIN_13		= 0xD,		///< Пин 13
	GPIO_PIN_14		= 0xE,		///< Пин 14
	GPIO_PIN_15		= 0xF,		///< Пин 15
} HAL_GPIO_Pin;


/// Режим
typedef enum {
	PIN_MODE_INPUT,				///< Режим пина - Вход
	PIN_MODE_OUTPUT,			///< Режим пина - Выход
} HAL_GPIO_PinMode;


typedef enum {
	PIN_TYPE_IO,
	PIN_TYPE_ADC,
	PIN_TYPE_DAC,
	PIN_TYPE_TIMER,
	PIN_TYPE_INTERFACE_1,
	PIN_TYPE_INTERFACE_2,
} HAL_GPIO_PinType;


/* В документации есть, по факту нет

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


/// Активный уровень сигнала
typedef enum {
	PIN_ACTIVE_HI,			///< Активный уровент - высокий
	PIN_ACTIVE_LO,			///< Активный уровень - низкий
} HAL_GPIO_PinActiveState;




typedef struct
{
	//HAL_GPIO_Port			Port;
	GPIO_TypeDef			*PortInstance;
	HAL_GPIO_Pin			Pin;
	HAL_GPIO_PinMode		Mode;
	HAL_GPIO_PinType		Type;
	//HAL_GPIO_PinCurrent	Current;
	//HAL_GPIO_PinResistor	Resistor;
	HAL_GPIO_PinActiveState	ActiveState;			///< Only for 'PIN_TYPE_IO'
} HAL_GPIO_TypeDef;


void HAL_GPIO_Init(HAL_GPIO_TypeDef *TypeDef);


void HAL_GPIO_WritePin(HAL_GPIO_TypeDef *TypeDef, bool PinState);


void HAL_GPIO_TogglePin(HAL_GPIO_TypeDef *TypeDef);


bool HAL_GPIO_ReadPin(HAL_GPIO_TypeDef *TypeDef);


#endif