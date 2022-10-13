

#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include "myio.h"
#include <errno.h>
#include <stdlib.h>


struct file_stream{
    int fd;
    int *readData;
    int *writeData;
    int size;
    int offset;
};
/*
int buffer[][];
int maxsize; 
int *offset = buffer;    
*/
struct file_stream filearr [];
int maxsize = 1000; 



int myread(int fileDescriptor, int count, struct file_stream stream){
    if(count == 0){
        return 0;   
    }


    struct file_stream fs;//fs = filestack
    fs.fd = fileDescriptor;
    fs.readData = malloc(maxsize);
    fs.size = read(fs.fd, fs.readData, count);
    

    if(fs.size == -1){
        perror("Error");
        exit(EXIT_FAILURE);
    }
    fs.offset+= count;
    



    printf("Size is %d\n", fs.size);
    //    printf("Offset is %p\n", offset);
    printf("Offset is %d\n", fs.offset);



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

