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

static volatile USFR * puart;

static int channel = 0;

int uart_putchar(char c)
{
	while ((puart->utrstat & (1<<2)) == 0)
		;

	puart->utxh = c;

	return 0;
}

void uart_write_utxh(char c)
{
	puart->utxh = c;

	return;
}

char uart_read_urxh(void)
{
	return puart->urxh;
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
	
	/* which could be 0, 1, 2, 3 */
	channel = which;

	base_addr = 0xe2900000 + 0x400 * channel;

	puart = ioremap(base_addr, sizeof(USFR));
	puart->ulcon = 0x3;
	puart->ucon = 0x7c5;
	puart->ubrdiv = 0x23;
	puart->udivslot = 0x808;
	puart->ufcon = 0;
}

void uart_set_baudrate(int br)
{
	switch (br)
	{
		case 19200:
			puart->ubrdiv = 0xd5;
			break;

		case 115200:
			puart->ubrdiv = 0x23;
			break;
	}

	return;
}

void uart_enable_fifo(void)
{
	puart->ufcon = 1;

	return;
}	
