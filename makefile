main: myio.o testRead.o
	gcc -o main myio.o testRead.o

myio.o: myio.c
	gcc -Wall -pedantic -c -o myio.o myio.c


testRead.o: testRead.c
	gcc -Wall -pedantic -c -o testRead.o testRead.c
	




.Phony:clean
clean:
	rm -f main myio.o testRead.o