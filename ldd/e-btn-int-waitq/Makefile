CC = arm-linux-gcc

obj-m := mybtn_drv.o
KDIR := /home/akaedu/teacher_li/linux-2.6.35.7/

all:
	make mybtn_test
	make -C $(KDIR)	SUBDIRS=$(PWD) 	modules
	ls -l *.ko mybtn_test

clean:
	-rm *.ko *.o *.order *.mod.c *.symvers
	-rm mybtn_test
