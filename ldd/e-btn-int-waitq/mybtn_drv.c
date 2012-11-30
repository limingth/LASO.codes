#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <asm/io.h>
#include <linux/kdev_t.h>

#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/irqreturn.h>

#include <linux/wait.h>

MODULE_LICENSE("GPL");

static volatile int * vmem_btn;

static DECLARE_WAIT_QUEUE_HEAD(wq);
static int flag = 0;

irqreturn_t myhandler(int irq, void * p)
{
	printk("<myhandler> current->comm = %s\n", current->comm);

	flag = 1;
	//wake_up_interruptible(&wq);
	wake_up(&wq);

	return IRQ_HANDLED;	
}

int mybtn_open(struct inode * inode, struct file * filp)
{
	int local = 100;
	int ri;

	printk("mybtn open called!\n");

	printk("<driver> &local = %p\n", &local);
	printk("current = %p\n", current);
	printk("current pid = %d\n", current->pid);
	printk("current process name = %s\n", current->comm);
	printk("task struct size = %d\n", sizeof(*current));

	vmem_btn = ioremap(0xe0200C44, 4);

	ri = request_irq(160, myhandler, IRQF_TRIGGER_FALLING, "btn K1 interrupt", NULL);

	printk("mybtn open called finished!\n");
	
	return 0;
}

int mybtn_release(struct inode * inode, struct file * filp)
{
	printk("mybtn release ok!\n");

	free_irq(160, NULL);

	return 0;
}

ssize_t mybtn_read(struct file * filp, char __user * buf, size_t count, loff_t * pos)
{
	//int prev, curr;
	int i;

	printk("mybtn read ok!\n");

	//wait_event_interruptible(wq, flag == 1);
	wait_event(wq, flag == 1);
	if (flag == 1)
	{
		flag = 0;
		printk("K1 is pressed!\n");
		*(buf) = '1';
	}
	else
	{
		printk("CTRL+C is pressed!\n");
		*(buf) = 'C';
	}

	for (i = 0; i < 4095; i++)
		*(buf+1+i) = '\0';

#if 0
	prev = 1;	
	while (1)
	{
		curr = *vmem_btn & (1);

	//	printk("prev = %d, curr = %d!\n", prev, curr);
	//	if (prev == 1 && curr == 0)
		if (prev - curr == 1)
			break;	

		prev = curr;
	}
#endif

	return 4096;
}

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

struct file_operations mybtn_fops =
{
	.open = mybtn_open,
	.read = mybtn_read,
//	.write = mybtn_write,
//	.flush = mybtn_flush,
	.release = mybtn_release,
};

static __init int mybtn_init(void)
{
	int rc;

	printk("mybtn init\n");

	// register mybtn_drv 
	rc = register_chrdev(240, "this is my first char drv", &mybtn_fops);

	printk("rc = %d\n", rc);

	return 0;
}


static __exit void mybtn_exit(void)
{
	printk("mybtn exit\n");

	// unregister mybtn_drv 
	unregister_chrdev(240, "this is my first char drv");

	return;
}

module_init(mybtn_init);
module_exit(mybtn_exit);


