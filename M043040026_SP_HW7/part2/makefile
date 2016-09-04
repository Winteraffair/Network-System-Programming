all: isock_client isock_server

isock_client: main.c lookup8.c
	gcc -o isock_client main.c lookup8.c
isock_server: isock_server.c lookup5.c
	gcc -o isock_server isock_server.c lookup5.c

clean : 
	rm -rf *~ *.o isock_client isock_server

