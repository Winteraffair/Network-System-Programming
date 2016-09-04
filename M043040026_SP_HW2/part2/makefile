CC = gcc
INC = -I /usr/include
LIB = -L /usr/lib
homework2: shell.o  builtin.o parse.o is_background.o run_command.o redirect_in.o redirect_out.o pipe_present.o pipe_command.o
	gcc  shell.o builtin.o parse.o is_background.o  run_command.o redirect_in.o redirect_out.o pipe_present.o pipe_command.o -o homework2
shell.o: shell.c
	gcc -c shell.c 
parse.o: parse.c
	gcc -c parse.c 
builtin.o: builtin.c
	gcc -c builtin.c
is_background.o: is_background.c
	gcc -c is_background.c 
run_command.o: run_command.c
	gcc -c run_command.c
redirect_in.o: redirect_in.c
	gcc -c redirect_in.c
redirect_out.o: redirect_out.c
	gcc -c redirect_out.c
pipe_present.o: pipe_present.c
	gcc -c pipe_present.c
pipe_command.o: pipe_command.c
	gcc -c pipe_command.c

clean:
	rm -rf homework2 shell.o builtin.o run_command.o is_background.o parse.o redirect_in.o redirect_out.o pipe_present.o pipe_command.o
