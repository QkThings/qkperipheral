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

#include "em_adc.h"
#include "em_cmu.h"

void _qk_adc_startup()
{
	// default settings
	CMU_ClockEnable(cmuClock_ADC0, true);

	ADC_Init_TypeDef init = ADC_INIT_DEFAULT;
//	ADC_InitSingle_TypeDef singleInit = ADC_INITSINGLE_DEFAULT;

	init.timebase = ADC_TimebaseCalc(0);

	init.prescale = ADC_PrescaleCalc(7000000,0);

	ADC_Init(ADC0,&init);

}

uint32_t qk_adc_read(qk_adc_ch ch)
{
	ADC_InitSingle_TypeDef singleInit = ADC_INITSINGLE_DEFAULT;

	singleInit.reference 	= adcRefVDD;

	singleInit.input   		= (ch);
	singleInit.resolution	= adcRes12Bit; //4096 possible values between 0 and adcRefVDD

	singleInit.acqTime 		= adcAcqTime32;

	ADC_InitSingle(ADC0,&singleInit);

	ADC_Start(ADC0,adcStartSingle);

	//TODO: use interrupts instead of pin polling
	while(ADC0->STATUS & ADC_STATUS_SINGLEACT) {
		//TODO: go to sleep mode (EM2?)
	}

	return ADC_DataSingleGet(ADC0);
}
//TODO: allow parameters setup ?
void qk_adc_setup() {
	// change ADC_Init_TypeDef and ADC_InitSingle_TypeDef

}
