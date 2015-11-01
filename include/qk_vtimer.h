#ifndef QK_VTIMER_H
#define QK_VTIMER_H

typedef enum qk_vtimer_mode
{
	QK_VTIMER_MODE_SINGLE,
	QK_VTIMER_MODE_PERIODIC
} qk_vtimer_mode;

typedef struct qk_vtimer
{
	uint32_t id;
	uint64_t ticks;
	uint64_t remaining;
	qk_vtimer_mode mode;
	void *cb_arg;
	void (*cb)(int, void*);
	bool exec_callback;
	bool running;
} qk_vtimer;

void qk_vtimer_init(qk_vtimer *timers, uint32_t count);
int qk_vtimer_create(uint64_t msec, void (*cb)(int, void*), void *arg, qk_vtimer_mode mode);
void qk_vtimer_destroy(int id);

void qk_delay_ms(uint64_t msec);

#endif /* QK_VTIMER_H */
