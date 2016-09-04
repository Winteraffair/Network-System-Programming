CC = gcc
INC = -I /usr/include
LIB = -L /usr/lib
test: shell.o run_command.o builtin.o parse.o is_background.o
	gcc  shell.o run_command.o builtin.o parse.o is_background.o -o test
shell.o: shell.c
	gcc -c shell.c 
parse.o: parse.c
	gcc -c parse.c 
builtin.o: builtin.c
	gcc -c builtin.c
run.command.o: run_command.c
	gcc -c run_command.c 
is_background.o: is_background.c
	gcc -c is_background.c 

clean:
	rm -rf main.o shell.o builtin.o run_command.o is_background.o parse.o
