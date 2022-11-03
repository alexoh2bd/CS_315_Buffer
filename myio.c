
#include "myio.h"
#define BUFFERSIZE 20000

int myread(int count, struct file_stream *stream, char *dest){// file descriptor, byte count, file_stream
    if(count == 0){
        return 0;   
    }
    int preoffset = stream->fileoffset;
    int temp = stream->readBuf_offset + count; 
    int bytesread = 0; // number of bytes read
    stream->placeholder += stream->readBuf_offset;
    
    if(temp > stream->size){ // overflow    
        int rem = count; 
        if (stream->fileoffset!=0){// memcopy remainder of buffer
            memcpy((void *)((int *)(dest +stream->fileoffset)),(void *)(stream->readBuf+stream->readBuf_offset), (unsigned int)(stream->size - stream->readBuf_offset));
            rem -= (stream->size-stream->readBuf_offset);
            stream->fileoffset+=(stream->size-stream->readBuf_offset);
            stream-> readBuf_offset = 0;
        }
        
        // read MAXSIZE, memcpy temp to dest
        int iter = 0;
        while (rem > stream->size){
            bytesread += read(stream->fd, (void *)(stream->readBuf+stream->fileoffset), stream->size);
            memcpy((void *)((int *)(dest+ stream ->fileoffset)), (void *)stream ->readBuf, (unsigned int)stream->size);
            rem -=stream->size;
            stream->fileoffset += stream->size;
            iter ++;
        }  
        bytesread += read(stream->fd, (void *)(stream->readBuf+stream->fileoffset), stream->size);
        memcpy((void *)((int *)(dest+ stream ->fileoffset)), (void *)stream ->readBuf, (unsigned int)rem);
        stream->fileoffset += rem;
        stream->readBuf_offset += rem;

        printf("Read MAXSIZE, memcpy temp to dest %d times\n", iter);
        
    }
    else if(stream->fileoffset ==0){ // New read from scratch
        bytesread += read(stream->fd, (void *)(stream->readBuf+stream->fileoffset), stream->size);
        memcpy((void *)((int *)(dest+ stream ->fileoffset)), (void *)stream ->readBuf, (unsigned int)count);
        stream->fileoffset += count;
        stream->readBuf_offset += count;

        printf("New read from scratch\n");
    }
    else{ // No need for READ, memcpy temp to dest

        memcpy((void *)((int *)(dest+ stream ->fileoffset)), (void *)(stream ->readBuf + stream -> readBuf_offset), (unsigned int)count);
        stream -> readBuf_offset += count;
        stream -> fileoffset += count;
        printf("No READ, memcpy temp to dest\n");
    }

    printf("Count is %d\n", count);
    printf("Diff is %d\n", stream->fileoffset-preoffset);
    printf("Bytesread is %d\n", bytesread);
    printf("File Offset is %d\n", stream->fileoffset);
    printf("Buffer Offset is %d\n", stream->readBuf_offset);
    printf("Placeholder is %p\n\n", (void *)(dest+stream->fileoffset));
    printf("\n\n");

    return bytesread;
}

int mywrite(int count, struct file_stream *stream, int *dest){

   // int temp = stream->offset + count;
    return 1;


}

struct file_stream myopen(char *pathname, int flags){
    //what more do we have to do for open?

    struct file_stream stream;

    stream.fileoffset = 0;
    stream.readBuf_offset = 0;

    stream.fd = open(pathname, flags);
    if(stream.fd==-1){
        perror("fd");
        exit(EXIT_FAILURE);
    }

    stream.readBuf = malloc(BUFFERSIZE);
    //add malloc error handling
  //  stream.size = read(stream.fd, stream.readBuf, BUFFERSIZE);
    stream.size = BUFFERSIZE;
    // read returns the amount of read_buf read, USE LATER for purposed other than error handling
    if(stream.size== -1){
        perror("read");
        exit(EXIT_FAILURE);
    }
    //add a malloc for the write buffer

    return stream;
}

int myclose(struct file_stream* stream){
    //what more?

    free(stream->readBuf);

    if(close(stream->fd)==-1){
        perror("Error");
        return -1; // is this right?
    }

    return 0;
}
