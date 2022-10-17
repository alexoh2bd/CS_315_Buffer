#ifndef __my__io
#define __my__io

//int buffer[10000];

typedef struct file_stream{
    int fd;
    int *readData;
    int *writeData;
    int size;
    int offset;


} file_stream;


int myread(int count, struct file_stream stream, void *dest);




#endif