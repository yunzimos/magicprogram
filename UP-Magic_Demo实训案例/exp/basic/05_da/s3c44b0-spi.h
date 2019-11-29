#ifndef __S3C44B0_SPI_H__
#define __S3C44B0_SPI_H__

#define SPI_IOCTRL_WFORZLG7289	0x1
#define SPI_IOCTRL_WFORMAX504	0x2
#define SPI_IOCTRL_RW		0x3


typedef struct _spi_rw{
	char *buffer;
	int size;
}spi_rw;

#endif
