all:server_client
server_client:server.c client.c card.o game.o printout.o
	gcc server.c card.o game.o -o server.out
	gcc client.c card.o game.o printout.o -lGL -lGLU -lglut -o client.out
	rm *.o
test:printout.c card.o game.o client.o
	gcc printout.c card.o game.o client.o -lGL -lGLU -lglut -o test.out
card.o:card.c card.h
	gcc -c card.c
game.o:game.c game.h
	gcc -c game.c
client.o:client.c client.h
	gcc -c client.c
clean:
	rm *.out *.o
