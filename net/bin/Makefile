all:

cpnet:
	cp linux-2.6.35.7/arch/arm/boot/zImage net-zImage

cpnonet:
	cp linux-2.6.35.7/arch/arm/boot/zImage no-net-zImage
	
mk:
	./mkimage -A arm -O linux -T kernel -C none -a 21000000 -e 21000040 -n linux-2.6.35.7 -d no-net-zImage nn-uImage
	cp nn-uImage ..
	./mkimage -A arm -O linux -T kernel -C none -a 21000000 -e 21000040 -n linux-2.6.35.7 -d net-zImage net-uImage
	cp net-uImage ..
