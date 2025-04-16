#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/mm_types.h>

#define DEV_NAME "mmap-radio"
#define DEV_CLASS "mmapdemo"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("user");

static const int dev_range = 1;

static int radio_init;
static dev_t radio_first;
static struct class *radio_class;
static struct cdev radio_dev;

struct mmap_info {
    char *message;
    int counter;
};

void vm_open(struct vm_area_struct *vma)
{
    struct mmap_info *info = (struct mmap_info*)vma->vm_private_data;
    info->counter++;
}

void vm_close(struct vm_area_struct *vma)
{
    struct mmap_info *info = (struct mmap_info*)vma->vm_private_data;
    info->counter--;
}

vm_fault_t vm_fault(struct vm_fault *vmf)
{
    struct page *page;
    struct mmap_info *info;
    struct vm_area_struct *vma = vmf->vma;

    info = (struct mmap_info*)vma->vm_private_data;

    if(!info->message) return 0;

    page = virt_to_page(info->message);
    get_page(page);
    
    vmf->page = page;    
    
    return 0; 
}

int mmap_open(struct inode *inode, struct file *filp)
{
    struct mmap_info *info = NULL;
    char *msg = "This is mmap radio speaking!"; 

    info = kmalloc(sizeof(struct mmap_info), GFP_KERNEL);
    info->message = (char*)get_zeroed_page(GFP_KERNEL);
    memcpy(info->message, msg, strlen(msg));

    filp->private_data = info;

    return 0;
}

int mmap_release(struct inode *inode, struct file *filp)
{
    struct mmap_info *info = filp->private_data;

    free_page((unsigned long)info->message);
    kfree(info);

    filp->private_data = NULL;

    return 0;
}

struct vm_operations_struct vmops = {
    .open = vm_open,
    .close = vm_close,
    .fault = vm_fault
};

int mmap_op(struct file *filp, struct vm_area_struct *vma)
{
    vma->vm_ops = &vmops;
    vm_flags_set(vma, VM_DONTEXPAND | VM_DONTDUMP);
    vma->vm_private_data = filp->private_data;
    vm_open(vma);
    return 0;
}

static const struct file_operations mmap_fops = {
    .owner = THIS_MODULE,
    .open = mmap_open,
    .release = mmap_release,
    .mmap = mmap_op
};

int init_module(void)
{
    
    radio_init = alloc_chrdev_region(&radio_first, 0, dev_range, DEV_NAME);
    if(radio_init < 0)
    {
        printk(KERN_ALERT DEV_NAME " device region not allocated\n");
        return radio_init;
    }

    if((radio_class = class_create(DEV_CLASS)) == NULL)
    {
        unregister_chrdev_region(radio_first, dev_range);
        printk(KERN_ALERT "couldn't create new character device\n");
        return -ENODEV;
    }

    if((device_create(radio_class, NULL, radio_first, NULL, DEV_NAME)) == NULL)
    {
        class_destroy(radio_class);
        unregister_chrdev_region(radio_first, dev_range);
        printk(KERN_ALERT DEV_NAME " was not created\n");
        return -ENODEV;
    }

    cdev_init(&radio_dev, &mmap_fops);

    if((cdev_add(&radio_dev, radio_first, dev_range)) == -1)
    {
        device_destroy(radio_class, radio_first);
        class_destroy(radio_class);
        unregister_chrdev_region(radio_first, dev_range);
        printk(KERN_ALERT DEV_NAME " files were not created\n");
        return -EPERM;
    }

    printk(KERN_ALERT DEV_NAME " module and device ready, major number = %d\n",
                                                    MAJOR(radio_first));
    return 0;
}

void cleanup_module(void)
{
    cdev_del(&radio_dev);
    device_destroy(radio_class, radio_first);
    class_destroy(radio_class);
    unregister_chrdev_region(radio_first, dev_range);

    printk(KERN_ALERT DEV_NAME " exited\n");

    return;
}

