#ifndef QK_SPI_H
#define QK_SPI_H

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
