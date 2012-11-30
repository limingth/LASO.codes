
obj-m := gpio.o

KDIR := /home/akaedu/teacher_li/linux-2.6.35.7

all:
	make modules -C $(KDIR) SUBDIRS=$(PWD)

clean:
	-rm *.ko *.o *.order *.mod.c *.symvers

