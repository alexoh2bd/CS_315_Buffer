#include "myio.h"

#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv){
    int fd = open("myio.c", 100);
    int try =myread(fd, 10);
    printf("Offset is : %d\n", try);
  

    
}