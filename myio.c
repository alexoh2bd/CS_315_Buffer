
#include "myio.h"

int myread(int count, struct file_stream *stream, char *dest)
{// file descriptor, byte count, file_stream
    
    if(count == 0){
        return 0;   
    }

    int remainder;
    int dest_offset = 0;
    int bytesread = 0;// number of bytes read
    // stream->placeholder += stream->offset; //what is placeholder

    if(stream->readBuf_size==0){
        if( (stream->readBuf_size = read(stream->fd, stream->readBuf, BUFFERSIZE)) == -1){
            perror("myopen: read");
            exit(EXIT_FAILURE);
        }
    }

    if(stream->readBuf_offset + count <= stream->readBuf_size){ //request is within the buffer
        memcpy((void *)(dest), (void *)(stream ->readBuf+stream->readBuf_offset), (unsigned long)count);
        stream->readBuf_offset += count;

        printf("memcpy within buffer\n");
        return count;
    }
    else{ //(stream->offset + count > stream->buf_size){     //make sure this behaves right
        printf("buffer is gonna be full\n");
        remainder = count;
        while(stream->readBuf_offset + remainder > stream->readBuf_size){
            dest_offset += stream->readBuf_size - stream->readBuf_offset;
            memcpy((void *)(dest),(void *)(stream->readBuf+stream->readBuf_offset), (unsigned int)(stream->readBuf_size - stream->readBuf_offset)); // memcpy whats left in the buffer
            remainder -= stream->readBuf_size - stream->readBuf_offset;

            if( (bytesread = read(stream->fd, stream->readBuf, BUFFERSIZE)) < 0){
                perror("myread: read");
                exit(EXIT_FAILURE);
            }
            if(bytesread == EOF){
                printf("myread: End of file");
                exit(EXIT_FAILURE);
            }
            //what is bytes read is not EOF but just less than BUFFERSIZE
            stream->readBuf_offset = 0;
            stream->fileoffset += bytesread;
        }
        memcpy((void *)(dest+dest_offset), (void *)(stream->readBuf),remainder); //new buffer contains all remaining data needed
        stream->readBuf_offset = remainder;
    }
    
    
    return count; // this might be wrong, look into
}
// does not take into account malloc

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