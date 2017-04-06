all:
	gcc Src/*.c -IInclude -lSDL2 -lGL -ldl -lm -o TinyWeb

