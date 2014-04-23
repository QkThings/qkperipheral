#ifndef QK_PERIPHERAL_P_H
#define QK_PERIPHERAL_P_H

#ifndef INIT_CLKFREQ
#error "INIT_CLKFREQ is not defined"
#endif

typedef struct qk_peripheral
{
	int clk_freq;
} qk_peripheral;

#define QKPERIPHERAL_INIT { .clk_freq = INIT_CLKFREQ }

extern qk_peripheral _qk_peripheral;

#endif
