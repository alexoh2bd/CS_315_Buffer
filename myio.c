

#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include "myio.h"
#include <errno.h>
#include <stdlib.h>


struct file_info{
    int fd;
    int *readData;
    int *writeData;
    int size;
};
/*
int buffer[][];
int maxsize; 
int *offset = buffer;    
*/
int maxsize = 1000; 
int offset= 0;


int myread(int fileDescriptor, int count){
    if(count == 0){
        return 0;   
    }

  /*  offset = read(fd, buffer, sizeof(buffer));
    
    //  printf("Buffer contains : %d\n",buffer[0]);

    int size = read(fd, offset, sizeof(buffer));


    //  printf("Buffer contains : %d\n",buffer[0]);

    offset += size/4;
*/



    struct file_info fs;//fs = filestack
    fs.fd = fileDescriptor;
    fs.readData = malloc(maxsize);
    fs.size = read(fs.fd, fs.readData, count);


    if(fs.size == -1){
        perror("Error");
        exit(EXIT_FAILURE);
    }
    offset+= fs.size;




    printf("Size is %d\n", fs.size);
    //    printf("Offset is %p\n", offset);
    printf("Offset is %d\n", offset);



    return offset;

    
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

