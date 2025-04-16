#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/delay.h>

#define STEPS 1000

MODULE_LICENSE("GPL");
MODULE_AUTHOR("user");

static struct task_struct *thread;

int thread_func(void *data)
{
    long counter = (long)data;
    int i;

    for(i = 0; i < STEPS; i++)
    {
        if(counter%10 == 0) printk(KERN_ALERT "%ld\n", counter);
        msleep(100);
        counter++;

        if(kthread_should_stop())
        {
            break;
        }
    }

    return 0;
}

int init_module(void)
{
    char thread_name[] = "counter";
    printk(KERN_ALERT "kthreaddemo started\n");

    thread = kthread_run(thread_func, (void*)0, thread_name);
    if(!thread)
    {
        printk(KERN_ALERT "kthreaddemoo cannot start thread!\n");
        return -ENOSYS;
    }

    printk(KERN_ALERT "kthreaddemo working\n");
    return 0;
}

void cleanup_module(void)
{
    kthread_stop(thread);
    printk(KERN_ALERT "kthreaddemo exited\n");
}
