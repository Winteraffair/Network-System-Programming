all : producer consumer

producer:producer_systemv.o
	gcc -o producer producer_systemv.o
consumer:consumer_systemv.o
	gcc -o consumer consumer_systemv.o

producer.o:producer_systemv.c
	gcc -c producer_systemv.c

consumer.o:consumer_systemv.c
	gcc -c consumer_systemv.c

clean:
	rm -rf *~ producer consumer producer_systemv.o consumer_systemv.o testid
