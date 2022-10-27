
#include "myio.h"

int myread(int count, struct file_stream *stream, int *dest){// file descriptor, byte count, file_stream
    if(count == 0){
        return 0;   
    }
  //  int MAXSIZE = 10000;
    int temp = stream->offset + count;
    int tempsize = 0;// number of bytes read
    stream->placeholder += stream->offset;
    
    if(temp > stream->size){ // overflow 
        temp = temp - (stream->size);//temp = remainder
        memcpy((void *)(dest +stream->offset),(void *)stream->readBuff, (unsigned int)(stream->size - stream->offset));

        if(temp > (stream->size)){// read and memcpy overflow all at once
            tempsize = read(stream->fd, stream->readBuff, temp);
            memcpy((void *)(dest + stream->offset),(void *)stream->readBuff, (unsigned int)temp);
            stream-> offset = 0;//set offset to 0

            printf("Read and memcpy overflow all at once\n");
        }
        else{ // read MAXSIZE, memcpy temp to dest
            tempsize = read(stream->fd, stream->readBuff, stream->size);
            memcpy((void *)(dest + stream -> offset),(void *)stream->readBuff, (unsigned int)temp);
            stream-> offset += temp;//add 

            printf("Read MAXSIZE, memcpy temp to dest\n");
        }
    }
    else if(stream->offset ==0){ // New read
        tempsize = read(stream->fd, stream->readBuff, stream->size);
        memcpy((void *)(dest+ stream ->offset), (void *)stream ->readBuff, (unsigned long)count);
        stream->offset += count;

        printf("New read\n");
    }
    else{ // No READ, memcpy temp to dest
        memcpy((void *)(dest+ stream ->offset), (void *)stream ->readBuff, (unsigned long)count);
        stream -> offset += count;

        printf("No READ, memcpy temp to dest\n");
    }
    printf("Count is %d\n", count);
    printf("Tempsize is %d\n", tempsize);
    printf("Offset is %d\n", stream->offset);
    printf("Placeholder is %p\n\n", (void *)(dest+stream->offset));

    return tempsize;
}
// does not take into account malloc


int mywrite(int count, struct file_stream *stream, int *dest){

   // int temp = stream->offset + count;

    return 1;

}

















/*

struct file_stream myopen(char *pathname, int flags){
    //what more do we have to do for open?

    struct file_stream stream;
    stream.offset = 0;
    stream.fd = open(pathname, flags);




    return stream;

}*/
/*
int myclose(int fd){
    //what more?

    if(close(fd)==-1){
        perror("Error");
        exit(EXIT_FAILURE);
    }
    

}*/

