all : fifo_server fifo_client

fifo_server:fifo_server.o lookup2.o 
	gcc fifo_server.o lookup2.o -o fifo_server
fifo_client:lookup3.o main.o 
	gcc lookup3.o main.o -o fifo_client

fifo_server.o:fifo_server.c
	gcc -c fifo_server.c

lookup2.o:lookup2.c
	gcc -c lookup2.c
lookup3.o:lookup3.c
	gcc -c lookup3.c
main.o:main.c
	gcc -c main.c

clean :
	rm -rf fifo_server fifo_client fifo_server.o lookup2.o lookup3.o main.o




