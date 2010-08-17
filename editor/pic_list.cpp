

#include <iostream>
#include <stdint.h>

#include "pic_list.h"     
#include "window.h"
#include "files.h"

Pic_list::Pic_list()
{
	m_list = NULL;
}

Pic_list::Pic_list(std::string file_name)
{
	FILE *file = fopen(file_name.c_str(), "r");
	std::string str;
	int x, y;
	char temp[100];
	SDL_Rect pos;
	bool leave = false;
	find_string("Pic_list:", file);
	while(!leave){
		fscanf(file, "%s", temp);
		if (!strcmp(temp, "end")) {
			leave = true;
		}
		else {
			fscanf(file, "%d", &x);
			fscanf(file, "%d", &y);
			pos.x = x;
			pos.y = y;
			add(temp, pos);
		}
	}	
		
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

void Pic_list::save(FILE* file)
{
	pic_cell *curs = m_list;
	fprintf(file, "Pic_list:\n");
	while (curs != NULL) {
		fprintf(file, "%s %d %d\n", curs->pic_name.c_str(), curs->pos.x, curs->pos.y);
		curs = curs->suiv;
	}
	fprintf(file, "end");

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

void Pic_list::display_list(Window *window)
{
	pic_cell *curs = m_list;
	while (curs != NULL) {
		window->display_pic(curs->pic, curs->pos);
		curs = curs->suiv;
	}
}

