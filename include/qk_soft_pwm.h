#ifndef QK_SOFT_PWM_H
#define QK_SOFT_PWM_H

void qk_soft_pwm_enable();
void qk_soft_pwm_disable();
void qk_soft_pwm_set_period(uint32_t period);
//void qk_soft_pwm_set_duty_cycle(qk_gpio_pin pin, uint16_t duty_cycle);

#endif
