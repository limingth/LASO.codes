#include <linux/module.h>
#include <asm/io.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("limingth");
MODULE_DESCRIPTION("led module driver");
MODULE_VERSION("version1.0");
MODULE_ALIAS("myled test");

static int * vmem_led;
static int * vmem_buzzer_con;
static int * vmem_buzzer;
static int * vmem_btn;

static int led_no = 0;
module_param(led_no, int, 0);

void delay(void)
{
	/* tell compiler: do not optimize */
	volatile int i;

	for (i = 0; i < 10000000; i++)
		;
}

void led_blink(int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		*vmem_led = 0xF;
		delay();
		
		*vmem_led = 0x0;
		delay();
	}
}

void buzzer_beep(int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		*vmem_buzzer = 0x1;
		delay();
		
		*vmem_buzzer = 0x0;
		delay();
	}
}

int btn_get_id(void)
{
	int i;

	for (i = 0; i < 4; i++)
	{
		if ((*vmem_btn & (1<<i)) == 0)
			return i+1;
	}
		
	return 0; 
}


static __init int gpio_init(void)
{
	int btn_id;
	int i;

	printk("gpio init ok!\n");

	vmem_led = ioremap(0xe0200284, 4);
	vmem_buzzer_con = ioremap(0xe02000A0, 4);
	vmem_buzzer = ioremap(0xe02000A4, 4);
	vmem_btn = ioremap(0xe0200C44, 4);

	/* set GPIO CON = output 0001 */
	*vmem_buzzer_con = 0x1;

#if 0
	printk("led blink!\n");
	led_blink(3);

	printk("buzzer beep!\n");
	buzzer_beep(3);

	btn_id = btn_get_id();
	printk("btn id = %d\n", btn_id);
#endif
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

