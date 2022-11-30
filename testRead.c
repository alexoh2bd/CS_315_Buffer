#include "myio.h"

int main(int argc, char **argv){

    int destsize = 200000;
    // int destsize2 = 10000;

    file_stream *john;
    // file_stream numbers;

    printf("malloc\n");
    char *dest = malloc(destsize);
    // char *dest2 = malloc(destsize2);

    // FILE *john;
    // printf("before john \n");
    // john = fopen("john.txt", "r");
    // printf("open john \n");

    // fread(dest, 1, 1000000, john);
    // printf("read john \n");

    // fread(dest2, 1, 10, john);
    // printf("read john2 \n");

//              testing myread and myseek

    printf("opening\n");
    john = myopen("john.txt", O_RDWR );
//     printf("file offset = %d\n", john.fileoffset);

// //               testing reading the entire file
//     // myread(150000, john, dest);

//     // numbers = myopen("numbers.txt", O_RDWR);
//     printf("Myread A\n");
//     myread(800, john, dest);
//     printf("file offset = %d\n", john.fileoffset);

// //           testing SEEK_SET and SEEK_CUR
//     myseek(john, 0, SEEK_SET);
//     // myseek(john, -800, SEEK_CUR);

//     printf("Read B\n");
//     myread(1000, john, dest+800);
//     printf("file offset = %d\n", john.fileoffset);

    // myseek(numbers, 20, SEEK_CUR);

    // myread(20, numbers, dest);

//          prints all contents read
    // printf("\nprinting contents of dest: \n");
    // for(int i = 0; i< destsize; i++){
    //     printf("%c", dest[i]);
    // }
    // printf("\n\n");

    // printf("\nprinting contents of dest2: \n");
    // for(int i = 0; i< destsize2; i++){
    //     printf("%c", dest2[i]);
    // }
    // printf("\n\n");

    //              testing amount returned

    printf("reading\n");
    int read1 = myread(100, john, dest);
    printf("read %d characters\n", read1);

    myclose(john);
    // myclose(numbers);
    // printf("\nFreed Memory!\n");
    }