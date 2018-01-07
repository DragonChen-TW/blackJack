all:server_client
server_client:server.c client.c card.o
	gcc server.c card.o -o server.out
	gcc client.c card.o -o client.out
	rm *.o
card.o:card.c card.h
	gcc -c card.c
printout.o:printout.c printout.h
	gcc -c printout.c
clean:
	rm server.out client.out
