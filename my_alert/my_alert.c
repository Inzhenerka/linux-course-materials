#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("user");

int my_alert(const char *dev, const char *msg)
{
    printk(KERN_ALERT "Module %s sent message: %s\n", dev, msg);
    return 0;
}

EXPORT_SYMBOL(my_alert);

