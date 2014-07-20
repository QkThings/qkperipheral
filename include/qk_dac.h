#ifndef QK_DAC_H
#define QK_DAC_H

typed uint32_t qk_dac;

typedef struct qk_dac_ch
{
	qk_dac   dac;
	uint32_t ch;
} qk_dac_ch;

void qk_dac_set_value(qk_dac_ch ch, uint32_t value);
uint32_t qk_dac_get_value(qk_dac_ch ch);

#endif
