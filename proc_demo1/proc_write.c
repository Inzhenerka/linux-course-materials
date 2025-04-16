#include "proc.h"

ssize_t node_write(struct file *file, const char *buffer, size_t length, loff_t *offset)
{
    int ofs = *offset;
    char *p;
    ssize_t len;

    if(ofs >= BUF_SIZE-1) return 0;

    if(ofs+length > BUF_SIZE-1) length = BUF_SIZE-1-ofs;

    len=length;
    for(p = r_buffer+ofs; len > 0; p++, len--, buffer++) get_user(*p, buffer);
   
    *offset += length; 

    *(p-1) = 0;

    return length;
}

