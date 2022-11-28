CFLAGS = -g -Wall -pedantic

Rtest:myio.o testRead.o
	gcc -o Rtest myio.o testRead.o
	
Wtest:myio.o testWrite.o
	gcc -o Wtest myio.o testWrite.o

%.o:%.c
	gcc $(CFLAGS) -c -o $@ $<

.PHONY:clean
clean:
	rm -f main Rtest Wtest myio.o testRead.o testWrite.o 

