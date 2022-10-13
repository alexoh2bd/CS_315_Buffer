#include "myio.h"

#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv){
    int fd1 = open("myio.c", 100);
    int try1 =myread(fd1, 10);
    int fd2 = open("myio.h", 100);
    int try2 = myread(fd2, 100);




    printf("Offset is : %d\n", try1+try2);
  

    
}