#include <iostream>
#include <string>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


#include "files.h"
		
		
void new_level_file(std::string file_name, size_t weight, size_t height)
{
	FILE *file;
	file = fopen(file_name.c_str(), "w+");
	fprintf(file, "Size: %d %d\n\nBackground: background.bmp\n\nCollision:\n", weight, height);
	for (size_t i = 0; i < height; i++){
		for (size_t j = 0; j < weight; j++)
			fprintf(file, "0 ");
		fprintf(file, "\n");
	}
	fprintf(file,"\n\nPic_list:\n\n");
	fclose(file);
}

void find_string(std::string str, FILE* file)
{
	uint32_t char_found = 0;
	uint32_t size = str.size();
	char current = 'a';
	fseek(file, 0, SEEK_SET);
	while (current != EOF && char_found < size){
		current = fgetc(file);		
		if (current == str[char_found])
			char_found++;
		else
			char_found = 0;
	}
}