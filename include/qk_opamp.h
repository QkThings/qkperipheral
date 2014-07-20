#ifndef QK_OPAMP_H
#define QK_OPAMP_H

typed uint32_t qk_opamp;

typedef enum qk_opamp_config
{
	QK_OMAMP_CONFIG_UNITY_GAIN,
	QK_OMAMP_CONFIG_NON_INVERTING,
	QK_OMAMP_CONFIG_INVERTING
} qk_opamp_config;


void qk_opamp_enable(qk_opamp opamp, qk_opamp_config config);
void qk_opamp_disable(qk_opamp opamp);

#endif

