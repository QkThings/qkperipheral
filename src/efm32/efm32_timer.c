/*
 * QkThings LICENSE
 * The open source framework and modular platform for smart devices.
 * Copyright (C) 2014 <http://qkthings.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "qk_peripheral.h"
#include "qk_peripheral_p.h"

#include "em_cmu.h"
#include "em_timer.h"
#include "em_letimer.h"

#define CAL_Q 7

const uint32_t _1ms_scaler[] =
{
    14, // 14 Mhz (default)
    16, // 1 Mhz
    14, // 7 Mhz
    11, // 11 Mhz
    21, // 21 Mhz
    27, // 28 Mhz
};

const uint32_t _1ms_pre_mask[] =
{
    TIMER_CTRL_PRESC_DIV1024, // 14 Mhz (default)
    TIMER_CTRL_PRESC_DIV64,   // 1 Mhz
    TIMER_CTRL_PRESC_DIV512,  // 7 Mhz
    TIMER_CTRL_PRESC_DIV1024, // 11 Mhz
    TIMER_CTRL_PRESC_DIV1024, // 21 Mhz
    TIMER_CTRL_PRESC_DIV1024, // 28 Mhz
};

const int32_t _1ms_cal[] =
{
    42,   // 14 Mhz (default)
    96,   // 1 Mhz
    42,   // 7 Mhz
    42,   // 11 Mhz
    74,   // 21 Mhz
    -44,  // 28 Mhz
};

const uint32_t _1us_scaler[] =
{
    7,  // 14 Mhz (default)
    1,  // 1 Mhz
    7,  // 7 Mhz
    11, // 11 Mhz
    21, // 21 Mhz
    7,  // 28 Mhz
};

const uint32_t _1us_pre_mask[] =
{
    TIMER_CTRL_PRESC_DIV2,  // 14 Mhz (default)
    TIMER_CTRL_PRESC_DIV1,  // 1 Mhz
    TIMER_CTRL_PRESC_DIV1,  // 7 Mhz
    TIMER_CTRL_PRESC_DIV1,  // 11 Mhz
    TIMER_CTRL_PRESC_DIV1,  // 21 Mhz
    TIMER_CTRL_PRESC_DIV4,  // 28 Mhz
};
///******************************************************************************/
static void timer_set_period(TIMER_TypeDef *timer, uint32_t per, qk_timer_scale s);
static void timer_set_frequency(TIMER_TypeDef *timer, uint32_t freq);
static void letimer_set_period(LETIMER_TypeDef *timer, uint32_t per, qk_timer_scale s);
static void letimer_set_frequency(LETIMER_TypeDef *timer, uint32_t freq);
static uint32_t calc_top(uint32_t period, uint32_t scaler, int32_t cal);

///******************************************************************************/

typedef enum TIMER_Type
{
	TIMER_TYPE_UNKNOWN = 0,
	TIMER_TYPE_TIMER,
	TIMER_TYPE_LETIMER
} TIMER_Type;

#define EFM32_TIMER_IRQ(name, id) \
	void name ## _IRQHandler() \
	{ \
		_qk_timer_handle_interrupt(id); \
		TIMER_IntClear(name, TIMER_IF_OF); \
	}

#define EFM32_LETIMER_IRQ(name, id) \
	void name ## _IRQHandler() \
	{ \
		_qk_timer_handle_interrupt(id); \
		LETIMER_IntClear(name, LETIMER_IF_UF); \
	}

EFM32_TIMER_IRQ(TIMER0, 	_QK_PROGRAM_TIMER0)
EFM32_TIMER_IRQ(TIMER1, 	_QK_PROGRAM_TIMER1)
//EFM32_LETIMER_IRQ(LETIMER0, QK_TIMER_0)


void _qk_timer_startup(void)
{
	CMU_ClockEnable(cmuClock_TIMER0, true);
	CMU_ClockEnable(cmuClock_TIMER1, true);
//	CMU_ClockEnable(cmuClock_LETIMER0, true);

	TIMER_IntEnable(TIMER0, TIMER_IF_OF);
	TIMER_IntEnable(TIMER1, TIMER_IF_OF);
//	LETIMER_IntEnable(LETIMER0, LETIMER_IF_UF);

	NVIC_EnableIRQ(TIMER0_IRQn);
	NVIC_EnableIRQ(TIMER1_IRQn);
//	NVIC_EnableIRQ(LETIMER0_IRQn);
}

static TIMER_TypeDef* get_timer_typedef(qk_timer id)
{
	switch(id)
	{
	case _QK_PROGRAM_TIMER0: return TIMER0;
	case _QK_PROGRAM_TIMER1: return TIMER1;
	default: return 0;
	}
}

static LETIMER_TypeDef* get_letimer_typedef(qk_timer id)
{
	if(id == EFM32_TIMER_HIGHEST+1)
		return LETIMER0;
	return 0;
}

static TIMER_Type get_timer_type(qk_timer id)
{
	if(id == _QK_PROGRAM_TIMER0 || id == _QK_PROGRAM_TIMER1)
		return TIMER_TYPE_TIMER;
	else
		return TIMER_TYPE_LETIMER;
}

void qk_timer_set_period(qk_timer id, unsigned int value, qk_timer_scale scale)
{
	if(get_timer_type(id) == TIMER_TYPE_TIMER)
		timer_set_period(get_timer_typedef(id), value, scale);
	else
		letimer_set_period(get_letimer_typedef(id), value, scale);
}

void qk_timer_set_frequency(qk_timer id, unsigned int value)
{
	if(get_timer_type(id) == TIMER_TYPE_TIMER)
		timer_set_frequency(get_timer_typedef(id), value);
	else
		letimer_set_frequency(get_letimer_typedef(id), value);
}

void qk_timer_start(qk_timer id)
{
	if(get_timer_type(id) == TIMER_TYPE_TIMER)
		get_timer_typedef(id)->CMD = TIMER_CMD_START;
	else
		get_letimer_typedef(id)->CMD = LETIMER_CMD_START;
}

void qk_timer_stop(qk_timer id)
{
	if(get_timer_type(id) == TIMER_TYPE_TIMER)
		get_timer_typedef(id)->CMD = TIMER_CMD_STOP;
	else
		get_letimer_typedef(id)->CMD = TIMER_CMD_STOP;
}


void qk_timer_restart(qk_timer id)
{
	if(get_timer_type(id) == TIMER_TYPE_TIMER)
	{
		get_timer_typedef(id)->CNT = 0;
		get_timer_typedef(id)->CMD = TIMER_CMD_START;
	}
	else
	{
		//get_letimer_typedef(id)->CNT = get_letimer_typedef(id)->COMP0;
	}
}

void delay_ms(uint16_t value)
{
	bool running = ((TIMER0->STATUS & TIMER_STATUS_RUNNING) == 1 ? true : false);
	TIMER0->CTRL = (TIMER0->CTRL & ~_TIMER_CTRL_PRESC_MASK) | _1ms_pre_mask[0];

	uint32_t top = calc_top(value, _1ms_scaler[0], _1ms_cal[0]);

	if(!running)
		TIMER0->CMD = TIMER_CMD_START;
	TIMER0->CNT = 0;
	while(TIMER0->CNT < top);

	if(!running)
		TIMER0->CMD = TIMER_CMD_STOP;
}

void delay_us(uint16_t value)
{
	/*Note: value > 100*/
	uint32_t calibrated_val = _1us_scaler[0]*value-99; //FIXME
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CTRL |= 1;
	uint32_t temp = DWT->CYCCNT + calibrated_val;
	while (DWT->CYCCNT < temp);
}

///******************************************************************************/


static uint32_t calc_top(uint32_t period, uint32_t scaler, int32_t cal)
{
	return ((scaler*period)-((period*cal)>>CAL_Q));
}

static void timer_set_period(TIMER_TypeDef *timer, uint32_t per, qk_timer_scale s)
{
	switch(s)
	{
	case QK_TIMER_SCALE_MSEC:
		timer->CTRL = (timer->CTRL & ~_TIMER_CTRL_PRESC_MASK) | _1ms_pre_mask[0];
		timer->TOP = calc_top(per, _1ms_scaler[0], _1ms_cal[0]);
		break;
	case QK_TIMER_SCALE_USEC:
		timer->CTRL = (timer->CTRL & ~_TIMER_CTRL_PRESC_MASK) | _1us_pre_mask[0];
		timer->TOP = calc_top(per, _1us_scaler[0], 0);
		break;
	default: ;
	}
	timer->CNT = 0;
}

static void timer_set_frequency(TIMER_TypeDef *timer, uint32_t freq)
{
	uint16_t period = 0;
	qk_timer_scale scale;
	if(freq >= 1 && freq <= 1000) {
		period = (uint16_t)(1000.0/(float)freq); // msec
		scale = QK_TIMER_SCALE_MSEC;
	}
	else if(freq > 1000) {
		period = (uint16_t)(1000000.0/(float)freq); // usec
		scale = QK_TIMER_SCALE_USEC;
	}

	if(period > 0)
		timer_set_period(timer, period, scale);
}

static void letimer_set_period(LETIMER_TypeDef *timer, uint32_t per, qk_timer_scale s)
{
	switch(s)
	{
	case QK_TIMER_SCALE_MSEC:
		timer->CTRL = (timer->CTRL & ~_TIMER_CTRL_PRESC_MASK) | _1ms_pre_mask[0];
		timer->COMP0 = calc_top(per, _1ms_scaler[0], _1ms_cal[0]);
		break;
	case QK_TIMER_SCALE_USEC:
		timer->CTRL = (timer->CTRL & ~_TIMER_CTRL_PRESC_MASK) | _1us_pre_mask[0];
		timer->COMP0 = calc_top(per, _1us_scaler[0], 0);
		break;
	default: ;
	}
	//timer->CNT = 0;
}

static void letimer_set_frequency(LETIMER_TypeDef *timer, uint32_t freq)
{
	uint16_t period = 0;
	qk_timer_scale scale;
	if(freq >= 1 && freq <= 1000) {
		period = (uint16_t)(1000.0/(float)freq); // msec
		scale = QK_TIMER_SCALE_MSEC;
	}
	else if(freq > 1000) {
		period = (uint16_t)(1000000.0/(float)freq); // usec
		scale = QK_TIMER_SCALE_USEC;
	}

	if(period > 0)
		letimer_set_period(timer, period, scale);
}
