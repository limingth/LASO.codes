#include <stdio.h>
#include <fcntl.h>

char wbuf[10] = "200";
char rbuf[10];

int main(int argc, char * argv[])
{
	int fd;

	if (argc > 1)
		fd = open(argv[1], O_RDWR); 
	else
	{
		printf("pls: mknod bb c 250 0 and <./a.out bb> \n");
		return 0;
	}

	printf("fd = %d\n", fd);
	if (fd < 0)
	{
		printf("open bb failed \n");
		return 0;
	}

	int err = 0;
	while (1)
	{
		write(fd, wbuf, 4);
		read(fd, rbuf, 4);

		if (strcmp(wbuf, rbuf) == 0)
			;//printf("OK! good bye!\n");
		else
			printf("user 2 ERR %d! faint!\n", err++);
	}

	close(fd);

	return 0;
}
