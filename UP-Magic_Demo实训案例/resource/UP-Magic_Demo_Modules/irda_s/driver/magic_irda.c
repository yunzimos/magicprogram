#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
//#include <asm/irq.h>
#include <linux/interrupt.h>
#include <asm/uaccess.h>
#include <asm/arch/regs-gpio.h>
#include <asm/hardware.h>
#include <linux/device.h>
#include <linux/irq.h>
#include <asm/io.h>

#define DEVICE_NAME     "irda"  
#define IRDA_MAJOR    232         

static volatile int ev_press = 0;
static DECLARE_WAIT_QUEUE_HEAD(button_waitq);

static irqreturn_t irda_interrupt(int irq)
{
    ev_press = 1;                
    wake_up_interruptible(&button_waitq);   
    
    return IRQ_RETVAL(IRQ_HANDLED);
}

static int s3c_irda_open(struct inode *inode, struct file *file)
{ 	 
/*
    int err;
    
    err = request_irq(IRQ_EINT22, irda_interrupt,SA_INTERRUPT, "irda", NULL);
    if (err)
        printk("can't request irq!\n");
*/
    return 0;
}

static int s3c_irda_close(struct inode *inode, struct file *file)
{
//    free_irq(IRQ_EINT22, NULL);
    return 0;
}

static int s3c_irda_read(struct file *filp, char __user *buff, 
                                         size_t count, loff_t *offp)
{
/*
    unsigned long err;
    
    wait_event_interruptible(button_waitq, ev_press);
   
    err = copy_to_user(buff, (const void *)&ev_press, sizeof(ev_press));
    ev_press = 0;
    return err ? -EFAULT : 0;
*/
        unsigned long err;
        unsigned int temp=0;
        temp=(readl(S3C_GPLDAT)&0x7FFF)>>14;
        err = copy_to_user(buff, &temp, sizeof(temp));
        printk("GPLDAT14 is %x\n",temp);
        return err ? -EFAULT : 0;


}

static struct file_operations s3c_irda_fops = {
    .owner   =   THIS_MODULE,    
    .open    =   s3c_irda_open,
    .release =   s3c_irda_close, 
    .read    =   s3c_irda_read,
};


static int __init s3c_irda_init(void)
{
    int ret;
//		set_irq_type(IRQ_EINT22, IRQT_RISING);
		s3c_gpio_cfgpin(S3C_GPL14, S3C_GPL14_INP);
		s3c_gpio_pullup(S3C_GPL14,0);

    ret = register_chrdev(IRDA_MAJOR, DEVICE_NAME, &s3c_irda_fops);
    if (ret < 0) {
      printk(DEVICE_NAME " can't register major number\n");
      return ret;
    }
    
    printk(DEVICE_NAME " initialized\n");
    return 0;
}

static void __exit s3c_irda_exit(void)
{
    unregister_chrdev(IRDA_MAJOR, DEVICE_NAME);
}

module_init(s3c_irda_init);
module_exit(s3c_irda_exit);

MODULE_AUTHOR("xw_tech@126.com");             
MODULE_DESCRIPTION("S3C6410 IRDA Driver");   
MODULE_LICENSE("GPL");                              

