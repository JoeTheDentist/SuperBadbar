#include <iostream>
#include <string>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "files.h"
#include "editor.h"
		
void new_level_file(std::string file_name, std::string background_name)
{
	FILE *file;
	std::string file_n = LEVELS_DIR + file_name;
	file = fopen(file_n.c_str(), "w+");
	fprintf(file, "#Background#\n%s\n\n", background_name.c_str());
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

std::string static_pic_file_name(std::string str)
{ 
	return STATICS_PIC_DIR + str + STATICS_PIC_EXT ;
}

SDL_Surface *load_static(std::string str)
{
	SDL_Surface *pic = SDL_LoadBMP(static_pic_file_name(str).c_str());
	SDL_SetColorKey(pic, SDL_SRCCOLORKEY, SDL_MapRGB(pic->format, 0, 0, 255));
	return pic;
}