#include "myio.h"

int main(int argc, char **argv){

    int destSize = 10000;
    char *dest = malloc(destSize);

    char *testdata2 = malloc(sizeof(char)*12);
    testdata2 = "Heddo";

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


    file_stream testfile = myopen("testfile.txt", O_RDWR);

    myread(10, &testfile, dest);
    printf("\nprinting contents of dest: \n");
    for(int i = 0; i< destSize; i++){
        printf("%c", dest[i]);
    }
    printf("\n\n");

    printf("mywrite\n");
    mywrite(5, &testfile, testdata2);
    printf("fileoffset: %d\n", testfile.fileoffset);
    // printf("flush\n");
    // myflush(&testfile);

    printf("fileoffset: %d\n", testfile.fileoffset);
    printf("readbuf offset = %d\n", testfile.readBuf_offset);
    
    myread(10, &testfile, dest+10);

    printf("\nprinting contents of dest: \n");
    for(int i = 0; i< destSize; i++){
        printf("%c", dest[i]);
    }
    printf("\n\n");

//use cat testfile.txt to observe write function

    // printf("contents of writeBuf before flush: %s\n", testfile.writeBuf);
    // printf("Write buffer offset before flush = %d\n", testfile.writeBuf_offset);

    // myflush(&testfile);

    myclose(&testfile);

}