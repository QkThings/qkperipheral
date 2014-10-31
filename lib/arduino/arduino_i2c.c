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
		case START_ACK: return QK_I2C_OK;
		case REP_START_ACK: return QK_I2C_OK;
		// Erroneous status 
		default: return QK_I2C_ERROR;
	}
}


uint8_t qk_i2c_write(uint8_t * data, uint8_t num_bytes)
{	
	uint8_t i;
	for(i=0;i<num_bytes;i++)
	{	// Load Slave Addr + Write/Read bit 
		TWDR = data[i];

		// Start transmission
		TWCR = (1<<TWINT) | (1<<TWEN);

		// Wait for transmission
		while(!(TWCR & (1<<TWINT)));
		
		// Break if some error has occured 
		switch(_qk_i2c_status())
		{ 	
			// Expected status list
			case MT_SLA_ACK: break;
			case MT_DATA_ACK: break;
			case MR_SLA_ACK: break;
			// Erroneous status 
			default: return QK_I2C_ERROR;
		}
	}
	return QK_I2C_OK;
}

uint8_t qk_i2c_read(uint8_t * data, uint8_t num_bytes, bool ack)
{
	uint8_t i;
		
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
			case MR_DATA_ACK: break;
			case MR_DATA_NACK: break;
			// Erroneous status 
			default: return QK_I2C_ERROR;
		}
	}

	return QK_I2C_OK;
}

uint8_t qk_i2c_stop()
{
	//Send stop
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO) ;

	// Wait for TWINT flag set in TWCR Register
	while (!(TWCR & (1 << TWINT)));

	return QK_I2C_OK;
}


