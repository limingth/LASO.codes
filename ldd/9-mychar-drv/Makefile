CC = arm-linux-gcc

obj-m := mychar_drv.o
KDIR := /home/akaedu/teacher_li/linux-2.6.35.7/

all:
	make mychar_test
	make -C $(KDIR)	SUBDIRS=$(PWD) 	modules
	ls -l *.ko mychar_test

clean:
	-rm *.ko *.o *.order *.mod.c *.symvers
	-rm mychar_test
