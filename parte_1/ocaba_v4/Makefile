########################################################
CC = gcc
CFLAGS = -Wall -ansi -pedantic
EJS = ocabas
########################################################

all: ocabas  dist.tgz clean

ocabas: game_loop.o game.o screen.o space.o graphic_engine.o command.o player.o object.o GameReader.o
	$(CC) $(CFLAGS) -o ocabas game_loop.o game.o screen.o space.o graphic_engine.o command.o player.o object.o GameReader.o

game_loop.o:graphic_engine.h game.h
	$(CC) $(CFLAGS) -c game_loop.c

game.o: game.c game.h command.h space.h player.h object.h GameReader.h
	$(CC) $(CFLAGS) -c game.c

command.o: command.c command.h
	$(CC) $(CFLAGS) -c command.c

space.o: space.c space.h object.h
	$(CC) $(CFLAGS) -c space.c

graphic_engine.o: graphic_engine.c graphic_engine.h game.h screen.h
		$(CC) $(CFLAGS) -c 	graphic_engine.c

screen.o: screen.c screen.h
	$(CC) $(CFLAGS) -c screen.c

player.o: player.c player.h
		$(CC) $(CFLAGS) -c player.c

object.o: object.c object.h
				$(CC) $(CFLAGS) -c object.c
GameReader.o: GameReader.c GameReader.h game.h
				 $(CC) $(CFLAGS) -c GameReader.c
dist.tgz:
	tar -cvzf ocabas.tgz *.c *.h Makefile

clean:
	rm -rf *.o
