#include "../Inc/irq.h"


__weak void TIMER32_0_IRQ() {}

__weak void UART_0_IRQ() {}

__weak void UART_1_IRQ() {}

__weak void SPI_0_IRQ() {}

__weak void SPI_1_IRQ() {}

__weak void GPIO_IRQ_IRQ() {}

__weak void I2C_0_IRQ() {}

__weak void I2C_1_IRQ() {}

__weak void WDT_IRQ() {}

__weak void TIMER16_0_IRQ() {}

__weak void TIMER16_1_IRQ() {}

__weak void TIMER16_2_IRQ() {}

__weak void TIMER32_1_IRQ() {}

__weak void TIMER32_2_IRQ() {}

__weak void EEPROM_IRQ() {}

__weak void SPIFI_IRQ() {}

__weak void RTC_IRQ() {}

__weak void WDT_DOM3_IRQ() {}

__weak void WDT_SPIFI_IRQ() {}

__weak void WDT_EEPROM_IRQ() {}

__weak void DMA_GLB_ERR_IRQ() {}

__weak void DMA_CHANNELS_IRQ() {}

__weak void FREQ_MON_IRQ() {}

__weak void PVD_AVCC_UNDER_IRQ() {}

__weak void PVD_AVCC_OVER_IRQ() {}

__weak void PVD_VCC_UNDER_IRQ() {}

__weak void PVD_VCC_OVER_IRQ() {}

__weak void BATTERY_NON_GOOD_IRQ() {}

__weak void BOR_IRQ() {}

__weak void TSENS_IRQ() {}

__weak void ADC_IRQ() {}

__weak void PROG_IRQ() {}


void trap_handler() {
	if (EPIC->STATUS & (1 << EPIC_TIMER32_0_INDEX)) {
		TIMER32_0_IRQ();
	}

	if (EPIC->STATUS & (1 << EPIC_TIMER32_1_INDEX)) {
		TIMER32_1_IRQ();
	}

	if (EPIC->STATUS & (1 << EPIC_GPIO_IRQ_INDEX)) {
		GPIO_IRQ_IRQ();
	}
	EPIC->CLEAR = 0xFF;
}


void EnableInterrupts() {
	set_csr(mstatus, MSTATUS_MIE);
	set_csr(mie, MIE_MEIE);
}


void DisableInterrupts() {
	clear_csr(mie, MIE_MEIE);
}

