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



Talks::Talks()
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
	for (int i = 0; i < LINES_NUMBER; i++){
		m_text_surface[i] = NULL;
		m_pos_text[i].x = POSX;
		m_pos_text[i].y = POSY + i * POSH;
	}
	m_font.set_color(0, 0, 0);
}
void Talks::display_background()
{
	m_camera->display_picture(m_text_background, &m_pos_background);
}


struct cell_string *Talks::cut_text(std::string text)
{
	std::string str;
	cell_string *list_string = NULL, *curs_list;
	Surface_text *surface;
	list_string = new cell_string;
	curs_list = list_string;
	text+= ' '; // necessaire pour eviter une boucle infinie avec text == "-"
	while (!text.empty()) {
		str = "M";
		surface = new Surface_text(str, m_font);
		while( (surface->w() < POSW) && !text.empty()) {
			if (text[0] == '\n') {
				text = text.substr(1, text.size() - 1);
				str+= ' ';
				break;
			}
			str+= text[0];
			text = text.substr(1, text.size() - 1);
			delete surface;
			surface = new Surface_text(str, m_font);
		}
		str = str.substr(1, str.size() - 1);
		if (text[0] != ' ' && str[str.size()-1] != ' ') {
			str += '-';
			text.insert(0, "-");
		}
		std::cout << str << std::endl;
		curs_list->next = new cell_string;
		curs_list = curs_list->next;
		curs_list->str = str;
		curs_list->next = NULL;
		delete surface;
	}
	return list_string->next;
}

void Talks::instant_display(std::string str, int line)
{
	if (m_text_surface[line] != NULL)
		delete m_text_surface[line];
	m_text_surface[line] = new Surface_text(str, m_font);
	m_camera->display_picture(m_text_surface[line], &(m_pos_text[line]));
	m_camera->flip_camera();
}

void Talks::progressive_display(std::string str, int line)
{
	std::string curr_text;
	SDL_Event event;
	for (uint32_t i = 0; i < str.size(); i++){
		SDL_Delay(DISPLAY_SPEED);
		curr_text += str[i];
		m_text_surface[line] = new Surface_text(curr_text, m_font);
		m_camera->display_picture(m_text_surface[line], &(m_pos_text[line]));
		m_camera->flip_camera();
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_KEYDOWN)
				if(event.key.keysym.sym == SDLK_SPACE) {
					instant_display(str, line);
					return;
				}

		}
	}
}

void Talks::move_up()
{
	display_background();
	delete m_text_surface[0];
	for (int i = 0; i < LINES_NUMBER - 1; i++){
		m_text_surface[i] = m_text_surface[i+1];
		m_camera->display_picture(m_text_surface[i], &(m_pos_text[i]));
	}
	m_text_surface[LINES_NUMBER - 1] = NULL;
	m_camera->flip_camera();
}

void Talks::wait_space()
{
	SDL_Event event;
	bool leave = false;
	while(!leave){
		SDL_WaitEvent(&event);
		if(event.type == SDL_KEYDOWN)
			if(event.key.keysym.sym == SDLK_SPACE)
				leave = true;
	}
}

void Talks::display_text(std::string str)
{
	PRINT_TRACE(2, "Affichage d'un texte par Talks")
	display_background();
	std::string curr_text;
	cell_string *list_string = cut_text(str);
	cell_string *curr_list = list_string;
	/* affichage des premieres lignes (tant qu'on a pas besoin de décaler vers le haut) */
	for (int i = 0; (i < LINES_NUMBER) && (curr_list!=NULL); i++) {
		progressive_display(curr_list->str, i);		curr_list = curr_list->next;
	}

	while (curr_list!=NULL) {
		wait_space();
		move_up();
		progressive_display(curr_list->str, LINES_NUMBER - 1);
		curr_list = curr_list->next;
	}
	wait_space();

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
