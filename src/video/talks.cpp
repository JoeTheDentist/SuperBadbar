/**
 * 	@file talks.cpp
 * 	@brief Implémentation de la classe Talks
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>
#include <stdint.h>
#include <string>
#include <fstream>

#include "talks.h"
#include "../util/debug.h"
#include "../util/repertories.h"
#include "../control/keyboard.h"
#include "../video/pictures_container.h"
#include "../util/globals.h"
#include "../video/surface_frame.h"


Talks::Talks():
	m_font(POSH - 10, 0, 0, 0)
{
}

Talks::~Talks()
{
	PRINT_CONSTR(1, "Destruction de la classe Talks")
}

void Talks::init_talks(Camera *camera, Pictures_container *pictures_container)
{
	PRINT_CONSTR(1, "Initialisation de la classe Talks")
	m_camera = camera;
	std::string background_name = "talks_background.png";
	m_text_background = new Surface(PIC_TALKS_R + background_name);
	m_pos_background.x = 5;
	m_pos_background.y = 400;
	m_pos_background.w = m_text_background->w();
	m_pos_background.h = m_text_background->h();
	m_talker = new Surface(PIC_TALKS_R + "babar.png");
	m_pos_talker.x = POSX;
	m_pos_talker.y = POSY;
	m_pos_talker.w = m_talker->w();
	m_pos_talker.h = m_talker->h();
	for (int i = 0; i < LINES_NUMBER; i++){
		m_pos_text[i].x = m_pos_talker.x + m_pos_talker.w + 10;
		m_pos_text[i].y = POSY + i * POSH;
		m_pos_text[i].w = 0;
	}
	m_font.set_color(0, 0, 0);
	m_active = false;
}

void Talks::display_text(std::string str)
{
	m_waiting_for_enter = false;
	m_curr_line = 0;
	m_string_curs = 0;
	m_active = true;
	aux_cut_text(str);
	aux_display_cell(m_cells.front());
	m_cells.pop();
	PRINT_TRACE(2, "Affichage d'un texte par Talks")
}

void Talks::load_and_display_text(std::string filename)
{

	char curr;
	std::ifstream file((TALKS_R + filename).c_str(), std::ios::in);
	std::string str;
	if(!file) {
		std::cout << "Erreur lors de l'ouverture du fichier de dialogue " << filename << std::endl;
		return;
	}
	while (!file.eof()) {
		file.get(curr);
		str += curr;
	}
	str.erase(str.size()-1);
	file.close();
	display_text(str);
}

void Talks::update()
{

	if (!aux_end_of_cell() && !m_waiting_for_enter) {
		bool temp = write_letter();
		if (temp) 
			move_up();
	}
	if (gKeyboard->is_next_menu_key()) {
		if (gKeyboard->pop_menu_key() == mk_enter) {
			if (end_of_talks()) {
				m_active = false;
				return;
			}
			if (aux_end_of_cell()) {
				aux_display_cell(m_cells.front());
				m_cells.pop();
			} else if (m_waiting_for_enter) {
				m_waiting_for_enter = false;
				end_move_up();
			} else {
				while (!write_letter()) {}
				move_up();
			}
		}
	}
}

bool Talks::isActive()
{
	return m_active;
}

void Talks::display()
{
	display_background();
	for (int i = 0; i < LINES_NUMBER; i++){
		std::list<Surface_text *>::iterator it;
		Rect pos = m_pos_text[i];
		for (it = m_text_surface[i].begin(); it != m_text_surface[i].end(); ++it) {
			if (*it)
				m_camera->display_picture((*it), &pos, true);
			pos.x += (*it)->w();
		}
	}
}


/************************************************/
/**			Fonctionnement interne				*/
/************************************************/


void Talks::aux_cut_text(std::string str)
{
	unsigned int curs = 0;
	
	while (curs < str.size()) {
		std::string newString, newTalker;
		if (str[curs] == '<') {
			curs++;
			while (str[curs] != '>' && curs < str.size()) {
				newTalker += str[curs];
				curs++;
			}
			curs++;
			while (str[curs] != '<' && curs < str.size()) {
				newString += str[curs];
				curs++;
			}
			while (newString[newString.size() - 1] == '\n') {
				newString.erase(newString.size() - 1, 1);
			}
			cell_string newCell;
			newCell.str = newString;
			newCell.talker = newTalker;
			std::cout << "talker: " << newTalker << std::endl << "text: " << newString << std::endl;
			m_cells.push(newCell);
		}
	}
}

void Talks::aux_display_cell(cell_string cell)
{
	m_talker = new Surface(PIC_TALKS_R + cell.talker + ".png");
	std::cout << "affichage de " << cell.str << std::endl;
	m_text = cell.str;
	m_pos_talker.x = POSX;
	m_pos_talker.y = POSY;
	m_pos_talker.w = m_talker->w();
	m_pos_talker.h = m_talker->h();
	m_string_curs = 0;
	clear_lines();
	for (int i = 0; i < LINES_NUMBER; i++){
		m_pos_text[i].x = m_pos_talker.x + m_pos_talker.w + 10;
		m_pos_text[i].y = POSY + i * POSH;
		m_pos_text[i].w = 0;
	}
}	

bool Talks::aux_end_of_cell()
{
	return m_string_curs >= m_text.size();
}

void Talks::display_background()
{
	m_camera->display_picture(m_text_background, &m_pos_background, true);
	m_camera->display_picture(m_talker, &m_pos_talker, true);
	Surface_frame *plop = new Surface_frame(m_pos_background, 100, 100, 100);
	m_camera->display_picture(plop, &m_pos_background, true);
	delete plop;
}

void Talks::move_up()
{
	m_curr_line++;
	if (m_curr_line >= LINES_NUMBER) {
		m_waiting_for_enter = true;
		m_curr_line = LINES_NUMBER - 1;
		return;
	} 
}

void Talks::end_move_up()
{
	m_text_surface[0].clear();
	for (int i = 0; i < LINES_NUMBER - 1; i++){
		m_text_surface[i] = m_text_surface[i+1];
	}
	m_text_surface[LINES_NUMBER - 1].clear();
	m_pos_text[LINES_NUMBER -1].w = 0;	
}

bool Talks::write_letter()
{
	if (aux_end_of_cell())
		return true;
	std::string temp;
	if (m_text[m_string_curs] == '\n') {
		m_string_curs++;
		std::cout << "true 1" << std::endl;

		return true;
	}
	temp += m_text[m_string_curs];
	Surface_text *surf = new Surface_text(temp, m_font);
	if ((m_pos_text[m_curr_line].x + m_pos_text[m_curr_line].w + surf->w()) > POSW) {
		delete surf;
		std::cout << "a" << temp << "a" << std::endl;
		return true;
	} else {
		m_text_surface[m_curr_line].push_back(surf);
		m_string_curs++;
		m_pos_text[m_curr_line].w += surf->w();
		return false;
	}
}

bool Talks::end_of_talks()
{
	return aux_end_of_cell() && m_cells.empty();
}

void Talks::clear_lines()
{
	for (int i = 0; i < LINES_NUMBER; ++i) {
		m_text_surface[i].clear();
	}
	m_curr_line = 0;
}

