#include <iostream>
#include <string>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


#include "files.h"
		
		
void new_level_file(std::string file_name)
{
	FILE *file;
	file = fopen(file_name.c_str(), "w+");
	fprintf(file, "#Background#\nbackground.bmp\n\n#Collisions#\n");
	//~ for (size_t i = 0; i < height; i++){
		//~ for (size_t j = 0; j < weight; j++)
			//~ fprintf(file, "0 ");
		//~ fprintf(file, "\n");
	//~ }
	fprintf(file,"\n\n#Pictures#\n\nend");
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