#ifndef _PROC_H_
#define _PROC_H_

#include <linux/module.h>

#define DEV_NAME "procdemo"
#define BUF_SIZE 1024

extern char r_buffer[BUF_SIZE];

int node_open(struct inode*, struct file*);
int node_release(struct inode*, struct file*);

ssize_t node_read(struct file*, char*, size_t, loff_t*);
ssize_t node_write(struct file*, const char*, size_t, loff_t*);

#endif /*_PROC_H_*/
