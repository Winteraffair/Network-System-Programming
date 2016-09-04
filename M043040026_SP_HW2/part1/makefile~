hostinfo: hostinfo.o
	gcc hostinfo.o -o hostinfo
printdir: printdir.o
	gcc printdir.o -o printdir
mycat: mycat.o
	gcc mycat.o -o mycat
mydate: mydate.o
	gcc mydate.o -o mydate
pipe_ls: hostinfo.o
	gcc pipe_ls.o -o pipe_ls

hostinfo.o: hostinfo.c
	gcc -c hostinfo.c
printdir.o: printdir.c
	gcc -c printdir.c
mycat.o: mycat.c
	gcc -c mycat.c
mydate.o: mydate.c
	gcc -c mydate.c
pipe_ls.o: pipe_ls.o
	gcc -c pipe_ls.c
clean:
	rm -rf printdir mycat mydate pipe_ls hostinfo printdir.o mycat.o mydate.o pipe_ls.o hostinfo.o
