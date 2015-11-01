#ifndef QK_VTIMER_P_H
#define QK_VTIMER_P_H

typedef struct qk_vtimer_list
{
	qk_vtimer *first;
	qk_vtimer *last;
	qk_vtimer *instances;
	uint32_t count;
} qk_vtimer_list;

extern qk_vtimer_list _vtimer_list;

void _qk_vtimer_startup(void);
void _qk_vtimer_handle_interrupt(void);

#endif /* QK_VTIMER_P_H */
