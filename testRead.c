#include "myio.h"


int main(int argc, char **argv){
    int destsize = 200000;
    file_stream john;
    file_stream numbers;
    char *dest = malloc(destsize);
 /* thrones.offset =0;
    thrones.fd = open("thrones.pdf", O_RDONLY | O_CREAT);
    thrones.size = MAXSIZE;
    thrones.readBuf = malloc(MAXSIZE);
*/
    john =myopen("john.txt", O_RDONLY );
    numbers = myopen("numbers.txt", O_RDWR);
    printf("Myread A\n");
    // myread(10000, &john, dest);
    
    printf("Myread B\n");
    myread(20, &numbers, dest);

    myseek(&numbers, 20, SEEK_CUR);


    myread(20, &numbers, dest);

    // printf("Myread C\n");
    // myread(20000, &john, dest);

    // printf("Myread D\n");
    // myread(40000, &john, dest);

    // printf("Myread E\n");
    // myread(1300, &john, dest);
    // myread(30000, &john, dest);
    // myread(300, &john, dest);
    // myread(3300, &john, dest);
    // myread(3030, &john, dest);

    
    for(int i = 0; i< destsize; i++){
        printf("%c", dest[i]);
    }

    
    myclose(&john);
    myclose(&numbers);
    printf("\nFreed Memory!\n");
    }