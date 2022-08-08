#include "../Inc/hal.h"







__weak uint64_t HAL_GetCpuTick(void)
{
	return (uint64_t)rdtime();
}


__weak uint32_t HAL_GetCpuTimeMs(void)
{
	return (uint64_t)rdtime() / (CPU_CLOCK_MHZ * 1000);
}


__weak uint32_t HAL_GetCpuTimeMcs(void)
{
	return (uint64_t)rdtime() / CPU_CLOCK_MHZ;
}


__weak void HAL_Delay(uint32_t DelayMs)
{
	uint32_t tickstart = HAL_GetCpuTimeMs();
	uint32_t wait = DelayMs;

	while ((HAL_GetCpuTimeMs() - tickstart) < wait);
}



void HAL_InitClock() {
	PM->CLK_AHB_SET = PM_CLOCK_CPU_M | PM_CLOCK_EEPROM_M | PM_CLOCK_RAM_M;
	PM->CLK_APB_M_SET = PM_CLOCK_PAD_CONFIG_M | PM_CLOCK_WU_M | PM_CLOCK_PM_M;
}