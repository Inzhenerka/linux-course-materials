#include "radio.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("user");

static struct file_operations fops;
static int radio_major;
char r_buffer[BUF_SIZE];

int init_module(void)
{
    memset(&fops, 0, sizeof(fops));
    fops.owner = THIS_MODULE;
    fops.open = radio_open;
    fops.release = radio_release;
    fops.read = radio_read;
    fops.write = radio_write;
    
    radio_major = register_chrdev(0, DEV_NAME, &fops);
    if(radio_major < 0)
    {
        printk(KERN_ALERT DEV_NAME " was not registered\n");
        return radio_major;
    }    

    printk(KERN_ALERT DEV_NAME " registered, major number = %d\n", radio_major);

    return 0;
}

void cleanup_module(void)
{
    unregister_chrdev(radio_major, DEV_NAME);
    printk(KERN_ALERT DEV_NAME " exited\n");
}


