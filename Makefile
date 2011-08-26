CC=gcc -std=gnu99 -O3 -s
O=tgen.o j.o
all: ${O}
	${CC} ${O} -o J -fwhole-program -ffast-math -lglfw -lGL
e: e.c
	${CC} tgen.o e.c -o E -fwhole-program -ffast-math -lglfw -lGL
spr:
	pinch g G
.PHONY:spr