#ifndef __SPI_UPTECH_H
#define __SPI_UPTECH_H

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <asm/io.h>
#include <asm/unistd.h>
#include <asm-arm/arch-s3c2410/regs-gpio.h>
#include <linux/clk.h>
#include <asm/arch/regs-spi.h>
#include <asm/arch/map.h>

unsigned long *spi0_addr;

#define rSPI_CH_CFG  		((volatile unsigned long *)r_CH_CFG)   
#define rSPI_CLK_CFG  		((volatile unsigned long *)r_CLK_CFG)   
#define rSPI_MODE_CFG  		((volatile unsigned long *)r_MODE_CFG)   
#define rSPI_CS_CFG  		((volatile unsigned long *)r_CS_CFG)   
#define rSPI_INT_EN  		((volatile unsigned long *)r_INT_EN)   
#define rSPI_STATUS  		((volatile unsigned long *)r_STATUS)   
#define rSPI_TX_DATA  		((volatile unsigned long *)r_TX_DATA)   
#define rSPI_RX_DATA  		((volatile unsigned long *)r_RX_DATA)   
#define rSPI_PACKET_CNT_REG  	((volatile unsigned long *)r_PACKET_CNT_REG)   
#define rSPI_PANDING_CLR_REG  	((volatile unsigned long *)r_PANDING_CLR_REG)   
#define rSPI_SWAP_REG  		((volatile unsigned long *)r_SWAP_REG)   
#define rSPI_FB_CLK_SEL  	((volatile unsigned long *)r_FB_CLK_SEL)   
 
#define rCLKCON 		((volatile unsigned long *)r_CLKCON)

#define S3C2410_GPG2_NSS0 	(0x03 << 4)

unsigned long *r_CH_CFG,*r_CLK_CFG,*r_MODE_CFG,*r_CS_CFG,*r_INT_EN,*r_STATUS,*r_TX_DATA,*r_RX_DATA,*r_PACKET_CNT_REG,*r_PANDING_CLR_REG,*r_SWAP_REG,*r_FB_CLK_SEL,*r_CLKCON;

int address_map(void)
{
	r_CLKCON 	= ioremap(0x7E00F034,4);
	r_CH_CFG 	= ioremap(0x7F00B000,4);
	r_CLK_CFG 	= ioremap(0x7F00B004,4);
	r_MODE_CFG	= ioremap(0x7F00B008,4);
	r_CS_CFG 	= ioremap(0x7F00B00C,4);
	r_INT_EN 	= ioremap(0x7F00B010,4);
	r_STATUS 	= ioremap(0x7F00B014,4);
	r_TX_DATA 	= ioremap(0x7F00B018,4);
	r_RX_DATA 	= ioremap(0x7F00B01c,4);
	r_PACKET_CNT_REG = ioremap(0x7F00B020,4);
	r_PANDING_CLR_REG = ioremap(0x7F00B024,4);
	r_SWAP_REG 	= ioremap(0x7F00B028,4);
	r_FB_CLK_SEL 	= ioremap(0x7F00B02c,4);

	return 0;
}

int spi_hw_init(void)
{
    	unsigned long temp; 

    	temp = readl(rCLKCON);
	//printk("rCLKCON = 0x%x\n",temp);
    	temp |= 0x200000; 
	writel(temp,rCLKCON);	
    	temp = readl(rCLKCON);
	//printk("rCLKCON = 0x%x\n",temp);
	s3c_gpio_cfgpin(S3C_GPC0, S3C_GPC0_SPI_MISO0);
	s3c_gpio_cfgpin(S3C_GPC1, S3C_GPC1_SPI_CLK0);
	s3c_gpio_cfgpin(S3C_GPC2, S3C_GPC2_SPI_MOSI0);

	s3c_gpio_pullup(S3C_GPC0,1);
	s3c_gpio_pullup(S3C_GPC1,1);
	s3c_gpio_pullup(S3C_GPC2,1);

    return 0;
}
#ifndef DBG
#define DBG printk
#endif
static void s3c_spi_init(int rx_tx)
{

	unsigned long temp;
	u32 spi_chcfg = 0, spi_slavecfg, spi_inten= 0, spi_packet=0;

//	u8 prescaler = 4;		// 8.887Mhz
	u8 prescaler = 8;		// 8.887Mhz

	u32 spi_clkcfg = 0, spi_modecfg = 0 ;

	/* initialise the spi controller */
	spi_hw_init();

	/* 1. Set transfer type (CPOL & CPHA set) */
	spi_chcfg = SPI_CH_RISING | SPI_CH_FORMAT_A;

	spi_chcfg |= SPI_CH_MASTER;
	writel( spi_chcfg , rSPI_CH_CFG);
	temp = readl(rSPI_CH_CFG);

	/* 2. Set clock configuration register */
	spi_clkcfg = SPI_ENCLK_ENABLE;

	spi_clkcfg |= SPI_CLKSEL_PCLK;

	writel( spi_clkcfg , rSPI_CLK_CFG);

	spi_clkcfg = readl( rSPI_CLK_CFG);

	spi_clkcfg |= prescaler;
	writel( spi_clkcfg , rSPI_CLK_CFG);
	temp = readl(rSPI_CLK_CFG);

	/* 3. Set SPI MODE configuration register */
	spi_modecfg = SPI_MODE_CH_TSZ_BYTE| SPI_MODE_BUS_TSZ_BYTE;

	spi_modecfg |= SPI_MODE_TXDMA_OFF| SPI_MODE_SINGLE| SPI_MODE_RXDMA_OFF;

	if (rx_tx == 0x01)
		spi_modecfg |= ( 0x3f << 5); /* Tx FIFO trigger level in INT mode */
	if (rx_tx == 0x00)
		spi_modecfg |= ( 0x3f << 11); /* Rx FIFO trigger level in INT mode */
	spi_modecfg |= ( 0x3ff << 19);

	writel(spi_modecfg, rSPI_MODE_CFG);
	temp = readl(rSPI_MODE_CFG);

	/* 4. Set SPI INT_EN register */

	if (rx_tx == 0x01)
		spi_inten = SPI_INT_TX_FIFORDY_EN|SPI_INT_TX_UNDERRUN_EN|SPI_INT_TX_OVERRUN_EN;
	if (rx_tx == 0x00){
		spi_inten = SPI_INT_RX_FIFORDY_EN|SPI_INT_RX_UNDERRUN_EN|SPI_INT_RX_OVERRUN_EN|SPI_INT_TRAILING_EN	;
	}
	//disable all int
	writel(0x00, rSPI_INT_EN);
	temp = readl(rSPI_INT_EN);

	writel(0x1f,  rSPI_PANDING_CLR_REG);
	temp = readl(rSPI_PANDING_CLR_REG);

	/* 5. Set Packet Count configuration register */
	spi_packet = readl(rSPI_PACKET_CNT_REG);

	spi_packet = SPI_PACKET_CNT_EN;
	spi_packet |= 0x01;
	writel(spi_packet, rSPI_PACKET_CNT_REG);
	temp = readl(rSPI_PACKET_CNT_REG);

	/* 6. Set Tx or Rx Channel on */
	spi_chcfg = readl(rSPI_CH_CFG);
	spi_chcfg |= SPI_CH_TXCH_OFF | SPI_CH_RXCH_OFF;

	if (rx_tx == 0x01)
		spi_chcfg |= SPI_CH_TXCH_ON;
	if (rx_tx == 0x00)
		spi_chcfg |= SPI_CH_RXCH_ON;

	writel(spi_chcfg, rSPI_CH_CFG);
	temp = readl(rSPI_CH_CFG);

	/* 7. Set nSS low to start Tx or Rx operation */
	spi_slavecfg = readl(rSPI_CS_CFG);
	
	spi_slavecfg &= SPI_SLAVE_SIG_ACT;
	writel(spi_slavecfg,  rSPI_CS_CFG);
	temp = readl(rSPI_CS_CFG);

}


inline static void s3c_spi_close ( int channel ){
	u32 spi_clkcfg;	
        if(channel == 0) {
 
                s3c_gpio_cfgpin(S3C_GPC0, 0);
                s3c_gpio_cfgpin(S3C_GPC1, 0);
                s3c_gpio_cfgpin(S3C_GPC2, 0);
 
        } else {
 
                s3c_gpio_cfgpin(S3C_GPC4, 0);
                s3c_gpio_cfgpin(S3C_GPC5, 0);
                s3c_gpio_cfgpin(S3C_GPC6, 0);
                s3c_gpio_cfgpin(S3C_GPC7, 0);
        }
        spi_clkcfg = readl(rSPI_CLK_CFG);
        spi_clkcfg &= SPI_ENCLK_DISABLE;
        writel( spi_clkcfg , rSPI_CLK_CFG);
 
        /* Buffer Clear after finish xfer */
        writel( 0x20, rSPI_CH_CFG);
        writel( 0x0, rSPI_CH_CFG);
}

inline static unsigned char SPIRecv ( int channel )
{
    	unsigned long temp;

	s3c_spi_init(0);//recv
	udelay(100);

    	temp = readl(rSPI_RX_DATA); 
	s3c_spi_close(0); 
	
    	return temp;
}

inline static void SPISend ( unsigned char val, int channel )
{
	s3c_spi_init(1);//send 
	while(((readl(rSPI_STATUS)) & 0x01) == 0x00);
        {
            	writel(val,rSPI_TX_DATA);
		udelay(100);
        } 
	while(((readl(rSPI_STATUS)) & 0x01) == 0x00);

	s3c_spi_close(0); 
}



inline static void SPI_initIO(int channel)
{
	address_map();
}

#endif
