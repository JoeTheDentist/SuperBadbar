#ifndef _FILES_
#define _FILES_

#include <string>
#include <SDL/SDL.h>

#define STATICS_PIC_DIR "../pic/statics/"
#define STATICS_PIC_EXT ".bmp"


void new_level_file(std::string file_name, std::string background_name);
void find_string(std::string str, FILE* file);
std::string static_pic_file_name(std::string str);
SDL_Surface *load_static(std::string str);



#endif