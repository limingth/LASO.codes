#include <stdio.h>
#include <fcntl.h>

#include <sys/types.h>
#include <unistd.h>

int fd;

char uart_getchar(void)
{
	char c;

	read(fd, &c, 1);

	return c;
}

void uart_putchar(char c)
{
	write(fd, &c, 1);

	return;
}

int argc;
char * argv[10];

int main(int main_argc, char * main_argv[])
{
	int ret;
	char buf[64];

	fd = open(main_argv[1], O_RDWR); 

	printf("fd = %d\n", fd);

	printf("hello, test char drv\n");

	while (1)
	{
		int i;

		printf("LUMIT $ ");
		gets(buf);
	
		if (buf[0] == 'q')
			break;

		printf("your input: <%s>\n", buf);
		if (buf[0] == '\0')
			continue;

		argc = shell_parse(buf, argv);

		for (i = 0; i < argc; i++)
			printf("%d: <%s>\n", i, argv[i]);	

		command_do(argc, argv);
	}

	close(fd);

	return 0;
}
//#include "uart.h"

int putchar(int c)
{
	if (c == '\n')
		uart_putchar('\r');

	if (c == '\b')
	{
		uart_putchar('\b');
		uart_putchar(' ');	
	}

	uart_putchar((char)c);

	return c;	
}

int getchar(void)
{
	int c;

	c = (int)uart_getchar();

	if (c == '\r')
		return '\n';

	return c;
}

int puts(const char * s)
{
	while (*s)
		putchar(*s++);

	// arm-linux-gcc will optimize printf("hello\n") as puts("hello");
	// puts() function should print out '\n' as default
	putchar('\n');

	return 0;
}

char * gets(char * s)
{
	char * p = s;

	// note: here we use getchar(), not uart_getchar() for portability
	while ((*p = getchar()) != '\n')
	{
		if (*p != '\b')
			putchar(*p++);
		else	
			if (p > s)
				putchar(*p--);	
	}

	*p = '\0';
	putchar('\n');

	return s;
}

int shell_parse(char * buf, char * argv[])
{
	int argc = 0;
	int state = 0;

	while (*buf)
	{
		if (*buf != ' ' && state == 0)
		{
			argv[argc++] = buf;
			state = 1;
		}


		if (*buf == ' ' && state == 1)
		{
			*buf = '\0';
			state = 0;
		}

		buf++;	
	}

	return argc;
}
//#include "stdio.h"

void putchar_hex(char c)
{
	char * hex = "0123456789ABCDEF";	// good
	//char hex[] = "0123456789ABCDEF"; bad!

	putchar(hex[(c & 0xf0)>>4]);
	putchar(hex[(c & 0x0f)>>0]);
	//putchar(' ');
}

void putint_hex(int a)
{
	putchar_hex( (a>>24) & 0xFF );
	putchar_hex( (a>>16) & 0xFF );
	putchar_hex( (a>>8) & 0xFF );
	putchar_hex( (a>>0) & 0xFF );
}

char * itoa(int a, char * buf)
{
	int num = a;
	int i = 0;
	int len = 0;

	do
	{
		buf[i++] = num % 10 + '0';
		num /= 10;	
	} while (num);
	buf[i] = '\0';

	len = i;
	for (i = 0; i < len/2; i++)
	{
		char tmp;
		tmp = buf[i];
		buf[i] = buf[len-i-1];
		buf[len-i-1] = tmp;
	}

	return buf;	
}

#if 0
#include <stdarg.h>
#else
typedef int * va_list;
#define va_start(ap, A) (ap = (int *)&(A) + 1)
#define va_arg(ap, T) (*(T *)ap++)
#define va_end(ap) ((void)0)
#endif

static int _puts(const char * s)
{
	while (*s)
		putchar(*s++);

	return 0;
}

int printf(const char * format, ...)
{
	char c;	
	va_list ap;

	va_start(ap, format);

	while ((c = *format++) != '\0')
	{
		switch (c)
		{
			case '%':
				c = *format++;

				switch (c)
				{
					char ch;
					char * p;
					int a;
					char buf[100];

					case 'c':
					ch = va_arg(ap, int);
					putchar(ch);
					break;
					case 's':
					p = va_arg(ap, char *);
					_puts(p);
					break;	
					case 'x':
					a = va_arg(ap, int);
					putint_hex(a);
					break;	
					case 'd':
					a = va_arg(ap, int);
					itoa(a, buf);
					_puts(buf);
					break;	

					default:
					break;
				}	
				break;	

			default:
				putchar(c);
				break;
		}
	}

	return 0;	
}

int help(int argc, char * argv[])
{
	printf("help usage: \n");
	printf("md - memory dispaly\n");
	printf("mw - memory write\n");
	printf("loadb - load .bin file from uart\n");
	printf("go - go to address\n");
	printf("loadx - load .bin file using xmodem\n");

	return 0;
}

#include <sys/mman.h>		// mmap()
#include <fcntl.h>		// O_RDWR

int vmd(int addr)
{
	int * vmem;
	int fd;
	int base = addr & 0xFFFFF000;
	int offset = addr & 0xFFF;
	int ret;
	
//	printf("addr = 0x%x\n", addr);
//	printf("base = 0x%x, offset = 0x%x\n", base, offset);

	fd = open("/dev/mem", O_RDWR);
	
	vmem = mmap(0, 1, PROT_READ|PROT_WRITE, MAP_SHARED, fd, base);
//	printf("vmem = 0x%x\n", vmem);

	ret = *(vmem + offset/4);

	close(fd);
	
	return ret;
}

int md(int argc, char * argv[])
{	
	int * p = (int *)0;
	int i, j;

	if (argc >= 2)
		p = (int *)atoi(argv[1]);

	for (j = 0; j < 16; j++)
	{	
		printf("%x: ", (int)p);
		for (i = 0; i < 4; i++)
		{
			printf("%x ", vmd((int)p));	
			p++;
		}
		printf("\n");
	}

	return 0;
}

int vmw(int addr, int v)
{
	int * vmem;
	int fd;
	int base = addr & 0xFFFFF000;
	int offset = addr & 0xFFF;
	
	printf("addr = 0x%x, v = 0x%x\n", addr, v);
	printf("base = 0x%x, offset = 0x%x\n", base, offset);

	fd = open("/dev/mem", O_RDWR);
	
	vmem = mmap(0, 1, PROT_READ|PROT_WRITE, MAP_SHARED, fd, base);
	printf("vmem = 0x%x, v = 0x%x \n", vmem, v);

	*(vmem + offset/4) = v;

	close(fd);
	
	return 0;
}
	
// mw 0x0 0x1122
int mw(int argc, char * argv[])
{	
	int * p = (int *)0;
	int v = 0;

	printf("mw argv[1] = %s, [2] = %s\n", argv[1], argv[2]);
	if (argc >= 2)
		p = (int *)atoi(argv[1]);

	if (argc >= 3)
		v = atoi(argv[2]);

	printf("p = 0x%x, v = 0x%x\n", (int)p, v);

	// p should do mmap()
	//*p = v;
	vmw((int)p, v);

	return 0;
}

int command_do(int argc, char * argv[])
{
	printf("command do <%s> \n", argv[0]);

	if (strcmp(argv[0], "help") == 0)
		help(argc, argv);

	if (strcmp(argv[0], "md") == 0)
		md(argc, argv);

	if (strcmp(argv[0], "mw") == 0)
		mw(argc, argv);

	return 0;
}

int atoi(char * buf)
{
	int value = 0;	
	int base = 10;
	int i = 0;

	if (buf[0] == '0' && buf[1] == 'x')
	{
		base = 16;
		i = 2;
	}

	// 123 = (1 * 10 + 2) * 10 + 3
	// 0x1F = 1 * 16 + F(15)
	while (buf[i])
	{
		int tmp;

		if (buf[i] <= '9' && buf[i] >= '0')
			tmp = buf[i] - '0';
		else
			tmp = buf[i] - 'a' + 10;

		value = value * base + tmp;

		i++;
	}

	return value;
}

int strcmp(const char * s1, const char * s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
			return 0;	
		s1++;
		s2++;	
	}

	return *s1 - *s2;
}
