#include "hello.h"

void cleanup_module(void)
{
    my_alert(DEV_NAME, "exited");
}
