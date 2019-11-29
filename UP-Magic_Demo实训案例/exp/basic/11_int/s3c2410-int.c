
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

#include <asm/hardware.h>

#include <asm/arch/S3C2410.h>
#include <asm/arch/irqs.h>

/* debug macros */
//#undef DEBUG
#define DEBUG
#ifdef DEBUG
#define DPRINTK( x... )	printk("s3c2410-int: " ##x)
#else
#define DPRINTK( x... )
#endif


#define DEVICE_NAME  "s3c2410 int"
#define s3c2410_IRQ5		IRQ_EINT5	//IRQ_EINT3


#define GPIO_key_int01  (GPIO_MODE_IN | GPIO_PULLUP_DIS | GPIO_F3)

#define led01_enable() \
	({ 	GPCCON &=~ 0xc00;		\
		GPCCON |= 0x400;              \
		GPCDAT&=~ 0x20;          \
		GPCDAT |= 0x0;     \
})

#define led01_disable() \
		({ GPCDAT&=~ 0x20;          \
		GPCDAT |= 0x20;   \
})

#define led02_enable() \
    ({  GPCCON &=~ 0x3000;       \
        GPCCON |= 0x1000;              \
        GPCDAT&=~ 0x40;          \
        GPCDAT |= 0x0;     \
        })

#define led02_disable() \
        ({ GPCDAT&=~ 0x40;          \
           GPCDAT |= 0x40;   \
         })

#define led03_enable() \
    ({  GPCCON &=~ 0xc000;       \
        GPCCON |= 0x4000;              \
        GPCDAT&=~ 0x80;          \
        GPCDAT |= 0x0;     \
        })

#define led03_disable() \
        ({ GPCDAT&=~ 0x80;          \
           GPCDAT |= 0x80;   \
          })



static void s3c2410_IRQ5_fun(int irq, void *dev_id, struct pt_regs *reg)
{
      int i =0 ;
    	DPRINTK("enter interrupt 3 !\n");
        for (i=0;i<2;i++)
        	{
         led01_enable();
		 mdelay(800);
	     led01_disable();
	     mdelay(800);
         led02_enable();
         mdelay(800);
         led02_disable();
         mdelay(800);
         led03_enable();
         mdelay(800);
         led03_disable();
		}
}

static int __init s3c2410_interrupt_init(void)
{
	int  i, ret;
	int flags;


    set_gpio_ctrl(GPIO_key_int01);

    led01_disable();
    led02_disable();
    led03_disable();
 
    
    for (i=0;i<2;i++)
    {
        led01_enable();
        led02_enable();
        led03_enable();
        // printk(DEVICE_NAME"GPCCON:%x\t GPCDAT:%x\t\n", GPCCON, GPCDAT );
        mdelay(500);
        led01_disable();
        led02_disable();
        led03_disable();
        //  printk (DEVICE_NAME"GPCCON:%x\t GPCDAT:%x\t\n",GPCCON, GPCDAT );
        mdelay(500);
        
        

    }
     

    local_irq_save(flags);
	
    ret = set_external_irq(s3c2410_IRQ5, EXT_RISING_EDGE, GPIO_PULLUP_DIS);
    if (ret){

        printk("s3c2410_IRQ5  set_external_irq  failure");
        return ret;

    }
	local_irq_restore(flags);


	ret = request_irq(s3c2410_IRQ5, s3c2410_IRQ5_fun, SA_INTERRUPT, "s3c2410_IRQ5", s3c2410_IRQ5_fun);
	if (ret)
    {
        printk("s3c2410_IRQ5 request_irq  failure");

        return ret;
    }

	printk(DEVICE_NAME " int01   initialized\n");
	
	return 0;
}

static void __exit s3c2410_interrupt_exit(void)
{

	printk(DEVICE_NAME " unloaded\n");
}

module_init(s3c2410_interrupt_init);
module_exit(s3c2410_interrupt_exit);

