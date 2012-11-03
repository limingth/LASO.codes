#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <asm/io.h>
#include <linux/kdev_t.h>

MODULE_LICENSE("GPL");

static int * vmem_pled;
static int * vmem_pbuzzer;
static int * vmem_btn;

int mychar_open(struct inode * inode, struct file * filp)
{
	int local = 100;

	int ma, mi;

	printk("mychar open called!\n");

	printk("inode->i_rdev = 0x%x\n", inode->i_rdev);

	ma = MAJOR(inode->i_rdev);
	mi = MINOR(inode->i_rdev);

	printk("ma = %d, mi = %d\n", ma, mi);

	printk("current = %p\n", current);
	printk("current parent = %p\n", current->parent);
	printk("<driver> &local = %p\n", &local);
	printk("current pid = %d\n", current->pid);
#if 0
	printk("current pid = %d\n", current->pid);
	printk("current parent pid = %d\n", current->parent->pid);
	printk("current process name = %s\n", current->comm);
	printk("current open function = %p\n", mychar_open);

	printk("task struct size = %d\n", sizeof(*current));
#endif

	if (mi == 0)
		vmem_pled = ioremap(0xe0200284, 4);

	if (mi == 1)
	{
		int * pbuzzer_con = ioremap(0xe02000A0, 4);
		*pbuzzer_con = 1;

		vmem_pbuzzer = ioremap(0xe02000A4, 4);
	}

	if (mi == 2)
		vmem_btn = ioremap(0xe0200C44, 4);

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
//	static int size = 16;
	struct inode * inode;
	int i;
	int ma, mi;

	inode = filp->f_path.dentry->d_inode;

	ma = MAJOR(inode->i_rdev);
	mi = MINOR(inode->i_rdev);

#if 0
	printk("<read> ma = %d, mi = %d\n", ma, mi);

	printk("mychar read ok!\n");
	printk("mychar read count = %d!\n", count);
#endif

	*buf = 0;
	for (i = 0; i < 4; i++)
	{
		if ((*vmem_btn & (1<<i)) == 0)
		{
			*buf = (i+1);
			break;
		}
	}
	
	return 1;
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

ssize_t mychar_write(struct file * filp, const char __user * buf, size_t count, loff_t * pos)
{
	int i;
	int ma, mi;
	struct inode * inode;

	inode = filp->f_path.dentry->d_inode;

	ma = MAJOR(inode->i_rdev);
	mi = MINOR(inode->i_rdev);

	printk("<write> ma = %d, mi = %d\n", ma, mi);

	printk("mychar write ok!\n");
	printk("mychar write count = %d!\n", count);

	printk("buf = %p\n", buf);
	printk("buf[0] = %c\n", buf[0]);
	printk("buf[1] = %c\n", buf[1]);
	printk("buf[2] = %c\n", buf[2]);
	printk("buf[3] = %c\n", buf[3]);
//	printk("buf[count-1] = %c<%d>\n", buf[count-1], buf[count-1]);

	if (mi == 0)
	{
		for (i = 0; i < 4; i++)
		{
			if (buf[i] == '0' || buf[i] == 0)	// led off
				*vmem_pled |= 1<<i;	
			else			// led on
				*vmem_pled &= ~(1<<i);	
		}
		return 4;
	}

	if (mi == 1)
	{
		if (buf[0] == '0' || buf[0] == 0)	// buzzer off
			*vmem_pbuzzer &= ~(1<<0);	
		else			// buzzer on
			*vmem_pbuzzer |= 1<<0;	

		return 1;
	}

	delay();
	printk("mychar write finish!\n");

	return 0;
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


