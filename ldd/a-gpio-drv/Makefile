CC = arm-linux-gcc

obj-m := mygpio_drv.o
KDIR := /home/akaedu/teacher_li/linux-2.6.35.7/

all:
	make mygpio_test
	make -C $(KDIR)	SUBDIRS=$(PWD) 	modules
	ls -l *.ko mygpio_test

clean:
	-rm *.ko *.o *.order *.mod.c *.symvers
	-rm mygpio_test
