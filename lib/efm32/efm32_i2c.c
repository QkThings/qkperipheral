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

#include "em_i2c.h"
#include "em_cmu.h"

I2C_TransferReturn_TypeDef I2C_Status;

void I2C0_IRQHandler(void)
{
  /* Just run the I2C_Transfer function that checks interrupts flags and returns */
  /* the appropriate status */
  I2C_Status = I2C_Transfer(I2C0);
}

void _qk_i2c_startup()
{

	I2C_Init_TypeDef i2cInit = I2C_INIT_DEFAULT;


	/* Pin PA0 is configured to Open-drain with pull-up and filter */
	GPIO->P[0].MODEL = (GPIO->P[0].MODEL & ~_GPIO_P_MODEL_MODE0_MASK) | GPIO_P_MODEL_MODE0_WIREDANDPULLUPFILTER;
	/* Pin PA1 is configured to Open-drain with pull-up and filter */
	GPIO->P[0].MODEL = (GPIO->P[0].MODEL & ~_GPIO_P_MODEL_MODE1_MASK) | GPIO_P_MODEL_MODE1_WIREDANDPULLUPFILTER;

	/* Enable clock for I2C0 */
	CMU_ClockEnable(cmuClock_I2C0, true);

	/* Enable signals SDA, SCL */
	I2C0->ROUTE |= I2C_ROUTE_SDAPEN | I2C_ROUTE_SCLPEN;

    I2C_Init(I2C0, &i2cInit);

    /* Clear and enable interrupt from I2C module */
    NVIC_ClearPendingIRQ(I2C0_IRQn);
    NVIC_EnableIRQ(I2C0_IRQn);

}

uint32_t qk_i2c_write(uint8_t addr, uint8_t reg_addr, uint8_t value) {

	I2C_TransferSeq_TypeDef seq;
	uint8_t input_data[3];

	input_data[0] = reg_addr;
	input_data[1] = value;

	seq.addr = addr;

	seq.flags = I2C_FLAG_WRITE;
	seq.buf[0].data = input_data;
	seq.buf[0].len = 2;

	I2C_Status = I2C_TransferInit(I2C0, &seq);
	while ((I2C_Status=I2C_Transfer(I2C0)) == i2cTransferInProgress)
	{
		/* Enter EM1 while waiting for I2C interrupt */

		/* Could do a timeout function here. */
	}

	if (I2C_Status != i2cTransferDone)
	{
		return((int)I2C_Status);
	}

	return(I2C_Status);

}

uint8_t qk_i2c_read(uint8_t addr, uint8_t reg_addr) {

	I2C_TransferSeq_TypeDef seq;

	uint8_t received_data[3];
	uint8_t input_data[3];

	input_data[0] = reg_addr;

	memset(received_data,0,3); //clear buffer


	seq.addr 		= addr; //I2C address; e.g. EPPROM: EEPROM_CONTROL_BYTE_WRITE, etc
	seq.flags 		= I2C_FLAG_WRITE_READ;
	seq.buf[0].data = input_data;
	seq.buf[0].len 	= 1;

	seq.buf[1].data = received_data;
	seq.buf[1].len 	= 1;

	I2C_Status = I2C_TransferInit(I2C0,&seq);

	while(I2C_Status == i2cTransferInProgress);

	if (I2C_Status != i2cTransferDone)
	{
		return((int)I2C_Status);
	}

//	val = received_data;

	return received_data[0];


}


