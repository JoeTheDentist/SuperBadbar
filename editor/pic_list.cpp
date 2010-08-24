

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
	find_string("#Pictures#", file);
	m_list = NULL;
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


void Pic_list::save(FILE* file)
{
	pic_cell *curs = m_list;
	fprintf(file, "#Pictures#\n");
	while (curs != NULL) {
		fprintf(file, "%s %d %d\n", curs->pic_name.c_str(), curs->pos.x, curs->pos.y);
		curs = curs->suiv;
	}
	fprintf(file, "end");

}


void Pic_list::add(std::string file_name, SDL_Rect pos)
{
	pic_cell *m_last = m_list;
	pic_cell *new_cell= new pic_cell;

	new_cell->pic = SDL_LoadBMP(file_name.c_str());
	new_cell->pos = pos;
	new_cell->pic_name = file_name;
	new_cell->suiv = NULL;
	if (m_list == NULL) {
		m_list = new_cell;
	}
	else {
		m_last = m_list;
		while (m_last->suiv != NULL)
			m_last = m_last->suiv;
		m_last->suiv = new_cell;
	}
}

void Pic_list::display_list(Window *window)
{
	pic_cell *curs = m_list;
	while (curs != NULL) {
		window->display_pic(curs->pic, curs->pos);
		curs = curs->suiv;
	}
}

/* fonction recursive utilisée dans la méthode suivante */
bool delete_rec(SDL_Rect pos, pic_cell *curs)
{
	pic_cell *temp;
	if (curs->suiv != NULL ) {
		if (!delete_rec(pos, curs->suiv)) {
			temp = curs->suiv;
			if ((temp->pos.x < pos.x) && (temp->pos.x + temp->pic->w > pos.x)) {
				if ((temp->pos.y < pos.y) && (temp->pos.y + temp->pic->h > pos.y)) {
					SDL_FreeSurface(temp->pic);
					curs->suiv = curs->suiv->suiv;
					delete temp;
					return true;
				}
			}
		}
		else {
			return true;
		}
	}
	return false;
}


void Pic_list::delete_pic(SDL_Rect pos)
{
	pic_cell *senti = new pic_cell;
	senti->suiv = m_list;
	delete_rec(pos, senti);
	m_list = senti->suiv;
	delete senti;
}

pic_cell *Pic_list::last_pic_cell()
{
	pic_cell* curs = m_list;
	while (curs->suiv != NULL)
		curs = curs->suiv;
	return curs;
}


pic_cell *Pic_list::previous_pic_cell(pic_cell *cell)
{
	pic_cell* curs = m_list;
	if (cell == m_list)
		return m_list;
	if (cell == NULL)
		return last_pic_cell();
	while (curs->suiv != cell && curs!=NULL)
		curs = curs->suiv;
	if (curs == NULL) {
		return NULL;
	}
	if (curs->pic_name == cell->pic_name)
		curs = previous_pic_cell(curs);
	return curs;
}

pic_cell *Pic_list::next_pic_cell(pic_cell *cell)
{
	if (cell == NULL)
		return NULL;
	if(cell->suiv == NULL)
		return cell;
	if (cell->pic_name == cell->suiv->pic_name)
		cell->suiv = next_pic_cell(cell);
	return cell->suiv;
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


