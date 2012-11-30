
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_AUTHOR("AKAEDU");
MODULE_DESCRIPTION("module example ");
MODULE_LICENSE("GPL");

int global = 100;

int __init 
akae_init (void)
{
	int local = 200;
	printk ("Hello, akaedu\n");

	printk(".text = %p\n", akae_init);
	printk(".data = %p\n", &global);
	printk(".stack = %p\n", &local);
	return 0;
}

void __exit
akae_exit (void)
{
	int local = 300;
	printk ("module exit\n");

	printk(".text = %p\n", akae_exit);
	printk(".data = %p\n", &global);
	printk(".stack = %p\n", &local);
	return ;
}

module_init(akae_init);
module_exit(akae_exit);
