all : msgq_server msgq_client

msgq_server:msgq_server.o lookup2.o 
	gcc msgq_server.o lookup2.o -o msgq_server
msgq_client:lookup4.o main.o 
	gcc lookup4.o main.o -o msgq_client

msgq_server.o:msgq_server.c
	gcc -c msgq_server.c

lookup2.o:lookup2.c
	gcc -c lookup2.c
lookup4.o:lookup4.c
	gcc -c lookup4.c
main.o:main.c
	gcc -c main.c

clean :
	rm -rf msgq_server msgq_client msgq_server.o lookup2.o lookup4.o main.o




