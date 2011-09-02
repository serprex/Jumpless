CC=gcc -std=gnu99 -O3 -s
CW=-fwhole-program -ffast-math -lglfw -lGL
all:j e
j:tgen.o
	${CC} tgen.o j.c -o J ${CW}
e:tgen.o
	${CC} tgen.o e.c -o E ${CW}
spr:spr/*
	pinch g G