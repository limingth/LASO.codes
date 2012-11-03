#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <asm/io.h>
#include <linux/cdev.h>

#include <linux/wait.h>
#include <linux/interrupt.h>
#include <asm/uaccess.h>

#include "buzzer_drv.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("li ming");
MODULE_DESCRIPTION("This is a demo of uart driver");

static int v = 0;
module_param(v, int, 0);

//#define DPRINT(x)	printk("<%s> " #x " = 0x%x\n", __func__, (int)x);
//#define DPRINT(x)

#define DPRINT(x)	\
			do \
			{ \
				if (v == 1) \
					printk("<%s> " #x " = 0x%x\n", __func__, (int)x); \
				else \
					; \
			} while (0) 
	

#include "uart_drv.h"

wait_queue_head_t rx_waitq;
static int rxbuf_full = 0;

wait_queue_head_t tx_waitq;
static int txbuf_busy = 0;

static char kbuf[4096];

static struct work_struct mywork;
//static struct delayed_work mywork;

static struct timer_list mytimer;

static void timer_handler(unsigned long arg)
{
	buzzer_off();

	return;
}

static void work_handler(struct work_struct *data)
{
//	buzzer_beep(1);
	
	// get current time and set next call time
	mod_timer(&mytimer, jiffies + HZ / 50); 

	// start timer and buzzer on
	buzzer_on();

	return;
}

static struct tasklet_struct mytasklet;

static void tasklet_handler(unsigned long data)
{
//	buzzer_beep(1);

	// get current time and set next call time
	mod_timer(&mytimer, jiffies + HZ / 50); 

	// start timer and buzzer on
	buzzer_on();

	return;
}

static irqreturn_t uart_rx_handler(int irq, void * dev_id)
{
	DPRINT(irq);

	/* must read urxh reg in irq handler, or you get unending irqs */
	kbuf[0] = uart_read_urxh();
	
	rxbuf_full = 1;
	wake_up_interruptible(&rx_waitq);

	tasklet_schedule(&mytasklet);
//	schedule_work(&mywork);
	//schedule_delayed_work(&mywork, 1000);

	return IRQ_HANDLED;
}

static irqreturn_t uart_tx_handler(int irq, void * dev_id)
{
	DPRINT(irq);

	uart_write_utxh(kbuf[0]);

	txbuf_busy = 0;
	wake_up_interruptible(&tx_waitq);

	/* irq will be enable in write() call */
	disable_irq_nosync(irq);

	return IRQ_HANDLED;
}

int uart_open(struct inode * inode, struct file * filp)
{
	int channel = 0;
	int ri;

	DPRINT(filp->f_path.dentry->d_inode->i_rdev);
	DPRINT(inode->i_rdev);
	DPRINT(filp->f_flags);

	channel = MINOR(inode->i_rdev);
	DPRINT(channel);

	uart_init(channel);

	// must init wait queue before requesting tx irq handler
	init_waitqueue_head(&rx_waitq);
	init_waitqueue_head(&tx_waitq);
	
	// init timer
	init_timer(&mytimer);

	mytimer.function = timer_handler;
	add_timer(&mytimer);

	// uart rx irq handler -> BH
	tasklet_init(&mytasklet, tasklet_handler, 0);
	INIT_WORK(&mywork, work_handler);

	printk("request rx irq\n");
	ri = request_irq(16+channel*4, uart_rx_handler, 0, "uart rx irq", NULL);
	DPRINT(ri);
	if (ri != 0)
	{
		free_irq(16+channel*4, NULL);
		ri = request_irq(16+channel*4, uart_rx_handler, 0, "uart read irq", NULL);
		DPRINT(ri);
	}
	printk("request tx irq\n");

	printk("disable tx irq\n");
	disable_irq(18+channel*4);

	ri = request_irq(18+channel*4, uart_tx_handler, 0, "uart tx irq", NULL);
	DPRINT(ri);
	if (ri != 0)
	{
		free_irq(18+channel*4, NULL);
		ri = request_irq(18+channel*4, uart_tx_handler, 0, "uart tx irq", NULL);
		DPRINT(ri);
	}

	return 0;
}

int uart_release(struct inode * inode, struct file * filp)
{
	int channel = 0;

	DPRINT(filp->f_path.dentry->d_inode->i_rdev);
	DPRINT(inode->i_rdev);
	DPRINT(filp->f_flags);
	
	channel = MINOR(inode->i_rdev);
	DPRINT(channel);

	del_timer_sync(&mytimer);

	free_irq(16+channel*4, NULL);
	free_irq(18+channel*4, NULL);

	return 0;
}

ssize_t uart_read(struct file * filp, char __user * buf, size_t count, loff_t * pos)
{
	static int cnt = 0;
	int ret;

	DPRINT(filp->f_path.dentry->d_inode->i_rdev);
	DPRINT(filp->f_flags);
	DPRINT(count);

	// wait and then get uart data directly
	wait_event_interruptible(rx_waitq, rxbuf_full == 1);
	rxbuf_full = 0;
	DPRINT(rxbuf_full);

	//kbuf = uart_get_urxh();
	/* get data from urxh to kbuf in irq handler */
	DPRINT(kbuf[0]);

	// echo it 
	//uart_putchar(kbuf[0]);

	ret = copy_to_user(buf, kbuf, 1);
	DPRINT(ret);

	if (cnt++ >= 5)
		return 0;

	/* return 0 is ok */
	if (ret == 0)
		return 4096;

	return 0;
}

ssize_t uart_write(struct file * filp, const char __user * buf, size_t count, loff_t * pos)
{
	int channel = 0;
	struct inode * inode;
	int ret;

	DPRINT(filp->f_path.dentry->d_inode->i_rdev);
	DPRINT(filp->f_flags);

	inode = filp->f_path.dentry->d_inode;
	channel = MINOR(inode->i_rdev);
	DPRINT(channel);

	// wait and then send uart data directly
	wait_event_interruptible(tx_waitq, txbuf_busy == 0);
	txbuf_busy = 1;
	DPRINT(txbuf_busy);

	// kbuf is not busy
	ret = copy_from_user(kbuf, buf, count);
	DPRINT(ret);
	
	// send char in write handler
	enable_irq(18+channel*4);

	return 1;
}

int uart_ioctl(struct inode * inode, struct file * filp, unsigned int cmd, unsigned long arg)
{
	DPRINT(cmd);
	DPRINT(arg);

#define UART_SET_BUAD_RATE	0
#define UART_ENABLE_FIFO	1

	switch (cmd)
	{
		case UART_SET_BUAD_RATE:
			uart_set_baudrate(arg);
			break;

		case UART_ENABLE_FIFO:
			uart_enable_fifo();
			break;
	}

	return 0;
}

int uart_flush(struct file * filp, fl_owner_t id)
{
	DPRINT(filp->f_path.dentry->d_inode->i_rdev);

	return 0;
}

struct file_operations uart_fops =
{
	.open = uart_open,
	.read = uart_read,
	.write = uart_write,
	.ioctl = uart_ioctl,
	.flush = uart_flush,
	.release = uart_release,
};

static dev_t uart_dev;
static struct cdev uart_cdev;

static __init int uart_mod_init(void)
{
	int rc;

	printk("uart module init ok!\n");
	printk("v = %d\n", v);
	printk("jiffies = 0x%x\n", (int)jiffies);
	printk("HZ = %d\n", HZ);

	uart_dev = MKDEV(241, 0);

	rc = register_chrdev_region(uart_dev, 4, "ttyS");
	DPRINT(rc);

	cdev_init(&uart_cdev, &uart_fops);
	cdev_add(&uart_cdev, uart_dev, 4);
	
	buzzer_init();
	buzzer_beep(1);

	return 0;
}


static __exit void uart_mod_exit(void)
{
	printk("uart module exit ok!\n");

	unregister_chrdev_region(uart_dev, 4); 

	cdev_del(&uart_cdev);

	buzzer_beep(2);

	return;
}

module_init(uart_mod_init);
module_exit(uart_mod_exit);

