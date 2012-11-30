
all:
	cd driver && make
	make -C app
	ls -l

clean:
	make -C driver clean
	make -C app clean
	-rm shell
	-rm *.ko
	-rm *.order
	-rm *.sym*
