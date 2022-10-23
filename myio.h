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
    int *DATA;
    int size;
    int offset;
    int placeholder;
} file_stream;

int MAXSIZE;
int myread(int count, struct file_stream *stream, int *dest);

#endif
