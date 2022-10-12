

#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include "myio.h"



int buffer[10000];
int offset;



int myread(int fd, int count){
    if(count == 0){
        return 0;
    }/*else if (count >sizeof(buffer))
    {
        buffer.resize(count);
    }*/


    
    offset = read(fd, buffer, sizeof(buffer));
//  printf("Buffer contains : %d\n",buffer[0]);
    

    return offset;

    
}

int myopen(char *pathname, int flags, __mode_t mode){
    //what more do we have to do for open?

    int fd;
    fd = open(pathname, flags, mode);


    return fd;
}

