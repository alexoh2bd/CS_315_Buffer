#include "myio.h"

int main(int argc, char **argv){

    // int destSize = 10000;
    // char *dest = malloc(destSize);

    char *testdata2 = malloc(5);
    testdata2 = "Heddo";

    char *testdata3 = malloc(100);
    testdata3 = "HeddoHeddoHeddoHeddoHeddoHeddoHeddoHeddoHeddoHeddoHeddoHeddoHeddoHeddoHeddoHeddoHeddoHeddoHeddoHeddo";

// testing f commands functions
    // FILE* testfile2 = fopen("testfile.txt", "r+");

    // fread(dest, 1, 10, testfile2);
    // printf("\nprinting contents of dest: \n");
    // for(int i = 0; i< destSize; i++){
    //     printf("%c", dest[i]);
    // }
    // printf("\n\n");

    // fwrite(testdata2, 1, 5, testfile2);

    // fread(dest, 1, 10, testfile2);
    // printf("\nprinting contents of dest: \n");
    // for(int i = 0; i< destSize; i++){
    //     printf("%c", dest[i]);
    // }
    // printf("\n\n");


    // file_stream testfile = myopen("testfile.txt", O_RDWR);

    // myread(10, &testfile, dest);
    // printf("\nprinting contents of dest: \n");
    // for(int i = 0; i< destSize; i++){
    //     printf("%c", dest[i]);
    // }
    // printf("\n\n");

    // printf("mywrite\n");
    // mywrite(5, &testfile, testdata2);
    // printf("fileoffset: %d\n", testfile.fileoffset);
    // // printf("flush\n");
    // // myflush(&testfile);

    // printf("fileoffset: %d\n", testfile.fileoffset);
    // printf("readbuf offset = %d\n", testfile.readBuf_offset);
    
    // myread(10, &testfile, dest+10);

    // printf("\nprinting contents of dest: \n");
    // for(int i = 0; i< destSize; i++){
    //     printf("%c", dest[i]);
    // }
    // printf("\n\n");

//use cat testfile.txt to observe write function

    // printf("contents of writeBuf before flush: %s\n", testfile.writeBuf);
    // printf("Write buffer offset before flush = %d\n", testfile.writeBuf_offset);

    // myflush(&testfile);

    //              testing amt written return value

    file_stream *testfile = myopen("testfile.txt", O_RDWR);

    int writeAmt = mywrite(5, testfile, testdata2);
    printf("amt written: %d\n", writeAmt);

    int writeAmt2 = mywrite(100, testfile, testdata3);
    printf("amt written2: %d\n", writeAmt2);

    // printf("before close\n");
    myclose(testfile);

}