#include <linux/module.h>
#include <linux/timer.h>
#include <linux/jiffies.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("user");

static struct timer_list timer1;
static int delay = 500;

void timer_callback(struct timer_list *timer)
{
    printk(KERN_ALERT "timer!\n");
    mod_timer(&timer1, jiffies + msecs_to_jiffies(delay));
}

int init_module(void)
{
    timer_setup(&timer1, timer_callback, 0);
    mod_timer(&timer1, jiffies + msecs_to_jiffies(delay));
    return 0;
}

void cleanup_module(void)
{
    del_timer(&timer1);
    printk(KERN_ALERT "timer stopped\n");
}
