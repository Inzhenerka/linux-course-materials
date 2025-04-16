#include "proc.h"
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("user");

static struct proc_ops fops;
char r_buffer[BUF_SIZE] = "proc demo message";

int init_module(void)
{
    struct proc_dir_entry *proc_node = 0;

    memset(&fops, 0, sizeof(fops));
    fops.proc_open = node_open;
    fops.proc_release = node_release;
    fops.proc_read = node_read;
    fops.proc_write = node_write;
    
    if(!(proc_node = proc_create(DEV_NAME, 0, NULL, &fops)))
    {
        printk(KERN_ALERT DEV_NAME " cannot create /proc file\n");
        return -EACCES;
    }    

    printk(KERN_ALERT DEV_NAME " started\n");

    return 0;
}

void cleanup_module(void)
{
    remove_proc_entry(DEV_NAME, NULL);
    printk(KERN_ALERT DEV_NAME " exited\n");
}


