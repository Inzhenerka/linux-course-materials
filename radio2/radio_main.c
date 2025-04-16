#include "radio.h"
#include <linux/cdev.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("user");

static struct file_operations fops;
static dev_t radio_first;
static int radio_init;
static struct class *radio_class;
static struct cdev radio_dev;

int init_module(void)
{
    memset(&fops, 0, sizeof(fops));
    fops.owner = THIS_MODULE;
    fops.open = radio_open;
    fops.release = radio_release;
    
    radio_init = alloc_chrdev_region(&radio_first, 0, 1, DEV_NAME);
    if(radio_init < 0)
    {
        printk(KERN_ALERT DEV_NAME " allocation failed\n");
        return radio_init;
    }  

    radio_class = class_create("chdevice");
    if(radio_class == NULL)
    {
        unregister_chrdev_region(radio_first, 1);
        printk(KERN_ALERT DEV_NAME " class not created\n");
        return -ENODEV;
    }

    if((device_create(radio_class, NULL, radio_first, NULL, DEV_NAME)) == NULL)
    {
        class_destroy(radio_class);
        unregister_chrdev_region(radio_first, 1);
        printk(KERN_ALERT DEV_NAME " device not created\n");
        return -ENODEV;
    }

    cdev_init(&radio_dev, &fops);

    if((cdev_add(&radio_dev, radio_first, 1)) == -1)
    {
        device_destroy(radio_class, radio_first);
        class_destroy(radio_class);
        unregister_chrdev_region(radio_first, 1);
        printk(KERN_ALERT DEV_NAME " files not created\n");
        return -ENODEV;
    }

    printk(KERN_ALERT DEV_NAME " registered, major number = %d\n", MAJOR(radio_first));

    return 0;
}

void cleanup_module(void)
{
    cdev_del(&radio_dev);
    device_destroy(radio_class, radio_first);
    class_destroy(radio_class);
    unregister_chrdev_region(radio_first, 1);
    
    printk(KERN_ALERT DEV_NAME " exited\n");
}


