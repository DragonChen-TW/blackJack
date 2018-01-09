all:server_client
server_client:server.c client.c card.o game.o
	gcc server.c card.o game.o -o server.out
	gcc client.c card.o game.o -o client.out
	rm *.o
test:test.c printout.o
	gcc printout.o test.c -o test.out -lGL -lGLU -lglut
card.o:card.c card.h
	gcc -c card.c
game.o:game.c game.h
	gcc -c game.c
printout.o:printout.c printout.h
	gcc -c printout.c -lGL -lGLU -lglut
clean:
	rm *.out
