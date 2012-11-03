#include <linux/module.h>
#include <asm/io.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("limingth");
MODULE_DESCRIPTION("uart module driver");
MODULE_VERSION("version1.0");
MODULE_ALIAS("myuart test");

struct uart_sfr
{
	int ulcon;
	int ucon;
	int ufcon;
	int umcon;
	int utrstat;
	int uerstat;
	int ufstat;
	int umstat;
	int utxh;
	int urxh;
	int ubrdiv;
	int udivslot;
};

typedef struct uart_sfr USFR;

static volatile USFR *puart;

int uart_putchar(char c)
{
	while ((puart->utrstat & (1<<2)) == 0)
		;

	puart->utxh = c;

	return 0;
}

char uart_getchar(void)
{
	char c;

	while ((puart->utrstat & (1<<0)) == 0)
		;

	c = puart->urxh;

	return c;
}

void uart_init(void)
{
	puart = ioremap(0xe2900c00, sizeof(USFR));
	puart->ulcon = 0x3;
	puart->ucon = 0x7c5;
	puart->ubrdiv = 0x23;
	puart->udivslot = 0x808;
}

static __init int uart_mod_init(void)
{
	printk("uart module init ok!\n");

	uart_init();

	while (1)
	{
		char ch;
		
		ch = uart_getchar();

		uart_putchar(ch);

		if (ch == 'q')
			break;
	}

	printk("finished!\n");

	return 0;
}

static __exit void uart_mod_exit(void)
{
	printk("uart module exit ok!\n");

	return;
}

module_init(uart_mod_init);
module_exit(uart_mod_exit);

