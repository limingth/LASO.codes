#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <asm/io.h>
#include <linux/cdev.h>

MODULE_LICENSE("GPL");

//#define DPRINT(x)	printk("<%s> " #x " = %d\n", __func__, x);
#define DPRINT(x)

int uart_putchar(char c);
char uart_getchar(void);
void uart_init(int which);

int myuart_open(struct inode * inode, struct file * filp)
{
	DPRINT(filp->f_path.dentry->d_inode->i_rdev);
	DPRINT(inode->i_rdev);

	uart_init(MINOR(inode->i_rdev));

	return 0;
}

int myuart_release(struct inode * inode, struct file * filp)
{
	DPRINT(filp->f_path.dentry->d_inode->i_rdev);
	DPRINT(inode->i_rdev);
	return 0;
}

ssize_t myuart_read(struct file * filp, char __user * buf, size_t count, loff_t * pos)
{
	DPRINT(filp->f_path.dentry->d_inode->i_rdev);

	buf[0] = uart_getchar();

	return 1;
}

ssize_t myuart_write(struct file * filp, const char __user * buf, size_t count, loff_t * pos)
{
	DPRINT(filp->f_path.dentry->d_inode->i_rdev);

	uart_putchar(buf[0]);

	return 1;
}

int myuart_flush(struct file * filp, fl_owner_t id)
{
	DPRINT(filp->f_path.dentry->d_inode->i_rdev);

	return 0;
}

struct file_operations myuart_fops =
{
	.open = myuart_open,
	.read = myuart_read,
	.write = myuart_write,
	.flush = myuart_flush,
	.release = myuart_release,
};

static dev_t uart_dev;
static struct cdev uart_cdev;

static __init int myuart_init(void)
{
	int rc;

	uart_dev = MKDEV(241, 0);

	rc = register_chrdev_region(uart_dev, 4, "myttyS");
	DPRINT(rc);

	cdev_init(&uart_cdev, &myuart_fops);
	cdev_add(&uart_cdev, uart_dev, 4);
	
	return 0;
}


static __exit void myuart_exit(void)
{
	unregister_chrdev_region(uart_dev, 4); 

	cdev_del(&uart_cdev);

	return;
}

module_init(myuart_init);
module_exit(myuart_exit);


