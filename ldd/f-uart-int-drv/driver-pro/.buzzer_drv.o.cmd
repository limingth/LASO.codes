cmd_/home/akaedu/teacher_li/myhands/f-uart-int-drv/driver-pro/buzzer_drv.o := arm-linux-gcc -Wp,-MD,/home/akaedu/teacher_li/myhands/f-uart-int-drv/driver-pro/.buzzer_drv.o.d  -nostdinc -isystem /usr/bin/opt/FriendlyARM/toolschain/4.5.1/bin/../lib/gcc/arm-none-linux-gnueabi/4.5.1/include -I/home/akaedu/teacher_li/linux-2.6.35.7/arch/arm/include -Iinclude  -include include/generated/autoconf.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-s5pv210/include -Iarch/arm/plat-s5p/include -Iarch/arm/plat-samsung/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -marm -fno-omit-frame-pointer -mapcs -mno-sched-prolog -mabi=aapcs-linux -mno-thumb-interwork -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -Wframe-larger-than=1024 -fno-stack-protector -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack  -DMODULE -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(buzzer_drv)"  -D"KBUILD_MODNAME=KBUILD_STR(uart)"  -c -o /home/akaedu/teacher_li/myhands/f-uart-int-drv/driver-pro/buzzer_drv.o /home/akaedu/teacher_li/myhands/f-uart-int-drv/driver-pro/buzzer_drv.c

deps_/home/akaedu/teacher_li/myhands/f-uart-int-drv/driver-pro/buzzer_drv.o := \
  /home/akaedu/teacher_li/myhands/f-uart-int-drv/driver-pro/buzzer_drv.c \
  /home/akaedu/teacher_li/linux-2.6.35.7/arch/arm/include/asm/io.h \
    $(wildcard include/config/arm/dma/mem/bufferable.h) \
    $(wildcard include/config/mmu.h) \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /home/akaedu/teacher_li/linux-2.6.35.7/arch/arm/include/asm/types.h \
  include/asm-generic/int-ll64.h \
  /home/akaedu/teacher_li/linux-2.6.35.7/arch/arm/include/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/linux/posix_types.h \
  include/linux/stddef.h \
  include/linux/compiler.h \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  include/linux/compiler-gcc4.h \
  /home/akaedu/teacher_li/linux-2.6.35.7/arch/arm/include/asm/posix_types.h \
  /home/akaedu/teacher_li/linux-2.6.35.7/arch/arm/include/asm/byteorder.h \
  include/linux/byteorder/little_endian.h \
  include/linux/swab.h \
  /home/akaedu/teacher_li/linux-2.6.35.7/arch/arm/include/asm/swab.h \
  include/linux/byteorder/generic.h \
  /home/akaedu/teacher_li/linux-2.6.35.7/arch/arm/include/asm/memory.h \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/thumb2/kernel.h) \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/dram/size.h) \
    $(wildcard include/config/dram/base.h) \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/discontigmem.h) \
  include/linux/const.h \
  arch/arm/mach-s5pv210/include/mach/memory.h \
    $(wildcard include/config/mach/smdkv210.h) \
    $(wildcard include/config/mach/mini210.h) \
  /home/akaedu/teacher_li/linux-2.6.35.7/arch/arm/include/asm/sizes.h \
  include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
  include/asm-generic/memory_model.h \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
    $(wildcard include/config/sparsemem.h) \
  /home/akaedu/teacher_li/linux-2.6.35.7/arch/arm/include/asm/system.h \
    $(wildcard include/config/cpu/xsc3.h) \
    $(wildcard include/config/cpu/fa526.h) \
    $(wildcard include/config/arch/has/barriers.h) \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/cpu/sa1100.h) \
    $(wildcard include/config/cpu/sa110.h) \
    $(wildcard include/config/cpu/32v6k.h) \
  include/linux/linkage.h \
  /home/akaedu/teacher_li/linux-2.6.35.7/arch/arm/include/asm/linkage.h \
  include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  include/linux/typecheck.h \
  /home/akaedu/teacher_li/linux-2.6.35.7/arch/arm/include/asm/irqflags.h \
  /home/akaedu/teacher_li/linux-2.6.35.7/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/cpu/endian/be8.h) \
    $(wildcard include/config/arm/thumb.h) \
  /home/akaedu/teacher_li/linux-2.6.35.7/arch/arm/include/asm/hwcap.h \
  /home/akaedu/teacher_li/linux-2.6.35.7/arch/arm/include/asm/outercache.h \
    $(wildcard include/config/outer/cache/sync.h) \
    $(wildcard include/config/outer/cache.h) \
  include/asm-generic/cmpxchg-local.h \
  arch/arm/mach-s5pv210/include/mach/io.h \
  include/linux/delay.h \
  include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/spinlock/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
  /usr/bin/opt/FriendlyARM/toolschain/4.5.1/bin/../lib/gcc/arm-none-linux-gnueabi/4.5.1/include/stdarg.h \
  include/linux/bitops.h \
    $(wildcard include/config/generic/find/first/bit.h) \
    $(wildcard include/config/generic/find/last/bit.h) \
    $(wildcard include/config/generic/find/next/bit.h) \
  /home/akaedu/teacher_li/linux-2.6.35.7/arch/arm/include/asm/bitops.h \
  include/asm-generic/bitops/non-atomic.h \
  include/asm-generic/bitops/fls64.h \
  include/asm-generic/bitops/sched.h \
  include/asm-generic/bitops/hweight.h \
  include/asm-generic/bitops/arch_hweight.h \
  include/asm-generic/bitops/const_hweight.h \
  include/asm-generic/bitops/lock.h \
  include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  include/linux/dynamic_debug.h \
  /home/akaedu/teacher_li/linux-2.6.35.7/arch/arm/include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/debug/bugverbose.h) \
  include/asm-generic/bug.h \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
  /home/akaedu/teacher_li/linux-2.6.35.7/arch/arm/include/asm/div64.h \
  /home/akaedu/teacher_li/linux-2.6.35.7/arch/arm/include/asm/delay.h \
  /home/akaedu/teacher_li/linux-2.6.35.7/arch/arm/include/asm/param.h \
    $(wildcard include/config/hz.h) \

/home/akaedu/teacher_li/myhands/f-uart-int-drv/driver-pro/buzzer_drv.o: $(deps_/home/akaedu/teacher_li/myhands/f-uart-int-drv/driver-pro/buzzer_drv.o)

$(deps_/home/akaedu/teacher_li/myhands/f-uart-int-drv/driver-pro/buzzer_drv.o):
