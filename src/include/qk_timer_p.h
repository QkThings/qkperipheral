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

#ifndef QK_TIMER_P_H
#define QK_TIMER_P_H

#ifndef QK_TIMER_COUNT
#error "QK_TIMER_COUNT not defined"
#endif

typedef struct
{
  qk_timer_scale scale;
  uint32_t flags;
  uint32_t period;
  uint32_t _value;
} _qk_timer_struct;

extern _qk_timer_struct _qk_timer[QK_TIMER_COUNT];

void _qk_timer_init(void);
void _qk_timer_startup(void);
void _qk_timer_handle_interrupt(qk_timer id);

#endif // QK_TIMER_P_H
