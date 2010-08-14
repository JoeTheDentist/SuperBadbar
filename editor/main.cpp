#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "collision_matrix.h"
#include "editor.h"
#include "pic_list.h"



int main(int argc, char *argv[])
{
	Pic_list list;
	SDL_Rect pos;
	list.add("../pic/blob.bmp", pos);
	
	return 0;
}
