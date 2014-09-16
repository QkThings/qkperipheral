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

/** \addtogroup QkSPI
 * @brief Serial Peripheral Interface (SPI)
 *  @{
 */

typedef uint32_t qk_spi;

/**
 * SPI Mode
 * @see http://en.wikipedia.org/wiki/Serial_Peripheral_Interface
 */
typedef enum
{
	QK_SPI_MODE_0, //!< CPOL = 0, CKE = 1, CPHA = 0
	QK_SPI_MODE_1, //!< CPOL = 0, CKE = 0, CPHA = 1
	QK_SPI_MODE_2, //!< CPOL = 1, CKE = 0, CPHA = 0
	QK_SPI_MODE_3, //!< CPOL = 1, CKE = 1, CPHA = 1
} qk_spi_mode;


/**
 * SPI Bit Mode
 */
typedef enum qk_spi_bitmode
{
	QK_SPI_BITMODE_8, //!< 8 bit words
	QK_SPI_BITMODE_16, //!<16 bit words
} qk_spi_bitmode;

/**
 * SPI Speed
 */
typedef enum
{
	QK_SPI_SPEED_SLOW,
	QK_SPI_SPEED_NORMAL,
	QK_SPI_SPEED_FAST
} qk_spi_speed;

/**
 * @brief .
 */
void qk_spi_set_mode(qk_spi spi, qk_spi_mode mode);

/**
 * @brief .
 */
void qk_spi_set_bitmode(qk_spi spi, qk_spi_bitmode bitmode);

/**
 * @brief .
 */
void qk_spi_set_speed(qk_spi spi, qk_spi_speed speed);

#endif

/** @}*/
