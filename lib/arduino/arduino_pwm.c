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

#include <avr/io.h>

#define QK_PWM_CLK_DEFAULT ((1<<CS22) | (1<<CS20)) 
#define QK_PWM_DC_DEFAULT 128	

void _qk_pwm_startup()
{
	// Ensure the Timer2 is clocked from 
	// the 32kHz Crystal Ooscillator
	ASSR &=  ~(1<<EXCLK);
	ASSR |=   (1<<AS2);
		
	// Initialize Timer2 in Fast PWM mode	
	TCCR2A  |= (1<<WGM20) | (1<<COM2A1) | (1<<WGM21);
	
	// Wait until the TCCR2A updates
	while(ASSR & (1<<TCR2AUB));
	
	// Set PWM default duty cycle
	qk_pwm_set_duty_cycle(QK_PWM_DC_DEFAULT);

}
  
   
void qk_pwm_start()
{
	// Enable PWM default clock
	TCCR2B  |= QK_PWM_CLK_DEFAULT;
	// Wait until the TCCR2B updates
	while(ASSR & (1<<TCR2BUB));
}

void qk_pwm_stop()
{	
	// Disable PWM default clock
	TCCR2B  &= ~QK_PWM_CLK_DEFAULT;
	// Wait until the TCCR2B updates
	while(ASSR & (1<<TCR2BUB));
}
 
void qk_pwm_set_duty_cycle(uint8_t duty_cycle)
{	
	// Write duty cycle value to OCR
	OCR2A = duty_cycle;
	// Wait until the register updates
	while(ASSR & (1<<OCR2AUB));
}

