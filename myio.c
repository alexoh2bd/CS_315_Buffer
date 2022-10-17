

#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include "myio.h"
#include <errno.h>
#include <stdlib.h>



/*
int buffer[][];
int maxsize; 
int *offset = buffer;    
*/



int MAXSIZE = 10000; 


int myread(int count, struct file_stream stream, void *dest){// file descriptor, byte count, file_stream
    if(count == 0){
        return 0;   
    }
    

    if(stream.offset == NULL||stream.offset == 0){// new Stream struct
        if(count < MAXSIZE){// amount requested is less than max buffer size
            stream.readData = malloc(MAXSIZE);
            stream.size = read(stream.fd, stream.readData, MAXSIZE);
            memcpy(dest,stream.readData, count);

            stream.offset += count;

        }else{// return count amount of bytes requested
            stream.readData = malloc(count);
            stream.size = read(stream.fd, stream.readData, count);
            stream.offset += count;
            memcpy(dest,stream.readData, count);


        }
    }else{
        if(stream.offset + count > stream.size){//if overflow, count + stream's offset is greater than buffer size
            int bytes_read;
            


        }else{
            memcpy(dest, stream.readData, count);


        }
    }













    if(stream.size == -1){
        perror("Error");
        exit(EXIT_FAILURE);
    }
    
    



    printf("Size is %d\n", stream.size);
    //    printf("Offset is %p\n", offset);
    printf("Offset is %d\n", stream.offset);



    return count;

    
}




















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
    

}

