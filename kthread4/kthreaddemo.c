#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/delay.h>

#define STEPS 100

MODULE_LICENSE("GPL");
MODULE_AUTHOR("user");

static struct task_struct *thread1;
static struct task_struct *thread2;

static struct mutex mtx;

static int counter = 0;

int thread_func1(void *data)
{
    long id = (long)data;
    int i;

    for(i = 0; i < STEPS; i++)
    {
        if(i%10 == 0) printk(KERN_ALERT "%ld %d\n", id, counter);
        counter++;

        if(i == STEPS/2) mutex_unlock(&mtx);

        if(kthread_should_stop())
        {
            mutex_unlock(&mtx);
            break;
        }
    }

    return 0;
}

int thread_func2(void *data)
{
    long id = (long)data;
    int i;

    while((counter < STEPS/2) && !mutex_trylock(&mtx)) schedule();

    for(i = 0; i < STEPS; i++)
    {
        if(i%10 == 0) printk(KERN_ALERT "%ld %d\n", id, counter);
        //counter++;

        if(kthread_should_stop())
        {
            break;
        }
    }

    return 0;
}

int init_module(void)
{
    char thread_name1[] = "counter1";
    char thread_name2[] = "counter2";
    printk(KERN_ALERT "kthreaddemo started\n");
    mutex_init(&mtx);

    thread1 = kthread_create(thread_func1, (void*)1, thread_name1);
    if(!thread1)
    {
        printk(KERN_ALERT "kthreaddemo cannot start thread1!\n");
        mutex_destroy(&mtx);
        return -ENOSYS;
    }
    get_task_struct(thread1);
    wake_up_process(thread1);

    thread2 = kthread_create(thread_func2, (void*)2, thread_name2);
    if(!thread2)
    {
        kthread_stop(thread1);
        mutex_destroy(&mtx);
        printk(KERN_ALERT "kthreaddemo cannot start thread2!\n");
        return -ENOSYS;
    }
    get_task_struct(thread2);
    mutex_trylock(&mtx);
    wake_up_process(thread2);

    printk(KERN_ALERT "kthreaddemo working\n");
    return 0;
}

void cleanup_module(void)
{
    kthread_stop(thread1);
    put_task_struct(thread1);
    kthread_stop(thread2);
    put_task_struct(thread2);
    //mutex_unlock(&mtx);
    mutex_destroy(&mtx);
    printk(KERN_ALERT "kthreaddemo exited, counter = %d\n", counter);
}
