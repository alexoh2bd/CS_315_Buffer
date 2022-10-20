#include "myio.h"


int main(int argc, char **argv){
    int MAXSIZE = 10000;
    file_stream thrones;
    void  *dest = malloc(30000);
    thrones.offset =0;
    thrones.fd = open("thrones.pdf", O_RDONLY | O_CREAT);
    thrones.size = MAXSIZE;
    thrones.DATA = malloc(MAXSIZE);

    int bytes_read =myread(500, &thrones, dest);
    printf("%d bytes read\n", bytes_read);

    printf("destination: %p\n", dest);
    myread(320, &thrones, dest);
    myread(10000, &thrones, dest);




}
