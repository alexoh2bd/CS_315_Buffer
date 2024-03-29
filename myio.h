#ifndef __my__io
#define __my__io
#include <stdio.h>

typedef struct file_stream{
    int fd;
    int endOfFile;
    char *readBuf;
    int readBuf_size;
    int readBuf_offset;
    char *writeBuf; //write buff size won't differ from BUFFERSIZE ??
    int writeBuf_offset;
    int fileoffset;
} file_stream;

//int extern MAXSIZE;
int myread(int count, struct file_stream *stream, char *dest);
int mywrite(int count, struct file_stream *stream, char *src);
struct file_stream *myopen(char *pathname, int flags);
int myclose(struct file_stream* stream);
int myflush(struct file_stream *stream);
int myseek(struct file_stream *stream, off_t offset, int whence);

//struct file_stream myopen(char *pathname, int flags);

#endif
