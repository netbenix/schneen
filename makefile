CC= gcc
ARGS= -std=gnu99
CFLAGS= -I/usr/include/GLFW/
LDLIBS= -lglfw -lOpenGL -lGLEW
OBJ= main.o shader.o triangle.o

all: $(OBJ)
	$(CC) $(CFLAGS) $(ARGS) -o schneen $(OBJ) $(LDLIBS)

clean: $(OBJ)
	rm *.o
	rm ogl-test
	make ogl-test

main.o: main.c
	$(CC) -c main.c

shader.o: common/shader.c
	$(CC) -c common/shader.c

triangle.o: objects/triangle.c
	$(CC) -c objects/triangle.c