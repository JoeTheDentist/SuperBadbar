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



Talks::Talks():
	m_font(POSH - 10, 0, 0, 0)
{
}

Talks::~Talks()
{
	PRINT_CONSTR(1, "Destruction de la classe Talks")
	clear_talks();
}

void Talks::init_talks(Camera *camera, Pictures_container *pictures_container)
{
	PRINT_CONSTR(1, "Initialisation de la classe Talks")
	clear_talks();
	m_camera = camera;
	std::string background_name = "talks_background.png";
	m_text_background = new Surface(PIC_TALKS_R + background_name);
	m_pos_background.x = 5;
	m_pos_background.y = 400;
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

void Talks::display_background()
{
	m_camera->display_picture(m_text_background, &m_pos_background, true);
	m_camera->display_picture(m_talker, &m_pos_talker, true);
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


void Talks::display_text(std::string str)
{
	m_waiting_for_enter = false;
	m_curr_line = 0;
	m_string_curs = 0;
	m_active = true;
	PRINT_TRACE(2, "Affichage d'un texte par Talks")
	m_text = str;
	for (int i = 0; i < LINES_NUMBER; i++){
		m_pos_text[i].x = m_pos_talker.x + m_pos_talker.w + 10;
		m_pos_text[i].y = POSY + i * POSH;
		m_pos_text[i].w = 0;
	}
//~ 	std::string curr_text;
//~ 	cell_string *list_string = cut_text(str);
//~ 	cell_string *curr_list = list_string;
//~ 	/* affichage des premieres lignes (tant qu'on a pas besoin de décaler vers le haut) */
//~ 	for (int i = 0; (i < LINES_NUMBER) && (curr_list!=NULL); i++) {
//~ 		progressive_display(curr_list->str, i);
//~ 		curr_list = curr_list->next;
//~ 	}

//~ 	while (curr_list!=NULL) {
//~ 		while (gKeyboard->wait_menu_key() != mk_enter) {}
//~ 		move_up();
//~ 		progressive_display(curr_list->str, LINES_NUMBER - 1);
//~ 		curr_list = curr_list->next;
//~ 	}
//~ 	while (gKeyboard->wait_menu_key() != mk_enter) {}

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

void Talks::clear_talks()
{
}

void Talks::update()
{
	// ecrire deux lettres
//~ 	if (m_text_surface[m_curr_line]->w() + m_pos_text[m_curr_line].x < POSW - 20) {
//~ 		move_up();
//~ 	}
	if (!end_of_text() && !m_waiting_for_enter) {
		bool temp = write_letter();
		if (temp) 
			move_up();
	}
	if (gKeyboard->is_next_menu_key()) {
		if (gKeyboard->pop_menu_key() == mk_enter) {
			if (end_of_text()) {
				m_active = false;
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

bool Talks::end_of_text()
{
	return m_string_curs >= m_text.size();
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

bool Talks::write_letter()
{
	if (end_of_text())
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


