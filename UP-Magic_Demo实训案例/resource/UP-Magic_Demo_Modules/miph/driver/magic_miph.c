#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/irq.h>
#include <linux/interrupt.h>
#include <asm/uaccess.h>
#include <asm/arch/regs-gpio.h>
#include <asm/hardware.h>
#include <asm/io.h>

#define DEVICE_NAME     "MIPH"   
#define miph_MAJOR    235        

struct miph_irq_desc {
    int irq;
    unsigned long flags;
    char *name;
};

static struct miph_irq_desc miph_irqs [] = {
    {IRQ_EINT22, /*IRQF_TRIGGER_RISING*/IRQF_TRIGGER_FALLING, "miph"}, 
    {IRQ_EINT10, IRQF_TRIGGER_RISING, "lipe"}, 
};

static volatile int press_cnt [] = {0,0};

static DECLARE_WAIT_QUEUE_HEAD(miph_waitq);

static volatile int ev_press = 0;


static irqreturn_t miph_interrupt(int irq, void *dev_id)
{
    volatile int *press_cnt = (volatile int *)dev_id;
    //printk("Come into interrupt 4."); 
    *press_cnt = *press_cnt + 1; 
    ev_press = 1;                
    wake_up_interruptible(&miph_waitq);
    
    return IRQ_RETVAL(IRQ_HANDLED);
}

static int s3c24xx_miph_open(struct inode *inode, struct file *file)
{
/*
    int i;
    int err;
    
    for (i = 0; i < sizeof(miph_irqs)/sizeof(miph_irqs[0]); i++) {
        err = request_irq(miph_irqs[i].irq, miph_interrupt, IRQF_TRIGGER_RISING | miph_irqs[i].flags, miph_irqs[i].name, (void *)&press_cnt[i]);
        if (err)
            break;
    }

    if (err) {
        i--;
        for (; i >= 0; i--)
            free_irq(miph_irqs[i].irq, (void *)&press_cnt[i]);
        return -EBUSY;
    }
*/    
    return 0;
}

static int s3c24xx_miph_close(struct inode *inode, struct file *file)
{
    int i;
/*    
    for (i = 0; i < sizeof(miph_irqs)/sizeof(miph_irqs[0]); i++) {
        free_irq(miph_irqs[i].irq, (void *)&press_cnt[i]);
    }
*/
    return 0;
}

static int s3c24xx_miph_read(struct file *filp, char __user *buff, 
                                         size_t count, loff_t *offp)
{
        unsigned long err;
        unsigned int temp=0;
        temp=(readl(S3C_GPBDAT)&0x02)>>1;
        err = copy_to_user(buff, &temp, sizeof(temp));
        printk("GPBDAT2 is %x\n",temp);


/*
    unsigned long err;
    
    wait_event_interruptible(miph_waitq, ev_press);

    ev_press = 0;

    err = copy_to_user(buff, (const void *)press_cnt, min(sizeof(press_cnt), count));
    memset((void *)press_cnt, 0, sizeof(press_cnt));
*/
    return err ? -EFAULT : 0;
}

static struct file_operations s3c24xx_miph_fops = {
    .owner   =   THIS_MODULE,   
    .open    =   s3c24xx_miph_open,
    .release =   s3c24xx_miph_close, 
    .read    =   s3c24xx_miph_read,
};

static int __init s3c24xx_miph_init(void)
{
    int ret;
	s3c_gpio_cfgpin(S3C_GPB1,S3C_GPB1_INP);
        s3c_gpio_pullup(S3C_GPB1, 0);

    ret = register_chrdev(miph_MAJOR, DEVICE_NAME, &s3c24xx_miph_fops);
    if (ret < 0) {
      printk(DEVICE_NAME " can't register major number\n");
      return ret;
    }
    
    printk(DEVICE_NAME " initialized\n");
    return 0;
}

static void __exit s3c24xx_miph_exit(void)
{
    unregister_chrdev(miph_MAJOR, DEVICE_NAME);
}

module_init(s3c24xx_miph_init);
module_exit(s3c24xx_miph_exit);

MODULE_AUTHOR("UP-TECH");             
MODULE_DESCRIPTION("UP-MAGIC MIPH Driver");   
MODULE_LICENSE("GPL");                              

