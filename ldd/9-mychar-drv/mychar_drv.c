#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <asm/io.h>

MODULE_LICENSE("GPL");

int mychar_open(struct inode * in, struct file * filp)
{
	int local = 100;

	printk("mychar open called!\n");

	printk("current pid = %d\n", current->pid);
	printk("current parent pid = %d\n", current->parent->pid);
	printk("current process name = %s\n", current->comm);
	printk("current open function = %p\n", mychar_open);

	printk("<driver> &local = %p\n", &local);
	printk("task struct size = %d\n", sizeof(*current));

//	while (1);

	printk("mychar open called finished!\n");
	
	return 0;
}

int mychar_release(struct inode * inode, struct file * filp)
{
	printk("mychar release ok!\n");
	return 0;
}

ssize_t mychar_read(struct file * filp, char __user * buf, size_t count, loff_t * pos)
{
	static int size = 16;

	printk("mychar read ok!\n");
	printk("mychar read count = %d!\n", count);

	buf[0] = 'a';
	buf[1] = 'k';
	buf[2] = 'a';
	buf[3] = '\0';

	size -= 4;
	if (size >= 0)
		return 4;
	else 
		return 0;
}

static int * vmem_pled;

int delay(void)
{
	/* tell compiler: do not optimize */
	volatile int i;

	printk("&i = %p\n", &i);
	printk("current->pid = %d, comm = %s\n", current->pid, current->comm);

	for (i = 0; i < 10000000; i++)
		;

	return 0;
}

ssize_t mychar_write(struct file * filp, const char __user * buf, size_t count, loff_t * pos)
{
	int i;

	printk("mychar write ok!\n");
	printk("mychar write count = %d!\n", count);

	printk("buf = %p\n", buf);
	printk("buf[0] = %c\n", buf[0]);
	printk("buf[1] = %c\n", buf[1]);
	printk("buf[2] = %c\n", buf[2]);
	printk("buf[3] = %c\n", buf[3]);
//	printk("buf[count-1] = %c<%d>\n", buf[count-1], buf[count-1]);

	vmem_pled = ioremap(0xe0200284, 4);

	for (i = 0; i < 4; i++)
	{
		if (buf[i] == '0' || buf[i] == 0)	// led off
			*vmem_pled |= 1<<i;	
		else			// led on
			*vmem_pled &= ~(1<<i);	
	}

	delay();
	printk("mychar write finish!\n");

	return 4;
}

int mychar_flush(struct file * filp, fl_owner_t id)
{
	printk("mychar flush ok!\n");

	return 0;
}

struct file_operations mychar_fops =
{
	.open = mychar_open,
	.read = mychar_read,
	.write = mychar_write,
	.flush = mychar_flush,
	.release = mychar_release,
};

static __init int mychar_init(void)
{
	int rc;

	printk("mychar init\n");

	// register mychar_drv 
	rc = register_chrdev(240, "this is my first char drv", &mychar_fops);

	printk("rc = %d\n", rc);

	return 0;
}


static __exit void mychar_exit(void)
{
	printk("mychar exit\n");

	// unregister mychar_drv 
	unregister_chrdev(240, "this is my first char drv");

	return;
}

module_init(mychar_init);
module_exit(mychar_exit);


