#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif



static const char ____versions[]
__used __section("__versions") =
	"\x14\x00\x00\x00\xbb\x6d\xfb\xbd"
	"__fentry__\0\0"
	"\x1c\x00\x00\x00\x6e\x64\xf7\xb3"
	"kthread_should_stop\0"
	"\x10\x00\x00\x00\x7e\x3a\x2c\x12"
	"_printk\0"
	"\x18\x00\x00\x00\x38\xf0\x13\x32"
	"mutex_unlock\0\0\0\0"
	"\x1c\x00\x00\x00\xca\x39\x82\x5b"
	"__x86_return_thunk\0\0"
	"\x14\x00\x00\x00\x51\x0e\x00\x01"
	"schedule\0\0\0\0"
	"\x18\x00\x00\x00\xbf\xd3\x9e\xbb"
	"mutex_trylock\0\0\0"
	"\x18\x00\x00\x00\x9f\x0c\xfb\xce"
	"__mutex_init\0\0\0\0"
	"\x20\x00\x00\x00\x2c\xe6\x42\x81"
	"kthread_create_on_node\0\0"
	"\x18\x00\x00\x00\x18\x5f\x46\xbe"
	"wake_up_process\0"
	"\x20\x00\x00\x00\x5f\x69\x96\x02"
	"refcount_warn_saturate\0\0"
	"\x18\x00\x00\x00\x3d\xd0\xd3\xc0"
	"kthread_stop\0\0\0\0"
	"\x1c\x00\x00\x00\xcb\xf6\xfd\xf0"
	"__stack_chk_fail\0\0\0\0"
	"\x1c\x00\x00\x00\x92\x0c\x98\xd5"
	"__put_task_struct\0\0\0"
	"\x18\x00\x00\x00\x3a\x0a\xd8\xfc"
	"module_layout\0\0\0"
	"\x00\x00\x00\x00\x00\x00\x00\x00";

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "9ED608A2841EEB8F01FC09D");
