CC=gcc -std=gnu99 -O3 -s
O=tgen.o j.o
all: ${O}
	${CC} ${O} -o J -fwhole-program -lglfw -lGL
spr:
	pinch g G
.PHONY:spr