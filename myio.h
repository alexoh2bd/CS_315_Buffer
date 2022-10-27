#ifndef __my__io
#define __my__io
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

typedef struct file_stream{
    int fd;
    int *readBuff;
    int size;
    int offset;
    int placeholder;
} file_stream;

//int extern MAXSIZE;
int myread(int count, struct file_stream *stream, int *dest);
struct file_stream myopen(char *pathname, int flags);
int myclose(struct file_stream* stream);

//struct file_stream myopen(char *pathname, int flags);

#endif
