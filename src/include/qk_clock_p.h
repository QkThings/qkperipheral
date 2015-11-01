#ifndef QK_CLOCK_P_H
#define QK_CLOCK_P_H

#ifndef MCU_CLKFREQ
#error "MCU_CLKFREQ is not defined"
#endif

typedef struct qk_clock
{
	long unsigned freq;
} qk_clock;

extern qk_clock _qk_clock;

#endif /* QK_CLOCK_P_H */
