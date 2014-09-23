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

_qk_timer_struct _qk_timer[QK_TIMER_COUNT];

void _qk_timer_init(void)
{
	memset(_qk_timer, 0, QK_TIMER_COUNT*sizeof(_qk_timer_struct));
}

void _qk_timer_handle_interrupt(qk_timer id)
{
	if(_qk_timer[id].flags & QK_TIMER_FLAG_TIMEOUT)
		_qk_timer[id].flags |= QK_TIMER_FLAG_OVERLAP;
	_qk_timer[id].flags |= QK_TIMER_FLAG_TIMEOUT;
}

uint32_t qk_timer_flags(qk_timer id)
{
	qk_mcu_interrupt_disable();
	uint32_t flags = _qk_timer[id].flags;
	qk_mcu_interrupt_enable();
	return flags;
}

void qk_timer_flags_clear(qk_timer id, uint32_t flags)
{
	qk_mcu_interrupt_disable();
	_qk_timer[id].flags &= ~flags;
	qk_mcu_interrupt_enable();
}


