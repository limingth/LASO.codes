#include <stdio.h>
#include <fcntl.h>

#include <sys/types.h>
#include <unistd.h>

#define DF_BTN		"mybtn"

int main(int argc, char * argv[])
{
	int fd;
	int ret;
	char buf[4096];

	printf("hello, test char drv\n");

	fd = open(DF_BTN, O_RDWR); 
	printf("fd = %d\n", fd);

	while (1)
	{
		int i;

		read(fd, buf, 4096);
		printf("Key %c is down\n", *buf);
	}

	close(fd);

	return 0;
}
