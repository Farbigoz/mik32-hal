/*
 *  Copyright (c) 2022   Author: Столяров Сергей
 *                      Company: НПЦ Промэлектроника
 *                          URL: https://www.npcprom.ru/
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#include "../Inc/hal_irq.h"


void trap_handler() {
	if (__IRQ_IS(EPIC_TIMER32_0_INDEX))
	{
		HAL_TIMER32_0_IRQ();
		__CLEAN_IRQ(EPIC_TIMER32_0_INDEX);
	}
	else if (__IRQ_IS(EPIC_UART_0_INDEX))
	{
		HAL_USART_0_IRQ();
		__CLEAN_IRQ(EPIC_UART_0_INDEX);
	}
	else if (__IRQ_IS(EPIC_UART_1_INDEX))
	{
		HAL_USART_1_IRQ();
		__CLEAN_IRQ(EPIC_UART_1_INDEX);
	}
	else if (__IRQ_IS(EPIC_SPI_0_INDEX))
	{
		HAL_SPI_0_IRQ();
		__CLEAN_IRQ(EPIC_SPI_0_INDEX);
	}
	else if (__IRQ_IS(EPIC_SPI_1_INDEX))
	{
		HAL_SPI_1_IRQ();
		__CLEAN_IRQ(EPIC_SPI_1_INDEX);
	}
	else if (__IRQ_IS(EPIC_GPIO_IRQ_INDEX))
	{
		HAL_GPIO_IRQ_IRQ();
		__CLEAN_IRQ(EPIC_GPIO_IRQ_INDEX);
	}
	else if (__IRQ_IS(EPIC_TIMER32_1_INDEX))
	{
		HAL_TIMER32_1_IRQ();
		__CLEAN_IRQ(EPIC_TIMER32_1_INDEX);
	}
	else if (__IRQ_IS(EPIC_I2C_0_INDEX))
	{
		HAL_I2C_0_IRQ();
		__CLEAN_IRQ(EPIC_I2C_0_INDEX);
	}
	else if (__IRQ_IS(EPIC_I2C_1_INDEX))
	{
		HAL_I2C_1_IRQ();
		__CLEAN_IRQ(EPIC_I2C_1_INDEX);
	}
	else if (__IRQ_IS(EPIC_WDT_INDEX))
	{
		HAL_WDT_IRQ();
		__CLEAN_IRQ(EPIC_WDT_INDEX);
	}
	else if (__IRQ_IS(EPIC_TIMER16_0_INDEX))
	{
		HAL_TIMER16_0_IRQ();
		__CLEAN_IRQ(EPIC_TIMER16_0_INDEX);
	}
	else if (__IRQ_IS(EPIC_TIMER16_1_INDEX))
	{
		HAL_TIMER16_1_IRQ();
		__CLEAN_IRQ(EPIC_TIMER16_1_INDEX);
	}
	else if (__IRQ_IS(EPIC_TIMER16_2_INDEX))
	{
		HAL_TIMER16_2_IRQ();
		__CLEAN_IRQ(EPIC_TIMER16_2_INDEX);
	}
	else if (__IRQ_IS(EPIC_TIMER32_1_INDEX))
	{
		HAL_TIMER32_1_IRQ();
		__CLEAN_IRQ(EPIC_TIMER32_1_INDEX);
	}
	else if (__IRQ_IS(EPIC_TIMER32_2_INDEX))
	{
		HAL_TIMER32_2_IRQ();
		__CLEAN_IRQ(EPIC_TIMER32_2_INDEX);
	}
	else if (__IRQ_IS(EPIC_SPIFI_INDEX))
	{
		HAL_SPIFI_IRQ();
		__CLEAN_IRQ(EPIC_SPIFI_INDEX);
	}
	else if (__IRQ_IS(EPIC_RTC_INDEX))
	{
		HAL_RTC_IRQ();
		__CLEAN_IRQ(EPIC_RTC_INDEX);
	}
	else if (__IRQ_IS(EPIC_EEPROM_INDEX))
	{
		HAL_EEPROM_IRQ();
		__CLEAN_IRQ(EPIC_EEPROM_INDEX);
	}
	else if (__IRQ_IS(EPIC_WDT_DOM3_INDEX))
	{
		HAL_WDT_DOM3_IRQ();
		__CLEAN_IRQ(EPIC_WDT_DOM3_INDEX);
	}
	else if (__IRQ_IS(EPIC_WDT_SPIFI_INDEX))
	{
		HAL_WDT_SPIFI_IRQ();
		__CLEAN_IRQ(EPIC_WDT_SPIFI_INDEX);
	}
	else if (__IRQ_IS(EPIC_WDT_EEPROM_INDEX))
	{
		HAL_WDT_EEPROM_IRQ();
		__CLEAN_IRQ(EPIC_WDT_EEPROM_INDEX);
	}
	else if (__IRQ_IS(EPIC_DMA_GLB_ERR_INDEX))
	{
		HAL_DMA_GLB_ERR_IRQ();
		__CLEAN_IRQ(EPIC_DMA_GLB_ERR_INDEX);
	}
	else if (__IRQ_IS(EPIC_DMA_CHANNELS_INDEX))
	{
		HAL_DMA_CHANNELS_IRQ();
		__CLEAN_IRQ(EPIC_DMA_CHANNELS_INDEX);
	}
	else if (__IRQ_IS(EPIC_FREQ_MON_INDEX))
	{
		HAL_FREQ_MON_IRQ();
		__CLEAN_IRQ(EPIC_FREQ_MON_INDEX);
	}
	else if (__IRQ_IS(EPIC_PVD_AVCC_UNDER))
	{
		HAL_PVD_AVCC_UNDER_IRQ();
		__CLEAN_IRQ(EPIC_PVD_AVCC_UNDER);
	}
	else if (__IRQ_IS(EPIC_PVD_AVCC_OVER))
	{
		HAL_PVD_AVCC_OVER_IRQ();
		__CLEAN_IRQ(EPIC_PVD_AVCC_OVER);
	}
	else if (__IRQ_IS(EPIC_PVD_VCC_UNDER))
	{
		HAL_PVD_VCC_UNDER_IRQ();
		__CLEAN_IRQ(EPIC_PVD_VCC_UNDER);
	}
	else if (__IRQ_IS(EPIC_PVD_VCC_OVER))
	{
		HAL_PVD_VCC_OVER_IRQ();
		__CLEAN_IRQ(EPIC_PVD_VCC_OVER);
	}
	else if (__IRQ_IS(EPIC_BATTERY_NON_GOOD))
	{
		HAL_BATTERY_NON_GOOD_IRQ();
		__CLEAN_IRQ(EPIC_BATTERY_NON_GOOD);
	}
	else if (__IRQ_IS(EPIC_BOR_INDEX))
	{
		HAL_BOR_IRQ();
		__CLEAN_IRQ(EPIC_BOR_INDEX);
	}
	else if (__IRQ_IS(EPIC_TSENS_INDEX))
	{
		HAL_TSENS_IRQ();
		__CLEAN_IRQ(EPIC_TSENS_INDEX);
	}
	else if (__IRQ_IS(EPIC_ADC_INDEX))
	{
		HAL_ADC_IRQ();
		__CLEAN_IRQ(EPIC_ADC_INDEX);
	}
}


void HAL_IRQ_Init() {
	PM->CLK_APB_M_SET |= PM_CLOCK_EPIC_M;

	EPIC->MASK_CLEAR = 0xFFFF;
	EPIC->CLEAR = 0xFFFF;
}


void HAL_IRQ_Enable() {
	set_csr(mstatus, MSTATUS_MIE);
	set_csr(mie, MIE_MEIE);
}


void HAL_IRQ_Disable() {
	clear_csr(mie, MIE_MEIE);
}


__weak void HAL_TIMER32_0_IRQ() {}

__weak void HAL_USART_0_IRQ() {}

__weak void HAL_USART_1_IRQ() {}

__weak void HAL_SPI_0_IRQ() {}

__weak void HAL_SPI_1_IRQ() {}

__weak void HAL_GPIO_IRQ_IRQ() {}

__weak void HAL_I2C_0_IRQ() {}

__weak void HAL_I2C_1_IRQ() {}

__weak void HAL_WDT_IRQ() {}

__weak void HAL_TIMER16_0_IRQ() {}

__weak void HAL_TIMER16_1_IRQ() {}

__weak void HAL_TIMER16_2_IRQ() {}

__weak void HAL_TIMER32_1_IRQ() {}

__weak void HAL_TIMER32_2_IRQ() {}

__weak void HAL_EEPROM_IRQ() {}

__weak void HAL_SPIFI_IRQ() {}

__weak void HAL_RTC_IRQ() {}

__weak void HAL_WDT_DOM3_IRQ() {}

__weak void HAL_WDT_SPIFI_IRQ() {}

__weak void HAL_WDT_EEPROM_IRQ() {}

__weak void HAL_DMA_GLB_ERR_IRQ() {}

__weak void HAL_DMA_CHANNELS_IRQ() {}

__weak void HAL_FREQ_MON_IRQ() {}

__weak void HAL_PVD_AVCC_UNDER_IRQ() {}

__weak void HAL_PVD_AVCC_OVER_IRQ() {}

__weak void HAL_PVD_VCC_UNDER_IRQ() {}

__weak void HAL_PVD_VCC_OVER_IRQ() {}

__weak void HAL_BATTERY_NON_GOOD_IRQ() {}

__weak void HAL_BOR_IRQ() {}

__weak void HAL_TSENS_IRQ() {}

__weak void HAL_ADC_IRQ() {}

