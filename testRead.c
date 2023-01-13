#include "myio.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv){

    //          open and malloc 

    int destsize = 100;
    // int destsize2 = 10000;
    char *dest = malloc(destsize);

    file_stream *matt;
    matt = myopen("matthew.txt", O_RDWR );
    // file_stream *numbers;
    // numbers = myopen("numbers.txt", O_RDWR);
    // file_stream *testfile;
    // testfile = myopen("testfile.txt", O_RDWR | O_CREAT);

    // FILE *johnReal;
    // johnReal = fopen("john.txt", "r");

    // FILE *numbers2;
    // numbers2 = fopen("numbers2.txt", "r+");

    int readAmt1 = myread(10, matt, dest);
    printf("amt read: %d\n", readAmt1);

    for(int i = 0; i< destsize; i++){
        printf("%c", dest[i]);
    }


    int writeAmt1 = mywrite(10, matt, dest);
    printf("\namt written: %d\n", writeAmt1);



    for(int i = 0; i< 100; i++){
        printf("%c", matt->writeBuf[i]);
    }


    int readAmt2 = myread(20, matt, dest);
    printf("\namt read2: %d\n", readAmt2);

    for(int i = 0; i< 100; i++){
        printf("%c", dest[i]);
    }

    int writeAmt2 = mywrite(20, matt, dest);
    printf("\namt written2: %d\n", writeAmt2);

    for(int i = 0; i< 100; i++){
        printf("%c", matt->writeBuf[i]);
    }

    printf("\n");






    // char *dest2 = malloc(destsize2);

    // FILE *johnReal;
    // // printf("before john \n");
    // johnReal = fopen("john.txt", "r");
    // printf("open john \n");

    // int readAmt = fread(dest, 1, 2000, johnReal);
    // printf("Amount read my fread: %d\n", readAmt);
    // printf("\nprinting contents of dest: \n");
    // for(int i = 0; i< destsize; i++){
    //     printf("%c", dest[i]);
    //}
    // printf("\n\n");
    // printf("read john \n");

    // fread(dest2, 1, 10, john);
    // printf("read john2 \n");


// //                           testing reading the entire file
    // readAmt = myread(2000, john, dest);
    // printf("Amount read my myread: %d\n", readAmt);

//     // numbers = myopen("numbers.txt", O_RDWR);
//     printf("Myread A\n");
//     myread(800, john, dest);
//     printf("file offset = %d\n", john.fileoffset);

// //                   testing SEEK_SET and SEEK_CUR
//     myseek(john, 0, SEEK_SET);
//     // myseek(john, -800, SEEK_CUR);

//     printf("Read B\n");
//     myread(1000, john, dest+800);
//     printf("file offset = %d\n", john.fileoffset);

    // myseek(numbers, 20, SEEK_CUR);

    // myread(20, numbers, dest);

        //  prints all contents read
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

    // printf("reading\n");
    // int read1 = myread(100, numbers, dest);
    // printf("read %d characters\n", read1);

    // int read2 = myread(75, numbers, dest);
    // printf("read %d characters\n", read2);



    //          testing large reads
    
    // int readAmt;
    // readAmt = myread(5000, john, dest);
    // printf("Amount read myread: %d\n\n", readAmt);

    // readAmt = myread(5000, john, dest);
    // printf("Amount read myread: %d\n\n", readAmt);

    // readAmt = myread(5000, john, dest);
    // printf("Amount read myread: %d\n\n", readAmt);

    // printf("\nprinting contents of dest my read: \n");
    // for(int i = 0; i< destsize; i++){
    //     printf("%c", dest[i]);
    // }
    // printf("\n\n");


    // readAmt = fread(dest, 1, 5000, johnReal);
    // readAmt = fread(dest, 1, 5000, johnReal);
    // readAmt = fread(dest, 1, 5000, johnReal);

    // printf("\nprinting contents of dest fread: \n");
    // for(int i = 0; i< destsize; i++){
    //     printf("%c", dest[i]);
    // }
    // printf("\n\n");

    //                  testing reads and writes intermingled

    // char *testdata2 = malloc(100);
    // testdata2 = "";

    // char *testdata3 = malloc(100);
    // testdata3 = "HeddoHeddoHeddoHeddoHeddoHeddoHeddoHeddoHeddoHeddoHeddoHeddoHeddoHeddoHeddoHeddoHeddoHeddoHeddoHeddo";

    // printf("reading\n");
    // int read1 = myread(10, john, dest);
    // printf("read %d characters\n", read1);
    // for(int i = 0; i< destsize; i++){
    //     printf("%c", dest[i]);
    // }
    // printf("file offset = %d\n\n", john->fileoffset);

    // read1 = myread(10, john, dest);
    // printf("read %d characters\n", read1);
    // for(int i = 0; i< destsize; i++){
    //     printf("%c", dest[i]);
    // }
    // printf("file offset = %d\n\n", john->fileoffset);

    // int writeAmt2 = mywrite(5, john, testdata2);
    // printf("amt written2: %d\n", writeAmt2);
    // printf("%\n", testdata2);
    // printf("file offset = %d\n\n", john->fileoffset);

    // read1 = myread(10, john, dest);
    // printf("read %d characters\n", read1);
    // for(int i = 0; i< destsize; i++){
    //     printf("%c", dest[i]);
    // }
    // printf("file offset = %d\n\n", john->fileoffset);

    // writeAmt2 = mywrite(5, john, testdata2);
    // printf("amt written2: %d\n", writeAmt2);
    // printf(testdata2);
    // printf("file offset = %d\n\n", john->fileoffset);

    // printf("\nprinting contents of dest my read: \n");
    // for(int i = 0; i< destsize; i++){
    //     printf("%c", dest[i]);
    // }
    // printf("\n\n");

    // read1 = fread(dest, 1, 10, numbers2);
    // printf("read %d characters\n", read1);
    // read1 = fread(dest, 1, 10, numbers2);
    // printf("read %d characters\n", read1);
    // writeAmt2 = fwrite(testdata2, 1, 10, numbers2);
    // printf("amt written2: %d\n", writeAmt2);
    // read1 = fread(dest, 1, 10, numbers2);
    // printf("read %d characters\n", read1);

    // printf("\nprinting contents of dest my read: \n");
    // for(int i = 0; i< destsize; i++){
    //     printf("%c", dest[i]);
    // }
    // printf("\n\n");


    //myclose(john);
   // myclose(numbers);

}