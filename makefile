all: game.o grid.o main.o printer.o
	gcc game.o grid.o main.o printer.o -lalloc_grid -L./ -o main

game.o: game.c game.h
	gcc game.c -c -o game.o

grid.o: grid.c grid.h
	gcc grid.c -c -o grid.o

main.o: main.c game.h grid.h
	gcc main.c  -c -o main.o

printer.o: printer.c printer.h
	gcc printer.c -c -o printer.o

