#include <linux/module.h>	// EXPORT_SYMBOL

int count = 1;
module_param(count, int, 0);

MODULE_LICENSE("GPL");

int hello_init(void)
{
	int i;

	printk("hello module init ok!\n");

	for (i = 0; i < count; i++)
		printk("init = %p\n", hello_init);

	return 0;
}

void hello_exit(void)
{
	printk("hello module exit ok!\n");
	return ;
}

module_init(hello_init);
module_exit(hello_exit);

//EXPORT_SYMBOL(hello_init);
//EXPORT_SYMBOL(hello_exit);

