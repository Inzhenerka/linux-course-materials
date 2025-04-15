#include "hello.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("user");

int init_module(void)
{
    my_alert(DEV_NAME, "started");
    return 0;
}
