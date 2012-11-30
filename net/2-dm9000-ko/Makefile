
obj-m := dm9000.o

all:
	make modules \
		-C /home/akaedu/teacher_li/linux-2.6.35.7/ \
		SUBDIRS=$(PWD) 
	ls *.ko -l

clean:
	rm *.o *.ko *.order *.symvers *.mod.c 
