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

	if (main_argc > 1)
		fd = open(main_argv[1], O_RDWR | O_NONBLOCK); 
	else
		fd = open("myttyS3", O_RDWR); 

	// set baud rate = 19200
//	ioctl(fd, 0, 19200);

	sleep(1);

	printf("fd = %d\n", fd);

	printf("Welcome to mybootloader 1.0 (%s)\n", __DATE__);

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
