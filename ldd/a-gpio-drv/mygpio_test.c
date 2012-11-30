#include <stdio.h>
#include <fcntl.h>

#include <sys/types.h>
#include <unistd.h>

char testbuf[500000];

#define DF_LED		"myled"
#define DF_BUZZER	"mybuzzer"
#define DF_BTN		"mybtn"

int main(int argc, char * argv[])
{
	int fd[3];
	int ret;
	char buf[64];

	printf("hello, test char drv\n");

	fd[0] = open(DF_LED, O_RDWR); 
	printf("fd[0] = %d\n", fd[0]);

	fd[1] = open(DF_BUZZER, O_RDWR); 
	printf("fd[1] = %d\n", fd[1]);

	fd[2] = open(DF_BTN, O_RDWR); 
	printf("fd[2] = %d\n", fd[2]);

	ret = write(fd[1], "1", 1);
	ret = write(fd[0], "1111", 4);

	sleep(3);

	ret = write(fd[1], "0", 1);
	ret = write(fd[0], "0000", 4);

	while (1)
	{
		int i;

		read(fd[2], buf, 1);
	//	printf("Key %c is down\n", *buf + '0');

		for (i = 0; i < *buf; i++)
		{
			ret = write(fd[1], "1", 1);
			sleep(1);
			ret = write(fd[1], "0", 1);
			sleep(1);
		}
	}
		
#if 0
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

#endif
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);

	return 0;
}
