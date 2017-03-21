all:
	gcc Src/*.c -IInclude -lSDL2 -lGL -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -o TinyWeb

