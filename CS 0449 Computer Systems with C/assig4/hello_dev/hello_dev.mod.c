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
__attribute_used__
__attribute__((section("__versions"))) = {
	{ 0x189b029e, "struct_module" },
	{ 0x56fc11bf, "misc_deregister" },
	{ 0x1b7d4074, "printk" },
	{ 0xdc52c022, "misc_register" },
	{ 0x2da418b5, "copy_to_user" },
	{ 0xd0d8621b, "strlen" },
};

static const char __module_depends[]
__attribute_used__
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "1C26E7B357AB9F7E02D4B45");
