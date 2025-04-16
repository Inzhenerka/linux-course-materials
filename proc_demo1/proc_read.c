#include "proc.h"

ssize_t node_read(struct file *file, char *buffer, size_t length, loff_t *offset)
{
    char *msg = r_buffer;
    int msg_length = strlen(msg);
    int ofs = *offset;
    char *p;
    ssize_t len;
    
    if(ofs >= msg_length) return 0;

    if(ofs+length > msg_length) length = msg_length-ofs;

    len=length;
    for(p = msg+ofs; len > 0; p++, len--, buffer++) put_user(*p, buffer);
   
    *offset += length; 

    return length;
}

