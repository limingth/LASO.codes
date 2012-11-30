#include "stdio.h"

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
