/*
 * s3c2410-dcmotor.c
 *
 * DC motor driver for UP-NETARM2410-S DA
 *
 * Author: Wang bin <wbinbuaa@163.com>
 * Date  : $Date: 2005/7/26 15:50:00 $ 
 * Description : UP-NETARM2410-S
 * $Revision: 0.1.0 $
 *
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
#include <asm/arch/S3C2410.h>
//#include <asm/hardware.h>

#ifdef CONFIG_DEVFS_FS
#include <linux/devfs_fs_kernel.h>
#endif

/* debug macros */
//#undef DEBUG
#define DEBUG
#ifdef DEBUG
#define DPRINTK(x...) {printk(__FUNCTION__"(%d): ",__LINE__);printk(##x);}
#else
#define DPRINTK(x...) (void)(0)
#endif

#define DEVICE_NAME				"s3c2410-pwm-da"
#define DCMRAW_MINOR	1		//direct current motor

#define DCM_IOCTRL_SETPWM 			(0x10)
#define DCM_TCNTB0					(163840)
#define DCM_TCFG23					(0x200)
static int dcmMajor = 0;


#define tout02_03_enable() \
	({ 	GPBCON &=~ 0xff;		\
		GPBCON |= 0xa0;	 })     /*tout00  tout01 off ,tout02,tout03 open;*/

#define tout02_03_disable() \
	({ 	GPBCON &=~ 0xff;		\
		GPBCON |= 0x55; 		\
		GPBUP &=~0xf; 	})
	
/* deafault divider value=1/16		*/
/* deafault prescaler = 1/2 ;			*/
/* Timer input clock Frequency = PCLK / {prescaler value+1} / {divider value} */
#define dcm_stop_timer()	({ TCON &= ~0x11000; })    /*  12bit ,16bit=0*/

#define DPRINTREG() \
	({  													\
	DPRINTK("GPBCON %x\n", GPBCON);					\
	DPRINTK("TCFG0 %x\n", TCFG0); 						\
	DPRINTK("TCFG1 %x\n", TCFG1); 						\
	DPRINTK("TCNTB0 %x\n", TCNTB2); 						\
	DPRINTK("TCMPB0 %x\n", TCMPB2); 						\
	DPRINTK("TCON %x\n", TCON); 							\
	DPRINTK("GPBCON %x\n", GPBCON);					\
	DPRINTK("\n");										\
})


static void  dcm_start_timer()
{ TCFG0 &= ~(0xff00);
 TCFG0 |= (DCM_TCFG23);
 TCFG1 &= ~(0xffff);
 //TCFG1 |= 0x3300;
 TCNTB2 = DCM_TCNTB0;
 TCNTB3 = DCM_TCNTB0;
 TCMPB2 = DCM_TCNTB0/2;
 TCMPB3 = DCM_TCNTB0/2;
 TCON &=~(0xff000);
 TCON |=(0x22000);
 TCON &=~(0xff000);
 TCON |=(0x99000);
}
 


static int s3c2410_dcm_open(struct inode *inode, struct file *filp)
{
	MOD_INC_USE_COUNT;
	DPRINTK( "S3c2410 DC Motor device open now!\n");
	tout02_03_enable();
	dcm_start_timer();
	return 0;
}

static int s3c2410_dcm_release(struct inode *inode, struct file *filp)
{
	MOD_DEC_USE_COUNT;
	DPRINTK( "S3c2410 DC Motor device release!\n");
	tout02_03_disable();
	dcm_stop_timer();
	return 0;
}

static int dcm_setpwm(int v)
{
	return (TCMPB2 =DCM_TCNTB0/2 + v);
}
static int s3c2410_dcm_ioctl (struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	switch(cmd){
		
	/*********write da 0 with (*arg) ************/		
	case DCM_IOCTRL_SETPWM:
		return dcm_setpwm((int)arg);	
	}
	return 0;	
}

static struct file_operations s3c2410_dcm_fops = {
	owner:	THIS_MODULE,
	open:	s3c2410_dcm_open,
	ioctl:	s3c2410_dcm_ioctl,
	release:	s3c2410_dcm_release,
};


#ifdef CONFIG_DEVFS_FS
static devfs_handle_t devfs_dcm_dir, devfs_dcm0;
#endif
int __init s3c2410_dcm_init(void)
{
	int ret;
	
//	DPRINTREG();
	
	ret = register_chrdev(0, DEVICE_NAME, &s3c2410_dcm_fops);
	if (ret < 0) {
		DPRINTK(DEVICE_NAME " can't get major number\n");
		return ret;
	}
	dcmMajor=ret;

#ifdef CONFIG_DEVFS_FS
	devfs_dcm_dir = devfs_mk_dir(NULL, "pwm_da", NULL);
	devfs_dcm0 = devfs_register(devfs_dcm_dir, "0raw", DEVFS_FL_DEFAULT,
				dcmMajor, DCMRAW_MINOR, S_IFCHR | S_IRUSR | S_IWUSR, &s3c2410_dcm_fops, NULL);
#endif

	DPRINTK (DEVICE_NAME"\tdevice initialized\n");
	return 0;
	
}

module_init(s3c2410_dcm_init);

#ifdef MODULE
void __exit s3c2410_dcm_exit(void)
{
#ifdef CONFIG_DEVFS_FS
	devfs_unregister(devfs_dcm0);
	devfs_unregister(devfs_dcm_dir);
#endif

	unregister_chrdev(dcmMajor, DEVICE_NAME);
}

module_exit(s3c2410_dcm_exit);
#endif

MODULE_LICENSE("GPL"); 

