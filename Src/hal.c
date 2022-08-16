#include "../Inc/hal.h"


uint64_t __div64_32(uint64_t rem, uint32_t base)
{
	uint64_t b = base;
	uint64_t res, d = 1;
	uint32_t high = rem >> 32;

	/* Reduce the thing a bit first */
	res = 0;
	if (high >= base) {
		high /= base;
		res = (uint64_t) high << 32;
		rem -= (uint64_t) (high*base) << 32;
	}

	while ((int64_t)b > 0 && b < rem) {
		b = b+b;
		d = d+d;
	}

	do {
		if (rem >= b) {
			rem -= b;
			res += d;
		}
		b >>= 1;
		d >>= 1;
	} while (d);

	return res;
}



inline uint64_t HAL_GetCpuClock(void)
{
	return ((uint64_t)read_csr(timeh) << 32) | (uint64_t)read_csr(time);
}


__weak uint32_t HAL_GetCpuTimeMs(void)
{
	//return (uint32_t)HAL_GetCpuTick() / (CPU_CLOCK_MHZ * 1000);
	return __div64_32(HAL_GetCpuClock(), CPU_CLOCK_MHZ * 1000);
}


__weak uint32_t HAL_GetCpuTimeMcs(void)
{
	return __div64_32(HAL_GetCpuClock(), CPU_CLOCK_MHZ);
}


__weak void HAL_Delay(uint32_t DelayMs)
{
	uint64_t delayTicks = CPU_CLOCK_MHZ * 1000 * DelayMs;
	uint64_t tickEnd = HAL_GetCpuClock() + delayTicks;
	while (HAL_GetCpuClock() < tickEnd);
}


__weak void HAL_DelayMcs(uint32_t DelayMcs)
{
	uint64_t delayTicks = CPU_CLOCK_MHZ * DelayMcs;
	uint64_t tickEnd = HAL_GetCpuClock() + delayTicks;
	while (HAL_GetCpuClock() < tickEnd);
}



void HAL_InitClock() {
	PM->CLK_AHB_SET = PM_CLOCK_CPU_M | PM_CLOCK_EEPROM_M | PM_CLOCK_RAM_M;
	PM->CLK_APB_M_SET = PM_CLOCK_PAD_CONFIG_M | PM_CLOCK_WU_M | PM_CLOCK_PM_M;
}