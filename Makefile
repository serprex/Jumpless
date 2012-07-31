CFLAGS=-std=gnu99 -Ofast -s
j:tgen.o
	${CC} ${CFLAGS} tgen.o j.c -o J ${CW} -lglfw -lGL -fwhole-program
	${CC} ${CFLAGS} tgen.o e.c -o E ${CW} -lglfw -lGL -fwhole-program
mingw:
	i486-mingw32-gcc ${CFLAGS} tgen.c e.c -o J.exe -lglfw -lopengl32
	i486-mingw32-gcc ${CFLAGS} tgen.c e.c -o E.exe -lglfw -lopengl32
spr:spr/*
	pinch g