/**************************************************************
	demo.c
	linux driver example for UP-netarm3000 & UP-netarm2410 
	It can be compiled for x86 PC
	author: zou jian-guo <ah_zou@163.com>
	date:   2004-8-20

***************************************************************/


//#define CONFIG_DEVFS_FS


#ifndef __KERNEL__
#  define __KERNEL__
#endif
#ifndef MODULE
#  define MODULE
#endif


#include <linux/config.h>
#include <linux/module.h>
#include <linux/devfs_fs_kernel.h>

#include <linux/init.h>
#include <linux/kernel.h>   /* printk() */
#include <linux/slab.h>   /* kmalloc() */
#include <linux/fs.h>       /* everything... */
#include <linux/errno.h>    /* error codes */
#include <linux/types.h>    /* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h>    /* O_ACCMODE */
#include <linux/poll.h>    /* COPY_TO_USER */
#include <asm/system.h>     /* cli(), *_flags */

#define DEVICE_NAME		"demo"
#define demo_MAJOR 254
#define demo_MINOR 0
static int MAX_BUF_LEN=1024;
static char drv_buf[1024];
static int WRI_LENGTH=0;

/*************************************************************************************/
/*逆序排列缓冲区数据*/
static void do_write()
{
	int i;
	int len = WRI_LENGTH;
	int mid = len>>1;
	char tmp;
	for(i = 0; i < mid; i++,len--){
		tmp = drv_buf[len-1];
		drv_buf[len-1] = drv_buf[i];
		drv_buf[i] = tmp;
	}
}
/*************************************************************************************/
static ssize_t  demo_write(struct file *filp,const char *buffer, size_t count)
{ 
	if(count > MAX_BUF_LEN)count = MAX_BUF_LEN;
	copy_from_user(drv_buf , buffer, count);
	WRI_LENGTH = count;
	printk("user write data to driver\n");
	do_write();	
	return count;
}
/*************************************************************************************/
static ssize_t  demo_read(struct file *filp, char *buffer, size_t count, loff_t *ppos)
{
	if(count > MAX_BUF_LEN)
		count=MAX_BUF_LEN;
	copy_to_user(buffer, drv_buf,count);
	printk("user read data from driver\n");
	return count;
}
/*************************************************************************************/
static int demo_ioctl(struct inode *inode, struct file *file, 
                 unsigned int cmd, unsigned long arg)
{
	printk("ioctl runing\n");
	switch(cmd){
		case 1:printk("runing command 1 \n");break;
		case 2:printk("runing command 2 \n");break;
		default:
			printk("error cmd number\n");break;
	}
	return 0;
}
/*************************************************************************************/
static int demo_open(struct inode *inode, struct file *file)
{
	sprintf(drv_buf,"device open sucess!\n");
	printk("device open sucess!\n");
	return 0;
}
/*************************************************************************************/
static int  demo_release(struct inode *inode, struct file *filp)
{
	MOD_DEC_USE_COUNT;
	printk("device release\n");
	return 0;
}

/*************************************************************************************/
static struct file_operations demo_fops = {
	owner:	THIS_MODULE,
	write:	demo_write,	
	read:	demo_read,	
	ioctl:	demo_ioctl,
	open:	demo_open,
	release:	demo_release,
};
/*************************************************************************************/

#ifdef CONFIG_DEVFS_FS
static devfs_handle_t  devfs_demo_dir, devfs_demoraw;
#endif

/*************************************************************************************/
static int __init demo_init(void)
{
#ifdef CONFIG_DEVFS_FS
	devfs_demo_dir = devfs_mk_dir(NULL, "demo", NULL);
	devfs_demoraw = devfs_register(devfs_demo_dir, "0", DEVFS_FL_DEFAULT,
			demo_MAJOR, demo_MINOR, S_IFCHR | S_IRUSR | S_IWUSR,
			&demo_fops, NULL);
#else
	int  result;
    SET_MODULE_OWNER(&demo_fops);
    result = register_chrdev(demo_MAJOR, "demo", &demo_fops);
    if (result < 0) return result;
//    if (demo_MAJOR == 0) demo_MAJOR = result; /* dynamic */
#endif
	printk(DEVICE_NAME " initialized\n");
	return 0;
}

/*************************************************************************************/
static void __exit  demo_exit(void)
{
    unregister_chrdev(demo_MAJOR, "demo");
    //kfree(demo_devices);
	printk(DEVICE_NAME " unloaded\n");
}

/*************************************************************************************/
module_init(demo_init);
module_exit(demo_exit);
