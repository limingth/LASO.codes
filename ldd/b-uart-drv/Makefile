CC = arm-linux-gcc

obj-m := myuart.o

myuart-objs := uart.o myuart_drv.o

KDIR := /home/akaedu/teacher_li/linux-2.6.35.7/

all:
	cat main.c stdio.c shell.c printf.c command.c lib.c > myshell.c
	make myshell
	make -C $(KDIR)	SUBDIRS=$(PWD) 	modules
	ls -l *.ko 

clean:
	-rm *.ko *.o *.order *.mod.c *.symvers
