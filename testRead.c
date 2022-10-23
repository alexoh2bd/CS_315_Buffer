#include "myio.h"


int main(int argc, char **argv){
    MAXSIZE = 100000;
    file_stream thrones;
    int *dest = malloc(MAXSIZE);
    thrones.offset =0;
    thrones.fd = open("thrones.pdf", O_RDONLY | O_CREAT);
    thrones.size = MAXSIZE;
    thrones.DATA = malloc(MAXSIZE);

    myread(500, &thrones, dest);
    //printf("%d bytes read\n", bytes_read);

    //printf("destination: %p\n", dest);
    myread(300000, &thrones, dest);
    myread(130000, &thrones, dest);





}
