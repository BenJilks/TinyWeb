#include "TinyWeb/RawData.h"
#include <stdio.h>
#include <stdlib.h>

/* Reads raw text from a file */
char* ReadFile(char* file_path)
{
	unsigned int length;
	char* data;

	FILE* file = fopen(file_path, "r");
	fseek(file, 0, SEEK_END);
	length = ftell(file);
	rewind(file);
	data = (char*)malloc(length+1);
	fread(data, 1, length, file);
	fclose(file);
	
	data[length] = '\0';
	return data;
}

