CC = arm-linux-gcc

obj-m := uart.o

uart-objs := uart_mod.o uart_drv.o buzzer_drv.o

KDIR := /home/akaedu/teacher_li/linux-2.6.35.7/

all:
	make -C $(KDIR)	SUBDIRS=$(PWD) 	modules
	cp *.ko ../
	ls -l *.ko 

clean:
	-rm *.ko *.o *.order *.mod.c *.symvers
