Rtest: myio.o testRead.o
	gcc -o Rtest myio.o testRead.o
	


Wtest:myio.o testWrite.o
	gcc -o Wtest myio.o testWrite.o


myio.o: myio.c
	gcc -Wall -pedantic -c -o myio.o myio.c


testRead.o: testRead.c
	gcc -Wall -pedantic -c -o testRead.o testRead.c
	

testWrite.o: testWrite.c
	gcc -Wall -pedantic -c -o testWrite.o testWrite.c



.Phony:clean
clean:
	rm -f main Rtest Wtest myio.o testRead.o testWrite.o 