convert: convert.o
	gcc convert.o -o convert
main: main.o lookup1.o 
	gcc main.o lookup1.o -o main

convert.o: convert.c
	gcc -c convert.c
main.o: main.c 
	gcc -c main.c
lookup1.o: lookup1.c
	gcc -c lookup1.c

clean:
	rm -rf convert main convert.o main.o lookup1.o 
