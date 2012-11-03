#include <stdio.h>
#include <fcntl.h>

#include <sys/types.h>
#include <unistd.h>

char testbuf[500000];

int main(int argc, char * argv[])
{
	int fd;
	int local = 100;

	int ret;
	char buf[64];

	testbuf[0] = 'L';
	testbuf[1] = 'M';
	testbuf[499999] = 'G';

	printf("hello, test char drv\n");
	printf("<main> &local = %p\n", &local);

	printf("current pid = %d\n", getpid());

	fd = open("mychar", O_RDWR); 
	printf("fd = %d\n", fd);

	if (fd < 0)
	{
		perror("open mychar failed!\n");
		return -1;
	}

	ret = read(fd, buf, 10);
	printf("<read> ret = %d\n", ret);
	printf("buf = %s\n", buf);

	ret = write(fd, argv[1], 4);
	printf("<write> ret = %d\n", ret);
	printf("<write> testbuf = %p\n", testbuf);

	close(fd);

	return 0;
}
