all: udp_client udp_server

udp_client: main.c lookup9.c
	gcc -o udp_client main.c lookup9.c
udp_server: udp_server.c lookup5.c
	gcc -o udp_server udp_server.c lookup5.c

clean : 
	rm -rf *~ *.o udp_client udp_server 

