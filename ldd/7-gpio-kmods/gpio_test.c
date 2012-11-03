#include <linux/module.h>
#include <asm/io.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("limingth");
MODULE_DESCRIPTION("led module driver");
MODULE_VERSION("version1.0");
MODULE_ALIAS("myled test");

#if 1
extern void led_blink(int n);
extern void buzzer_beep(int n);
extern int btn_get_id(void);
extern void init_all(void);
#endif

static __init int gpio_init(void)
{
	int btn_id;

	printk("gpio init ok!\n");
	printk("&btn_id = %p\n", &btn_id);

	init_all();

	while (1)
	{
		btn_id = btn_get_id();

		led_blink(btn_id);

		buzzer_beep(btn_id);
	
		if (btn_id == 4)
			break;
	}

	printk("finished!\n");

	return 0;
}

static __exit void gpio_exit(void)
{
	printk("gpio exit ok!\n");

	return;
}

module_init(gpio_init);
module_exit(gpio_exit);

