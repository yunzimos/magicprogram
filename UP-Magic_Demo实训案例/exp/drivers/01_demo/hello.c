
#include <linux/config.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>   /* printk() */


int init_module(void)
{

	printk("<1>hello world,i started! \n");
	return 0;

}

void cleanup_module(void)
{
	printk("<1>goodbye \n");

}
