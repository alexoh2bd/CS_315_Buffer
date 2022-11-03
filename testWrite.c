#include "myio.h"

int main(int argc, char **argv){
    printf("write file\n"); 

    char *testdata = malloc(sizeof(char)*12);
    testdata = "Hello World, hello my name is aiden this is the long test deez nuts yo mama";

    char *testdata2 = malloc(sizeof(char)*12);
    testdata2 = "Heddo World";


    struct file_stream testfile = myopen("testfile.txt", O_RDWR);
    printf("contents in malloc: %s\n", testdata);

    printf("Write buffer offset = %d\n", testfile.writeBuf_offset);

    mywrite(11, &testfile, testdata2);
    mywrite(11, &testfile, testdata2);

    printf("sangjay gupta test\n");
    mywrite(60, &testfile, testdata);

    printf("last write\n");
    mywrite(11, &testfile, testdata2);

    printf("contents of writeBuf: %s\n", testfile.writeBuf);
    printf("Write buffer offset = %d\n", testfile.writeBuf_offset);

    myflush(&testfile);

    myclose(&testfile);

    char *testing = malloc(100);
    memcpy(testing, testdata, 11);
    printf("%s\n", testing);
    memcpy((testing+11), testdata2, 11);
    printf("%s\n", testing);


}