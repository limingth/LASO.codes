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
