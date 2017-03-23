all:
	gcc Src/*.c -IInclude -lSDL2 -lGL -ldl -o TinyWeb

