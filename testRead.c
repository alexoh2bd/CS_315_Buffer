#include "myio.h"


int main(int argc, char **argv){
    int MAXSIZE = 1000000;
    file_stream thrones;
    int *dest = malloc(MAXSIZE);
    thrones.offset =0;
    thrones.fd = open("thrones.pdf", O_RDONLY | O_CREAT);
    thrones.size = MAXSIZE;
    thrones.readBuff = malloc(MAXSIZE);

    myread(500, &thrones, dest);
    //printf("%d bytes read\n", bytes_read);
    myread(300, &thrones, dest);
    myread(2000, &thrones, dest);
    myread(3000, &thrones, dest);
    myread(5000, &thrones, dest);
/*
    //printf("destination: %p\n", dest);
    myread(30000, &thrones, dest);
    myread(13000, &thrones, dest);
    myread(20000, &thrones, dest);
    myread(3300, &thrones, dest);
    myread(33300, &thrones, dest);
    myread(30330, &thrones, dest);
*/



    free(dest);
    printf("Freed memory\n");
    }

