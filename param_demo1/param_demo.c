#include <linux/module.h>

#define DEV_NAME "param_demo"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("user");

static int m_count = 1;
static char *m_char = "empty";

module_param(m_count, int, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
MODULE_PARM_DESC(m_count, "module counter");

module_param(m_char, charp, 0664);
MODULE_PARM_DESC(m_char, "module string");

int init_module(void)
{
    if(m_count==1) printk(KERN_ALERT DEV_NAME " using default counter, string = %s\n", m_char);
    else printk(KERN_ALERT DEV_NAME " parameters: %.*s\n", m_count, m_char);    

    return 0;
}

void cleanup_module(void)
{
    printk(KERN_ALERT DEV_NAME " exited\n");
}

