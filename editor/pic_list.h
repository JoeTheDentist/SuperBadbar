
#ifndef _PIC_LIST_
#define _PIC_LIST_

#include <iostream>
#include <stdint.h>
#include <SDL/SDL.h>



struct pic_cell {
	SDL_Surface *pic;
	SDL_Rect pos;
	std::string pic_name;
	struct pic_cell *suiv;
};



class Pic_list{
private:
	pic_cell *m_list;
public:
	Pic_list();
	~Pic_list();
	void add(std::string file_name, SDL_Rect pos);
	void display_list(SDL_Surface *screen);
	
};







#endif