#include <linux/module.h>
#include <asm/io.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("limingth");
MODULE_DESCRIPTION("led module driver");
MODULE_VERSION("version1.0");
MODULE_ALIAS("myled test");

static int * vmem;
static int led_no = 0;
module_param(led_no, int, 0);

static __init int led_init(void)
{
	printk("led init ok!\n");

//	*(int *)0xe0200284 = 0x0;
	vmem = ioremap(0xe0200284, 4);
	printk("vmem = %p\n", vmem);
//	*vmem = 0x0;
	*vmem &= ~(1 << led_no);

	return 0;
}

static __exit void led_exit(void)
{
	printk("led exit ok!\n");

//	*(int *)0xe0200284 = 0xf;
	*vmem = 0xf;

	return;
}

module_init(led_init);
module_exit(led_exit);

