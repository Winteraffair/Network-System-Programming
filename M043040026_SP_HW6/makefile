all : shm_server shm_client

shm_server: shm_server.c lookup5.c
	gcc -o shm_server shm_server.c lookup5.c
shm_client: main.c lookup6.c
	gcc -o shm_client main.c lookup6.c

clean :
	rm -rf *~ shm_server shm_client
