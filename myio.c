

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



int myread(struct file_stream stream, int count){
    if(count == 0){
        return 0;   
    }
   // if(stream.fd == ){

    stream.readData = malloc(maxsize);
    stream.size = read(stream.fd, stream.readData, count);
    

    if(stream.size == -1){
        perror("Error");
        exit(EXIT_FAILURE);
    }
    stream.offset+= count;
    

 //   if

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

