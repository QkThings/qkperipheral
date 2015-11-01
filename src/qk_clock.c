#include "qk_clock.h"
#include "qk_clock_p.h"

qk_clock _qk_clock = {
		.freq = MCU_CLKFREQ
};

void qk_clock_update(unsigned long clk_freq)
{
	_qk_clock.freq = clk_freq;
}

long unsigned qk_clock_frequency(void)
{
	return _qk_clock.freq;
}
