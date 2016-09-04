all: usock_client usock_server

usock_client: main.c lookup7.c
	gcc -o usock_client main.c lookup7.c
usock_server: usock_server.c lookup5.c
	gcc -o usock_server usock_server.c lookup5.c

clean : 
	rm -rf *~ *.o usock_client usock_server TUNNEL

