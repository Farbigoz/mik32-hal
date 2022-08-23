# HAL МК-32 Амур

Библиотека с открытым кодом для высокоуровнего взаимодействия с периферией микроконтроллера МК-32 Амур.

## Как использовать

- Создаём проект PlatformIO в VSCode или в Clion;
- В консоли переходим в каталог `$PROJECT_PATH\lib\`;
- Клонируем проект в дирректорию `lib` командой `git clone git@github.com:Farbigoz/mik32-hal.git`.

## Авторы

Библиотека была написана в стенах [**Научно-производственного центра Промэлектроника**](https://www.npcprom.ru/).

- Столяров Сергей

## Лицензия

Лицензия MIT [license.txt](license.txt)

## Исправленная версия тулчейна для PlatformIO

[**Ссылка на репозиторий**](https://github.com/Farbigoz/mik32-platformio).

### Список исправлений

- Исправление скрипта линкера для установки asm кода на правильный адрес вхождения прерывания
- Добавление поддержки других прошивальщиков (Проверены: J-Link, XDS100v2).
- Исправление кода python для правильной работы в режиме отладки (В режиме отладки не применялись параметры из файла platformio.ini).


