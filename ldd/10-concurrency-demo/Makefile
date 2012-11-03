
CC = gcc

obj-m := blackboard_drv.o

KDIR := /usr/src/linux-headers-2.6.32-33-generic/

all:
	make app1
	make app2
	make modules -C $(KDIR) SUBDIRS=$(PWD)

clean:
	rm app1 app2
	rm *.ko

test:
	sudo insmod blackboard_drv.ko
	./app1 bb
	./app2 bb
	sudo rmmod blackboard_drv

i:	
	sudo insmod blackboard_drv.ko

r:
	sudo rmmod blackboard_drv
	
t1:
	./app1 bb

t2:
	./app2 bb
	
	
