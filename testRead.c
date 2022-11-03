#include "myio.h"


int main(int argc, char **argv){
    int destsize = 200000;
    file_stream john;
    char *dest = malloc(destsize);
 /* thrones.offset =0;
    thrones.fd = open("thrones.pdf", O_RDONLY | O_CREAT);
    thrones.size = MAXSIZE;
    thrones.readBuf = malloc(MAXSIZE);
*/
    john =myopen("john.txt", O_RDONLY );
    printf("Myread A\n");
    myread(10000, &john, dest);
    
    printf("Myread B\n");
    myread(3000, &john, dest);


    printf("Myread C\n");
    myread(20000, &john, dest);

    //printf("destination: %p\n", dest);
    printf("Myread D\n");
    myread(40000, &john, dest);


/*
    for(int i = 0; i< destsize; i++){
        printf("%c", dest[i]);
    }*/

    printf("Myread E\n");
    myread(1300, &john, dest);
    myread(30000, &john, dest);
    myread(300, &john, dest);
    myread(3300, &john, dest);
    myread(3030, &john, dest);

    free(dest);
    printf("Freed memory\n");
    }