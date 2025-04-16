#include "radio.h"

static char *array_msg[] =
{
    "This is radio-0 device speaking",
    "This is radio-1 device speaking"
};

ssize_t radio_read(struct file *file, char *buffer, size_t length, loff_t *offset)
{
    char *msg = 0;
    int msg_length = 0;
    int ofs = *offset;
    char *p;
    ssize_t len;
    int minor = iminor(file->f_inode);

    if(minor > 2) return -EINVAL;
    if(minor == 2) return -EACCES;

    if(strlen(r_buffer) > 0) msg = r_buffer;
    else msg = array_msg[minor];
    msg_length = strlen(msg);

    if(ofs >= msg_length) 
    {
        *r_buffer = 0;
        return 0;
    }

    if(ofs+length > msg_length) length = msg_length-ofs;

    len=length;
    for(p = msg+ofs; len > 0; p++, len--, buffer++) put_user(*p, buffer);
   
    *offset += length; 

    return length;
}

