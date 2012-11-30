#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <asm/io.h>

MODULE_LICENSE("GPL");

#include <asm/uaccess.h>
static char kbuf[100];

static spinlock_t lock;

//static struct semaphore sem;
DECLARE_MUTEX(sem);

static struct mutex mymutex;

int mychar_open(struct inode * in, struct file * filp)
{
	printk("mychar open called!\n");

	//spin_lock_init(&lock);

	mutex_init(&mymutex);

	return 0;
}

int mychar_release(struct inode * inode, struct file * filp)
{
	printk("mychar release ok!\n");
	return 0;
}

ssize_t mychar_read(struct file * filp, char __user * buf, size_t count, loff_t * pos)
{
	int i;
	// read blackboard
//	copy_to_user(buf, kbuf, count);
	for (i = 0; i < count; i++)
		buf[i] = kbuf[i];

	printk("<%s: pid %d> mychar read count = %d, buf = %s\n", current->comm, current->pid, count, buf);
	printk("----------------------\n");

	// after read
	// 1 enable irq
	//local_irq_enable();

	// 2 spin unlock
	//spin_unlock(&lock);

	// 3 sem V
	//up(&sem);

	// 4 mutex
	mutex_unlock(&mymutex);

	return 0;
}

ssize_t mychar_write(struct file * filp, const char __user * buf, size_t count, loff_t * pos)
{
	int i;


	// before write
	// 1 disable irq
	//local_irq_disable();

	// 2 spin lock
	//spin_lock(&lock);

	// 3. sem P
	//down_interruptible(&sem);

	// 4. mutex
	mutex_lock(&mymutex);
	
	printk("----------------------\n");
	printk("<%s: pid %d> mychar write count = %d, buf = %s\n", current->comm, current->pid, count, buf);

	// write blackboard
	//copy_from_user(kbuf, buf, count);
	for (i = 0; i < count; i++)
		kbuf[i] = buf[i];

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
	rc = register_chrdev(250, "this is my first char drv", &mychar_fops);

	printk("rc = %d\n", rc);

	return 0;
}


static __exit void mychar_exit(void)
{
	printk("mychar exit\n");

	// unregister mychar_drv 
	unregister_chrdev(250, "this is my first char drv");

	return;
}

module_init(mychar_init);
module_exit(mychar_exit);


