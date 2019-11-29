#include <linux/config.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/miscdevice.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/poll.h>
#include <linux/spinlock.h>
#include <linux/delay.h>
#include <linux/ioport.h>
#include <asm/io.h>
#include <asm/hardware.h>
#include <asm/sizes.h>
#include <asm/uaccess.h>

#include <asm/arch/S3C2410.h>
#include <asm/arch/irqs.h>

/* debug macros */
//#undef DEBUG
#define DEBUG
#ifdef DEBUG
#define DPRINTK( x... )	printk("s3c2410-led: " x)
#else
#define DPRINTK( x... )
#endif

#define DEVICE_NAME     "s3c2410 led"
#define LED_TUBE_PHY_START   0x08000110
#define LED_DIG_PHY_START   0x08000100

#define LED_TUBE_IOCTRL  0x11
#define LED_DIG_IOCTRL   0x12

static int ledMajor = 0;
#define LED_MINOR    1

#ifdef CONFIG_DEVFS_FS
static devfs_handle_t devfs_led_dir,devfs_led;
#endif

static u32 s3c2410_led_tube_addr = IDE_BASE + 0x100;
static u32 s3c2410_led_dig_vaddr = IDE_BASE + 0x110;

static int s3c2410_led_ioctl (struct inode *inode, struct file *filp, unsigned int cmd, unsigned int arg)
{
	//printk("DOT buffer is %x\n" ,arg>>8 );
    switch(cmd){
        case LED_DIG_IOCTRL:
            return *(volatile unsigned long *)s3c2410_led_dig_vaddr=(arg>>8) | arg << 16; ;   
        default :
            return printk("your command is not exist");
    }

    return 0;
}

static ssize_t s3c2410_led_write(struct file *filp, const char *buf, size_t count, loff_t * f_pos)
{
	int i;
	unsigned char mdata[16];
	if (copy_from_user(mdata,buf,10)) {
		return -EFAULT;
	}
	for (i=0;i<8;i++){
//		printk("::%d ",mdata[i]);
	//	*((volatile unsigned char *)(s3c2410_led_tube_addr+i))=0xff;
		*((volatile unsigned char *)(s3c2410_led_tube_addr+i*2))=mdata[i];
//		printk("::%x ",*((volatile unsigned short *)(s3c2410_led_tube_addr+i)));
	}
//	printk("\n");
        return 0;
}


static int s3c2410_led_open(struct inode *inode, struct file *filp)
{
    MOD_INC_USE_COUNT;
    printk("led device open sucess!\n");
    return 0;
}

static int  s3c2410_led_release(struct inode *inode, struct file *filp)
{
    MOD_DEC_USE_COUNT;
    printk("led device release\n");
    return 0;
}

static struct file_operations s3c2410_led_fops = {
    owner:THIS_MODULE,
    open:s3c2410_led_open,
    ioctl:s3c2410_led_ioctl,
    write:s3c2410_led_write,
    release:s3c2410_led_release,
};


int __init s3c2410_led_init(void)
{
    int ret;

	BWSCON = ((BWSCON & ~(BWSCON_ST1 | BWSCON_WS1 | BWSCON_DW1)) | (BWSCON_ST1 | BWSCON_DW(1, BWSCON_DW_16)));
		BANKCON1= BANKCON_Tacs4 | BANKCON_Tcos4 | BANKCON_Tacc14 |BANKCON_Toch4 | BANKCON_Tcah4 | BANKCON_Tacp6 | BANKCON_PMC1;
		GPACON|=(1<<12);

    ret = register_chrdev(0, DEVICE_NAME, &s3c2410_led_fops);
    if (ret < 0) {
        DPRINTK(DEVICE_NAME " can't get major number\n");
        return ret;
    }
#ifdef CONFIG_DEVFS_FS
    devfs_led_dir = devfs_mk_dir(NULL, "led", NULL);
    devfs_led = devfs_register(devfs_led_dir, "0raw", DEVFS_FL_DEFAULT,
                                 ledMajor,LED_MINOR, S_IFCHR | S_IRUSR | S_IWUSR, &s3c2410_led_fops, NULL);
#endif

    DPRINTK (DEVICE_NAME"\tdevice initialized\n");
    return 0;   
}


void __exit s3c2410_led_exit(void)
{
#ifdef CONFIG_DEVFS_FS	
	devfs_unregister(devfs_led);
	devfs_unregister(devfs_led_dir);
#endif
	unregister_chrdev(ledMajor, DEVICE_NAME);
}

module_init(s3c2410_led_init);
module_exit(s3c2410_led_exit);

