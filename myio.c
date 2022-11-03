
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

            free(stream->readBuf);
            stream->readBuf = malloc(stream->size);/*
            if(()==NULL){
                perror("myread: readbuff malloc");
                exit(EXIT_FAILURE);
            }*/
        }
        
        // read MAXSIZE, memcpy temp to dest
        int iter = 0;
        while (rem > stream->size){
            bytesread += read(stream->fd, (void *)(stream->readBuf+stream->readBuf_offset), stream->size);
            memcpy((void *)((int *)(dest+ stream ->fileoffset)), (void *)stream ->readBuf, (unsigned int)stream->size);
            rem -=stream->size;
            stream->fileoffset += stream->size;
            iter ++;
        }  
        bytesread += read(stream->fd, (void *)(stream->readBuf+stream->readBuf_offset), stream->size);
        memcpy((void *)((int *)(dest+ stream ->fileoffset)), (void *)stream ->readBuf, (unsigned int)rem);
        stream->fileoffset += rem;
        stream->readBuf_offset += rem;

        printf("Read MAXSIZE to read buffer %d times, memcpy to dest\n", iter);
        
    }
    else if(stream->fileoffset ==0){ // New read from scratch
        bytesread += read(stream->fd, (void *)(stream->readBuf+stream->readBuf_offset), stream->size);
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

int mywrite(int count, struct file_stream *stream, char *src)
{
    // check how much space is left in the write buffer
    //if there is space, just memcpy the data into the buffer
    //if there isn't space (2 options) (1)flush then memcpy or (2)memcpy to fill then flush then put the rest in
    //option(1)
    //flush write data to the file, then do the full memcpy

    if( (count+stream->writeBuf_offset) > BUFFERSIZE){
        printf("buffer is full\n");
        if( (myflush(stream)) == -1){ //or maybe do this manually? are their any differences?
            printf("myflush returned -1");
            exit(EXIT_FAILURE);
        } //fresh buffer
        if(count > BUFFERSIZE){
            write(stream->fd, src, count);
        }
        else{
            memcpy((stream->writeBuf+stream->writeBuf_offset), src, count);
            stream->writeBuf_offset += count;
        }
    }
    else{
        memcpy((stream->writeBuf+stream->writeBuf_offset), src, count);
        stream->writeBuf_offset += count;
        //done
    }
                        
    return 1;
}

int myflush(struct file_stream *stream)
{   
    if ( (write(stream->fd, stream->writeBuf, stream->writeBuf_offset)) ==-1){
        perror("myflush: write");
        exit(EXIT_FAILURE);
    }
    free(stream->writeBuf);
    if( (stream->writeBuf = malloc(BUFFERSIZE)) == NULL){ //reinit write buffer
        perror("myflush: writeBuff: malloc");
        exit(EXIT_FAILURE);
    }
    stream->writeBuf_offset=0;
    // is this all to "empty" the buffer  

    return 1; 
}

int myseek(int fd, off_t offset, int whence){

    //where is the file position indicator used

    //when using write sys call to write write buf contents to a field
    //But write has no parameter on where to write to 
    
    //When reading in data from a file


    
    return 1;
}

struct file_stream myopen(char *pathname, int flags)
{
    //what more do we have to do for open?

    struct file_stream stream;

    stream.readBuf_offset = 0;
    stream.writeBuf_offset = 0;
    stream.fileoffset = 0;

    stream.fd = open(pathname, flags, 0666);
    if(stream.fd==-1){
        perror("myopen: open");
        exit(EXIT_FAILURE);
    }
    if( (stream.writeBuf = malloc(BUFFERSIZE)) == NULL){ //write buffer init
        perror("myopen: writeBuff: malloc");
        exit(EXIT_FAILURE);
    }

    if( (stream.readBuf = malloc(BUFFERSIZE)) == NULL){ //read buffer init
        perror("myopen: readBuff: malloc");
    //add malloc error handling
  //  stream.size = read(stream.fd, stream.readBuf, BUFFERSIZE);
    stream.size = BUFFERSIZE;
    // read returns the amount of read_buf read, USE LATER for purposed other than error handling
    if(stream.size== -1){
        perror("read");
        exit(EXIT_FAILURE);
    }

    stream.fileoffset = stream.readBuf_size;

    //add a malloc for the write buffer

    return stream;
}


int myclose(struct file_stream* stream){
    //what more?

    free(stream->readBuf);
    free(stream->writeBuf);

    if(close(stream->fd)==-1){
        perror("myclose: close");
        exit(EXIT_FAILURE);
    }

    return 0;
}
