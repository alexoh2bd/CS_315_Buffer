#include "myio.h"


int main(int argc, char **argv){
    int MAXSIZE = 100000;
    file_stream john;
    int *dest = malloc(MAXSIZE);
 /* thrones.offset =0;
    thrones.fd = open("thrones.pdf", O_RDONLY | O_CREAT);
    thrones.size = MAXSIZE;
    thrones.readBuff = malloc(MAXSIZE);
*/
    john =myopen("john.txt", O_RDONLY );

    myread(500, &john, dest);
    //printf("%d bytes read\n", bytes_read);
    myread(300, &john, dest);
    myread(2000, &john, dest);
    myread(3000, &john, dest);
    myread(5000, &john, dest);
/*
    int x;
    while(dest>>x){
        printf("%d", x);
    }*/



    //printf("destination: %p\n", dest);
/*    myread(3000, &john, dest);
    myread(1300, &john, dest);
    myread(2000, &john, dest);
    myread(300, &john, dest);
    myread(3300, &john, dest);
    myread(3030, &john, dest);

*/


    free(dest);
    printf("Freed memory\n");
    }

