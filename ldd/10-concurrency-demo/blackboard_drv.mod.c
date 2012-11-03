#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xbce771f0, "module_layout" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x6dbc4825, "per_cpu__current_task" },
	{ 0x37bcd53a, "__register_chrdev" },
	{ 0x3d329378, "mutex_unlock" },
	{ 0x20f1ef60, "__mutex_init" },
	{ 0xb72397d5, "printk" },
	{ 0xb4390f9a, "mcount" },
	{ 0x76ecad99, "mutex_lock" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "6773F8DF73424E51D59E828");
