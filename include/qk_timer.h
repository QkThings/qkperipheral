#ifndef QK_TIMER_H
#define QK_TIMER_H

typedef enum qk_timer
{
	QK_TIMER_0,
	QK_TIMER_1,
	QK_TIMER_2,
	QK_TIMER_3,
	QK_TIMER_4,
	QK_TIMER_5,
} qk_timer;

typedef enum qk_timer_scale
{
	QK_TIMER_SCALE_USEC,
	QK_TIMER_SCALE_MSEC,
	QK_TIMER_SCALE_SEC
} qk_timer_scale;

int qk_timer_set_period(qk_timer timer, qk_timer_scale scale, unsigned int value);
int qk_timer_get_value(qk_timer timer);
void qk_timer_start(qk_timer timer);
void qk_timer_stop(qk_timer timer);
void qk_timer_restart(qk_timer timer);
void qk_timer_set_interrupt(qk_timer_interrupt id);

#endif

