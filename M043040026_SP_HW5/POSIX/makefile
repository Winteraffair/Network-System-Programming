all : producer consumer

producer:producer_posix.o
	gcc -o producer producer_posix.o
consumer:consumer_posix.o
	gcc -o consumer consumer_posix.o

producer.o:producer_posix.c
	gcc -c producer_posix.c

consumer.o:consumer_posix.c
	gcc -c consumer_posix.c

clean:
	rm -rf *~ producer consumer producer_posix.o consumer_posix.o
