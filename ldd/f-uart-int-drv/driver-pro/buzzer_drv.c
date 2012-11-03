
#include <asm/io.h>
#include <linux/delay.h>

static int * vmem_buzzer_con;
static int * vmem_buzzer;

void buzzer_init(void)
{
	vmem_buzzer_con = ioremap(0xe02000A0, 4);
	vmem_buzzer = ioremap(0xe02000A4, 4);

	/* set GPIO CON = output 0001 */
	*vmem_buzzer_con = 0x1;

	return;
}

void buzzer_on(void)
{
	*vmem_buzzer = 0x1;

	return;
}

void buzzer_off(void)
{
	*vmem_buzzer = 0x0;

	return;
}

void buzzer_beep(int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		buzzer_on();
		mdelay(100);
		
		buzzer_off();
		mdelay(100);
	}
}



