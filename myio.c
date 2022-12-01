
#include "myio.h"
#define BUFFERSIZE 1024

int myread(int count, struct file_stream *stream, char *dest){// file descriptor, byte count, file_stream

    if(count == 0){
        return 0;   
    }

    int availableBytes = stream->readBuf_size - stream->readBuf_offset; //available bytes in the hidden buffer

    if(stream->endOfFile == 1){
        count = MIN(availableBytes, count); //force it to just read this many bytes bc we know they are no more after available bytes
    }

    if(stream->writeBuf_offset!=0){ //if there is data in write buffer, flush it before doing any reading
        // printf("flush call from in read\n");
        // printf("file offset before flush %d\n", stream->fileoffset);
        myflush(stream);
    }
    
    int nextOffset = stream->readBuf_offset + count; //read buffer offset plus count requested for read
    int totalBytesRead = 0; 
    
    if(nextOffset > stream->readBuf_size){ // more data request that buffer contains 
        int bytes_to_buf; //amount of bytes read to buffer
        // printf("new buffer needed\n"); 
        int bytes_to_read = count;  // data still needing to be read
        if (stream->readBuf_offset!=0){// memcopy remainder of buffer
            // printf("copying current buffer \n");
            memcpy(dest,(void *)(stream->readBuf+stream->readBuf_offset), (unsigned int)(availableBytes));
            bytes_to_read -= availableBytes;
            totalBytesRead += availableBytes;
            stream->fileoffset += availableBytes;
        }
        
        // read MAXSIZE, memcpy nextOffset to dest
        int iterations = 0;
        while (bytes_to_read > BUFFERSIZE){ 
            // printf("in buffer loop, copying data\n");
            bytes_to_buf = read(stream->fd, (void *)(stream->readBuf), BUFFERSIZE);
            stream->readBuf_size = bytes_to_buf;

            memcpy((void *)((int *)(dest + totalBytesRead)), (void *)stream ->readBuf, (unsigned int)stream->readBuf_size);
            bytes_to_read -= stream->readBuf_size;
            stream->fileoffset += stream->readBuf_size;
            totalBytesRead += bytes_to_buf;
            // printf("total bytes read1 = %d\n", totalBytesRead);
            
            iterations ++;

            if(bytes_to_buf < BUFFERSIZE){
                // printf("EOF \n\n");
                stream->endOfFile = 1;
                break;
                //We have reached EOF
            }
            
        }  

        if(stream->endOfFile == 0){
            bytes_to_buf = read(stream->fd, (void *)(stream->readBuf+stream->readBuf_offset), BUFFERSIZE);
            stream->readBuf_size = bytes_to_buf;

            if(bytes_to_buf < BUFFERSIZE){
                stream->endOfFile = 1;
                bytes_to_read = MIN(bytes_to_buf, bytes_to_read);
                // printf("EOF1 \n");
                //We have reached EOF
            }

            memcpy((void *)((int *)(dest + totalBytesRead)), (void *)stream->readBuf, (unsigned int)bytes_to_read);
            stream->fileoffset += bytes_to_read;
            stream->readBuf_offset += bytes_to_read;
            totalBytesRead += bytes_to_read;
            // printf("total bytes read2 = %d\n", totalBytesRead);
        } 

        // printf("Looped thru buffer %d times\n", iterations);
        
    }
    else{ // No need for READ, memcpy temp to dest
        memcpy(dest, (void *)(stream->readBuf + stream->readBuf_offset), (unsigned int)count);
        stream -> readBuf_offset += count;
        stream -> fileoffset += count;
        totalBytesRead = count;
        // printf("No read sys call, memcpy from buffer to dest\n");
    }

    // printf("total bytes read3 = %d\n", totalBytesRead);
    return totalBytesRead;
}

int mywrite(int count, struct file_stream *stream, char *src)
{
    // check how much space is left in the write buffer
    //if there is space, just memcpy the data into the buffer
    //if there isn't space (2 options) (1)flush then memcpy or (2)memcpy to fill then flush then put the rest in
    //option(1)
    //flush write data to the file, then do the full memcpy

    if( (count+stream->writeBuf_offset) > BUFFERSIZE){ //buffer doesn't have enough space
        // printf("buffer is full\n");
        if( (myflush(stream)) == -1){ //or maybe do this manually? are their any differences?
            // printf("myflush returned -1");
            exit(EXIT_FAILURE);
        } //fresh buffer
        if(count > BUFFERSIZE){
            write(stream->fd, src, count);
            stream->fileoffset =+ count;
        }
        else{
            memcpy((stream->writeBuf+stream->writeBuf_offset), src, count);
            stream->writeBuf_offset += count;
        }
    }
    else{ //buffer does have enough space
        memcpy((stream->writeBuf+stream->writeBuf_offset), src, count);
        stream->writeBuf_offset += count;
        //done
    }
                        
    return count;
}

int myflush(struct file_stream *stream)
{   

    lseek(stream->fd, stream->fileoffset, SEEK_SET);

    if(stream->writeBuf_offset != 0){
        if((write(stream->fd, stream->writeBuf, stream->writeBuf_offset)) ==-1){ //write writeBuf contents to file
            perror("myflush: write");
            exit(EXIT_FAILURE);
        }
        free(stream->writeBuf); //free the writeBuf
        if( (stream->writeBuf = malloc(BUFFERSIZE)) == NULL){ //reinit write buffer
            perror("myflush: writeBuff: malloc");
            exit(EXIT_FAILURE);
        }
        stream->writeBuf_offset=0;
    }

    //is there stuff to do with readBuf?

    return 1; 
}

int myseek(struct file_stream *stream, off_t offset, int whence){

    int readBuf_spaceLeft = BUFFERSIZE - stream->readBuf_offset;
    int bytesRead;

    if(whence == SEEK_SET){ //set offset to offset

        if( (stream->fileoffset+readBuf_spaceLeft <= offset) | (offset<stream->fileoffset) ){ //if the file offset request is outside of our read buffer, then we have to use lseak
            if( (lseek(stream->fd, offset, SEEK_SET)) == -1){
                perror("myseek");
                exit(EXIT_FAILURE);
            }
            if( (bytesRead = read(stream->fd, (void *)(stream->readBuf), BUFFERSIZE)) == -1){
                perror("myseek: read");
                exit(EXIT_FAILURE);
            }
            if(bytesRead < BUFFERSIZE){
                stream->endOfFile = 1;
                printf("EOF \n");
                //We have reached EOF
            }
            stream->readBuf_size = bytesRead;
            stream->readBuf_offset = 0;
            // printf("lseak systeam call used\n");
        }
        else{
            stream->readBuf_offset += (stream->fileoffset - offset); // move the readBuf offset to match the request seek
        }

        stream->fileoffset = offset;

    }
    else if(whence == SEEK_CUR){ //set offset to current offset plus offset
        if( (offset>=readBuf_spaceLeft) | (offset<0) ){ // if the offset is greater than the space left in the readBuf, then we use lseak
            if( (lseek(stream->fd, stream->fileoffset + offset, SEEK_SET)) == -1){
                perror("myseek: lseek");
                exit(EXIT_FAILURE);
            }
            if( (bytesRead = read(stream->fd, (void *)(stream->readBuf), BUFFERSIZE)) == -1){
                perror("myseek: read");
                exit(EXIT_FAILURE);
            }
            if(bytesRead < BUFFERSIZE){
                stream->endOfFile = 1;
                printf("EOF \n");
                //We have reached EOF
            }
            stream->readBuf_size = bytesRead;
            stream->readBuf_offset = 0;
            // printf("lseak systeam call used\n");
        }
        else{ //offset is positive and within the readBuf
            stream->readBuf_offset += offset; // there is space left in the read buffer to just move readBuf offset
        }
        stream->fileoffset =+ offset;
    }


    return 1;
}

struct file_stream *myopen(char *pathname, int flags)
{
    //what more do we have to do for open?

    void *ptr = malloc(sizeof(struct file_stream));
    struct file_stream *stream = ptr;

    stream->readBuf_offset = 0;
    stream->writeBuf_offset = 0;
    stream->fileoffset = 0;
    stream->endOfFile = 0;
    stream->readBuf_size = 0;

    stream->fd = open(pathname, flags, 0666);
    if(stream->fd==-1){
        perror("myopen: open");
        exit(EXIT_FAILURE);
    }
    if( (stream->writeBuf = malloc(BUFFERSIZE)) == NULL){ //write buffer init
        perror("myopen: writeBuff: malloc");
        exit(EXIT_FAILURE);
    }

    if( (stream->readBuf = malloc(BUFFERSIZE)) == NULL){ //read buffer init
        perror("myopen: readBuff: malloc");
        exit(EXIT_FAILURE);
    }
    //add malloc error handling
    
    //add a malloc for the write buffer

    return stream;
}

int myclose(struct file_stream* stream){
    //what more?

    myflush(stream);

    free(stream->readBuf);
    free(stream->writeBuf);

    if(close(stream->fd)==-1){
        perror("myclose: close");
        exit(EXIT_FAILURE);
    }

    // printf("before freeing stream\n");
    free(stream);

    return 0;
}
