#include <linux/module.h>
#include <asm/io.h>

MODULE_LICENSE("GPL");

static int * vmem_led;
static int * vmem_buzzer_con;
static int * vmem_buzzer;
static int * vmem_btn;

#include <asm/current.h>
#include <linux/sched.h>

int delay(void)
{
	/* tell compiler: do not optimize */
	volatile int i;

	printk("&i = %p\n", &i);
	printk("current->pid = %d, comm = %s\n", current->pid, current->comm);

	for (i = 0; i < 1000000; i++)
		;

	return 0;
}

void myexit(void)
{
}

module_init(delay);
module_exit(myexit);

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

void init_all(void)
{
	vmem_led = ioremap(0xe0200284, 4);
	vmem_buzzer_con = ioremap(0xe02000A0, 4);
	vmem_buzzer = ioremap(0xe02000A4, 4);
	vmem_btn = ioremap(0xe0200C44, 4);

	/* set GPIO CON = output 0001 */
	*vmem_buzzer_con = 0x1;
}

EXPORT_SYMBOL(init_all);
EXPORT_SYMBOL(led_blink);
EXPORT_SYMBOL(buzzer_beep);
EXPORT_SYMBOL(btn_get_id);
