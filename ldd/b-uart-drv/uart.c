#include <linux/module.h>
#include <asm/io.h>

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

void uart_init(int which)
{
	int base_addr;

	base_addr = 0xe2900000 + 0x400 * which;

	puart = ioremap(base_addr, sizeof(USFR));
	puart->ulcon = 0x3;
	puart->ucon = 0x7c5;
	puart->ubrdiv = 0x23;
	puart->udivslot = 0x808;
}

