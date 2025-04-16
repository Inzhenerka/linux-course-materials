#include "radio.h"

ssize_t radio_write(struct file *file, const char *buffer, size_t length, loff_t *offset)
{
    int ofs = *offset;
    char *p;
    ssize_t len;
    int minor = iminor(file->f_inode);

    if(minor > 2) return -EINVAL;
    if(minor < 2) return -EACCES;

    if(ofs >= BUF_SIZE-1) return 0;

    if(ofs+length > BUF_SIZE-1) length = BUF_SIZE-1-ofs;

    len=length;
    for(p = r_buffer+ofs; len > 0; p++, len--, buffer++) get_user(*p, buffer);
   
    *offset += length; 

    *(p-1) = 0;

    return length;
}

