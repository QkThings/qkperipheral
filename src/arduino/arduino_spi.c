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
#include <avr/interrupt.h>

void _qk_spi_startup()
{
	// Enable SPI Master, set clock rate fck/16 
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void qk_spi_set_mode(qk_spi_mode mode)
{
	// Clear CPOL and CPHA control bits
	SPSR  &= ~((1<<CPOL) | (1<<CPHA));
 
	// Set CPOL and CPHA bits according
	// to the SPI mode selected by the user
	switch(mode)
	{
		case QK_SPI_MODE_0: SPSR |= (0<<CPOL) | (0<<CPHA); 
		case QK_SPI_MODE_1: SPSR |= (0<<CPOL) | (1<<CPHA); 	
		case QK_SPI_MODE_2: SPSR |= (1<<CPOL) | (0<<CPHA); 	
		case QK_SPI_MODE_3: SPSR |= (1<<CPOL) | (1<<CPHA); 	
	}		
}


uint8_t qk_spi_transfer(uint8_t data)
{
	// Write to the SPI Data Register
	SPDR = data;
	// Wait for transmission
	while(!(SPSR & (1<<SPIF)))
	// Read the SPI Data Register
	return SPDR;
}

