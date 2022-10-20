

/*
int buffer[][];
int maxsize; 
int *offset = buffer;    
*/

#include "myio.h"

int MAXSIZE = 10000; 


int myread(int count, struct file_stream *stream, void *dest){// file descriptor, byte count, file_stream
    if(count == 0){
        return 0;   
    }
    int tempsize;/*
    if(stream.offset + count > stream.size){// Offset + amt requested > max size
        tempsize = read(stream.fd, stream.DATA, count);
        
       
        printf("First Path\n");

    }else{  // ret
        tempsize = read(stream.fd, stream.DATA, count);
        
        printf("Second path\n");


    }*/
   
/*
    if(stream.offset == 0){// new Stream struct
        if(count < MAXSIZE){// amount requested is less than max buffer size
            
        }else{// return count amount of bytes requested
            
        }
    }else{
        if(stream.offset + count > stream.size){//if overflow, count + stream's offset is greater than buffer size
            //int bytes_read;
            
            printf("3rd PATH\n");

        }else{
            memcpy(dest, stream.DATA, count);

            printf("fourth path\n");
        }
    }
*/



    tempsize = read(stream->fd, stream->DATA, count);
    memcpy(dest, (void *)stream ->DATA, (unsigned long)count);
    printf("pre count offset:%d\n", stream->offset);
    stream ->offset += count;
    
    /*
    if(stream.size == -1){
        perror("Error");
        exit(EXIT_FAILURE);
    }*/
    

    printf("Size is %d\n", tempsize);
    //    printf("Offset is %p\n", offset);
    printf("Offset is %d\n", stream->offset);




    return count;

    
}


















/*

int myopen(char *pathname, int flags){
    //what more do we have to do for open?

    int fd;
    fd = open(pathname, flags);
    if(fd==-1){
        perror("Error");
        exit(EXIT_FAILURE);
    }

    return fd;
}

int myclose(int fd){
    //what more?

    if(close(fd)==-1){
        perror("Error");
        exit(EXIT_FAILURE);
    }
    

}*/

