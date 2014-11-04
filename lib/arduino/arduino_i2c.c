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
#include <avr/sleep.h>
#include <avr/interrupt.h>

#define I2C_READ  1
#define I2C_WRITE 0

#define START_ACK 0x08
#define REP_START_ACK 0x10
// Master Receiver
#define MR_SLA_ACK  0x40
#define MR_DATA_ACK 0x50
#define MR_DATA_NACK 0x58
// Master Transmitter
#define MT_SLA_ACK  0x18
#define MT_DATA_ACK 0x28

void _qk_i2c_startup()
{
	// Set clkdiv=0
	TWSR = 0x00;
	// Set bitrate max bitrate to 400kHz
	TWBR = 0x02;
	// Enable I2C I/O pins
	TWCR = (1<<TWEN);
}

uint8_t _qk_i2c_status()
{
	return (TWSR & 0xF8);
}

uint8_t qk_i2c_start()
{
	// Clear TWINT flag, Set START and EN bits
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	// Wait for transmission
	while(!(TWCR & (1<<TWINT)));
	
	// Check if some error has occured 
	switch( _qk_i2c_status())
	{ 	
		// Expected status list
		case START_ACK:      return QK_I2C_OK_ACK;
		case REP_START_ACK:  return QK_I2C_OK_ACK;
		// Erroneous status 
		default: return QK_I2C_ERR;
	}
}


uint8_t qk_i2c_write(uint8_t * data, uint8_t num_bytes)
{	
	uint8_t i;
	qk_i2c_status status;

	for(i=0;i<num_bytes;i++)
	{	// Load data byte 
		TWDR = data[i];

		// Start transmission
		TWCR = (1<<TWINT) | (1<<TWEN);

		// Wait for transmission
		while((TWCR & (1<<TWINT))==0);
		
		// Break if some error has occured 
		switch(_qk_i2c_status())
		{ 	
			// Expected status list
			case MT_SLA_ACK:  status = QK_I2C_OK_ACK; break;
			case MT_DATA_ACK: status = QK_I2C_OK_ACK; break;
			case MR_SLA_ACK:  status = QK_I2C_OK_ACK; break;
			// Erroneous status 
			default: return QK_I2C_ERR;
		}
	}
	return QK_I2C_OK;
}

uint8_t qk_i2c_read(uint8_t * data, uint8_t num_bytes, bool ack)
{
	uint8_t i;
	qk_i2c_status status;
	
	for(i=0;i<num_bytes;i++)	
	{
		// Begin transmission 
    		TWCR = (1<<TWINT)|(1<<TWEN)|(ack<<TWEA);
    		// wait for transmission
		while(!(TWCR & (1<<TWINT)));
		// Read byte
		data[i] =  TWDR;
		
		// Break if some error has occured 
		switch(_qk_i2c_status())
		{ 	
			// Expected status list
			case MR_DATA_ACK:  status = QK_I2C_OK_ACK;  break;
			case MR_DATA_NACK: status = QK_I2C_OK_NACK; break;
			// Erroneous status 
			default: return QK_I2C_ERR;
		}
	}

	return status;
}

uint8_t qk_i2c_stop()
{
	//Send stop
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO) ;

	// Wait for TWSTO flag to be cleared 
	while (!(TWCR & (1 << TWSTO)));

	return QK_I2C_OK;
}


