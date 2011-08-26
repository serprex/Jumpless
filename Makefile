CC=gcc -std=gnu99 -O3 -s
CW=-fwhole-program -ffast-math -lglfw -lGL
all: j.c j.h tgen.o e
	${CC} tgen.o j.c -o J ${CW}
e: e.c j.h tgen.o
	${CC} tgen.o e.c -o E ${CW}
spr: spr/*
	pinch g G