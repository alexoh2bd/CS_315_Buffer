
#include "myio.h"

int myread(int count, struct file_stream *stream, int *dest){// file descriptor, byte count, file_stream
    if(count == 0){
        return 0;   
    }
    int temp = stream->offset + count;
    int tempsize = 0;
    stream->placeholder += stream->offset;
    
    if(temp > MAXSIZE){ // overflow 
        temp = temp - MAXSIZE;
        memcpy((void *)(dest +stream->offset),(void *)stream->DATA, (unsigned int)(MAXSIZE - stream->offset));

        if(temp > MAXSIZE){// read and memcpy overflow all at once
            tempsize = read(stream->fd, stream->DATA, temp);
            memcpy((void *)(dest + stream->offset),(void *)stream->DATA, (unsigned int)temp);
            stream-> offset = 0;

            printf("Read and memcpy overflow all at once\n");
        }
        else{ // read MAXSIZE, memcpy temp to dest
            tempsize = read(stream->fd, stream->DATA, MAXSIZE);
            memcpy((void *)(dest + stream -> offset),(void *)stream->DATA, (unsigned int)temp);
            stream-> offset += temp;

            printf("Read MAXSIZE, memcpy temp to dest\n");
        }
    }
    else if(stream->offset ==0){ // New read
        tempsize = read(stream->fd, stream->DATA, MAXSIZE);
        memcpy((void *)(dest+ stream ->offset), (void *)stream ->DATA, (unsigned long)count);
        stream->offset += count;

        printf("New read\n");
    }
    else{ // No READ, memcpy temp to dest
        memcpy((void *)(dest+ stream ->offset), (void *)stream ->DATA, (unsigned long)count);
        stream -> offset += count;

        printf("No READ, memcpy temp to dest\n");
    }

    printf("Tempsize is %d\n", tempsize);
    printf("Offset is %d\n", stream->offset);
    printf("Placeholder is %p\n\n", (void *)(dest+stream->offset));

    return count;
}
// does not take into account malloc


















/*

int myopen(char *pathname, int flags){
    //what more do we have to do for open?

    int fd;
    fd = open(pathname, flags);
    if(fd==-1){
        perror("Error");
        exit(EXIT_FAILURE);
    }

    return fd;
}

int myclose(int fd){
    //what more?

    if(close(fd)==-1){
        perror("Error");
        exit(EXIT_FAILURE);
    }
    

}*/

