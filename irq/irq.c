#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>

static int irq = 1;
static int dev_id;
static int irq_counter = 0;

static irqreturn_t kb_int(int irq, void *dev_id)
{
    irq_counter++;
    printk(KERN_ALERT "counter = %d\n", irq_counter);
    return IRQ_NONE;//IRQ_HANDLED
}

int init_module(void)
{
    if(request_irq(irq, kb_int, IRQF_SHARED, "kb_int", &dev_id))
        return -1;
    printk(KERN_ALERT "IRQ module loaded successfully\n");
    return 0;
}

void cleanup_module(void)
{
    synchronize_irq(irq);
    free_irq(irq, &dev_id);
    printk(KERN_ALERT "IRQ module finished\n");
}

MODULE_AUTHOR("user");
MODULE_LICENSE("GPL");

