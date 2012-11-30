#include <stdio.h>

#if 0
#define UTXH	*(volatile unsigned int *)0xe2900020

int main(void)
{
	while (1)
		UTXH = 'a';

	return 0;
}
#endif

#include <sys/mman.h>		// mmap()
#include <fcntl.h>		// O_RDWR

int global = 100;

int main(void)
{
	int * vmem_uart = (int *)0x0;
	int * vmem_led = (int *)0x0;
	int uart = 0xe2900000;	// 0x20;
	int led = 0xe0200000; 	// 0x284;
	int fd;
	
	fd = open("/dev/mem", O_RDWR);

	printf("fd = %d\n", fd);
	
	vmem_uart = mmap(0, 1, PROT_READ|PROT_WRITE, MAP_SHARED, fd, uart);
	vmem_led = mmap(0, 1, PROT_READ|PROT_WRITE, MAP_SHARED, fd, led);

	printf("vmem uart = %p\n", vmem_uart);
	printf("vmem led = %p\n", vmem_led);

	printf(".text = %p\n", main);
	printf(".data = %p\n", &global);
	printf(".stack = %p\n", &uart);

	sleep(1);
	while (1)
	{
		*(vmem_uart + 0x20/4) = 'a';
		*(vmem_led + 0x284/4) = 0xf;
		sleep(1);

		*(vmem_uart + 8) = 'b';
		*(vmem_led + 0x284/4) = 0x0;
		sleep(1);
	}

	close(fd);

	return 0;
}

