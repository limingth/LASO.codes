
obj-m := hello.o

#KDIR := /home/limingth/tiny210/src/linux-2.6.35.7
KDIR := /home/akaedu/teacher_li/linux-2.6.35.7/

all:
	make -C $(KDIR)	SUBDIRS=$(PWD) 	modules

clean:
	rm -rf *.o *.ko *.mod.* *.cmd 
	rm -rf .*

