/*
 * s3c2410-da.c
 *
 * da driver for UP-NETARM2410-S DA
 *
 * Author: Wang bin <wbinbuaa@163.com>
 * Date  : $Date: 2005/7/22 15:50:00 $ 
 * Description : UP-NETARM2410-S, with 74hc573
 * $Revision: 2.1.0 $
 *
 * Based on s3c2410-da-max504.c
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the main directory of this archive
 * for more details.
 *
 * History:
 *
 * 
 */

#include <linux/config.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
//#include <linux/kdev_t.h> MAJOR MKDEV
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/mm.h>
//#include <linux/poll.h>
//#include <linux/spinlock.h>
//#include <linux/irq.h>
#include <asm/uaccess.h>				/* copy_from_user */
//#include <asm/sizes.h>

#include <asm/arch/spi.h>
#include <asm/io.h>
#include <asm/hardware.h>


/* debug macros */
#undef DEBUG
//#define DEBUG
#ifdef DEBUG
#define DPRINTK(x...) {printk(__FUNCTION__"(%d): ",__LINE__);printk(##x);}
#else
#define DPRINTK(x...) (void)(0)
#endif

/* debug macros */
//#undef STEP_DEBUG
#define STEP_DEBUG
#ifdef STEP_DEBUG
#define DPRINTK_STEP(x...) {printk(__FUNCTION__"(%d): ",__LINE__);printk(##x);}
#else
#define DPRINTK_STEP(x...) (void)(0)
#endif

#define DEVICE_NAME	"s3c2410-exio"
#define EXIORAW_MINOR	1

#define DA_IOCTRL_WRITE 			0x10
#define DA_IOCTRL_CLR 				0x12

static int exioMajor = 0;
static void setSPImode (void)
{
	/*  prescaler =33   0-255*/
	Set_SIO_mode(0, SPCON_SMOD_POLL | SPCON_ENSCK | SPCON_MSTR |SPCON_CPOL_HIGH | 
		SPCON_CPHA_FMTA,   40, 2, NULL, NULL, NULL);
}

/************************************************************************/

static int s3c2410_exio_open(struct inode *inode, struct file *filp)
{
	MOD_INC_USE_COUNT;
	DPRINTK( "S3c2410 EXIO device open!\n");
	return 0;
}

static int s3c2410_exio_release(struct inode *inode, struct file *filp)
{
	MOD_DEC_USE_COUNT;
	DPRINTK( "S3c2410 EXIO device release!\n");
	return 0;
}


/*******Enable the select port of DA ********/
static ssize_t da_enable( )
{
	         GPGCON &=~ 0xC0;           
                GPGCON |= 0x40;      
                GPGDAT&=~ 0x08;         
              //  GPGDAT |= 0x0; 
	return 0;	
}


/*******Disable the select port of DA ********/
static ssize_t da_disable( )
{
	                GPGDAT&=~ 0x08;         
                       GPGDAT |= 0x08; 

	return 0;	
}


/*******Write the select port of DA ********/
static ssize_t da_write( const char *buffer)
{
	unsigned int value;
	char buf[4];

	copy_from_user(buf, buffer, 4);
	value = *((int *)buf);	
	value <<= 2;

	da_enable();
	udelay(10);
  	SPISend ((value>>8) &0xff, 0);
  	SPISend ((value&0xff), 0);
//	udelay(100);
	da_disable();

	DPRINTK("write to max504-1 => %u\n",value);
	return 0;
}


/*******Clear the select port of DA ********/
static ssize_t da_clear()
{
	da_disable();
	return 0;	
}


void tiny_delay(int t)
{
	int i;
	for(;t>0;t--)
		for(i=0;i<400;i++);
}

static int s3c2410_exio_ioctl (struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	switch(cmd){
		
	/*********write da 0 with (*arg) ************/		
	case DA_IOCTRL_WRITE:
		return da_write( (const char *)arg);

	/*********clear da (*arg) *****************/		
	case DA_IOCTRL_CLR:
		return da_clear();
      default:
	  	printk("Wrong ioctl arg");
	return 0;	
}
}

static struct file_operations s3c2410_exio_fops = {
	owner:	THIS_MODULE,
	open:	s3c2410_exio_open,
	ioctl:	      s3c2410_exio_ioctl,
	release:	s3c2410_exio_release,
};

#ifdef CONFIG_DEVFS_FS
static devfs_handle_t devfs_exio_dir, devfs_exio0;
#endif
int __init s3c2410_exio_init(void)
{
       SPI_initIO(0);
	setSPImode();
#ifdef CONFIG_DEVFS_FS
	devfs_exio_dir = devfs_mk_dir(NULL, "exio", NULL);
	devfs_exio0 = devfs_register(devfs_exio_dir, "0raw", DEVFS_FL_DEFAULT,
				exioMajor, EXIORAW_MINOR, S_IFCHR | S_IRUSR | S_IWUSR, &s3c2410_exio_fops, NULL);

#else	
	ret = register_chrdev(0, DEVICE_NAME, &s3c2410_exio_fops);
	if (ret < 0) {
		DPRINTK(DEVICE_NAME " can't get major number\n");
		return ret;
	}
	exioMajor=ret;
#endif


	DPRINTK (DEVICE_NAME"\tdevice initialized\n");
	return 0;
	
}

module_init(s3c2410_exio_init);

#ifdef MODULE
void __exit s3c2410_exio_exit(void)
{
#ifdef CONFIG_DEVFS_FS	
	devfs_unregister(devfs_exio0);
	devfs_unregister(devfs_exio_dir);
#else
	unregister_chrdev(exioMajor, DEVICE_NAME);
#endif
}

module_exit(s3c2410_exio_exit);
#endif


MODULE_LICENSE("GPL"); 

