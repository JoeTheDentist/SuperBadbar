

#include <iostream>
#include <stdint.h>

#include "pic_list.h"

Pic_list::Pic_list()
{
	m_list = NULL;
}

Pic_list::~Pic_list()
{
	pic_cell *temp;
	while (m_list != NULL) {
		temp = m_list;
		m_list = m_list->suiv;
		if (temp->pic != NULL)
			SDL_FreeSurface(temp->pic);
		delete temp;
	}
}

void Pic_list::add(std::string file_name, SDL_Rect pos)
{
	pic_cell *head = new pic_cell;
	head->pic = SDL_LoadBMP(file_name.c_str());
	head->pos = pos;
	head->pic_name = file_name;
	head->suiv = m_list;
	m_list = head;
}

void Pic_list::display_list(SDL_Surface *screen)
{
	pic_cell *curs = m_list;
	while (curs != NULL) {
		SDL_BlitSurface(curs->pic, NULL, screen, &(curs->pos));
		curs = curs->suiv;
	}
	SDL_Flip(screen);
}

