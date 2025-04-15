#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("user");

static int __init hello_init(void)
{
    printk(KERN_ALERT "module started\n");
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_ALERT "module exited\n");
    return;
}

module_init(hello_init);
module_exit(hello_exit);

