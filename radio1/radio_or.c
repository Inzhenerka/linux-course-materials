#include "radio.h"

static int radio_count = 0;

int radio_open(struct inode *inode, struct file *file)
{
    if(radio_count > 0) return -EBUSY;
    radio_count++;
    printk(KERN_ALERT DEV_NAME " in use\n");
    return 0;
}

int radio_release(struct inode *inode, struct file *file)
{
    radio_count--;
    printk(KERN_ALERT DEV_NAME " released\n");
    return 0;
}


