#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>
#include <string>
#include <fstream>
#include <SDL/SDL_ttf.h>
#include "talks.h"
#include "debug.h"
#include "globals.h"
#include "keyboard.h"



Talks::Talks()
{
	PRINT_CONSTR(1, "Construction de la classe Talks")
	TTF_Init();
	std::string background_name = "talks_background.bmp";
	std::string font_name = "font1.ttf"; //
	m_font_color.r = 0;
	m_font_color.g = 0;
	m_font_color.b = 0;
	m_text_background = SDL_LoadBMP((PIC_TALKS_DIR + background_name).c_str());
	m_pos_background.x = 5;
	m_pos_background.y = 400;
	for (int i = 0; i < LINES_NUMBER; i++){
		m_text_surface[i] = NULL;
		m_pos_text[i].x = POSX;
		m_pos_text[i].y = POSY + i * POSH;
	}
	m_font = TTF_OpenFont((FONTS_TALKS_DIR + font_name).c_str(), 30);
}

Talks::~Talks()
{
	PRINT_CONSTR(1, "Destruction de la classe Talks")
	SDL_FreeSurface(m_text_background);
	for (int i = 0; i < LINES_NUMBER; i++)
		SDL_FreeSurface(m_text_surface[i]);
	TTF_CloseFont(m_font);
	TTF_Quit();
}

void Talks::display_background()
{
	SDL_BlitSurface(m_text_background, NULL, screen, &m_pos_background);
}


struct cell_string *Talks::cut_text(std::string text)
{
	std::string str;
	SDL_Surface *surface;
	cell_string *list_string = NULL, *curs_list;
	list_string = new cell_string;
	curs_list = list_string;
	text+= ' '; // necessaire pour eviter une boucle infinie avec text == "-"
	while (!text.empty()) {
		str = "M";
		surface = TTF_RenderText_Blended(m_font, str.c_str(), m_font_color);
		while( (surface->w < POSW) && !text.empty()) {
			if (text[0] == '\n') {
				text = text.substr(1, text.size() - 1);
				str+= ' ';
				break;
			}
			str+= text[0];
			text = text.substr(1, text.size() - 1);
			SDL_FreeSurface(surface);
			surface = TTF_RenderText_Blended(m_font, str.c_str(), m_font_color);
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
		SDL_FreeSurface(surface);
	}
	return list_string->next;
}

void Talks::instant_display(std::string str, int line)
{
	if (m_text_surface[line] != NULL)
		SDL_FreeSurface(m_text_surface[line]);
	m_text_surface[line] = TTF_RenderText_Blended(m_font, str.c_str(), m_font_color);
	SDL_BlitSurface(m_text_surface[line], NULL, screen, &(m_pos_text[line]));
	SDL_Flip(screen);
}

void Talks::progressive_display(std::string str, int line)
{                                            
	std::string curr_text;
	SDL_Event event;
	for (uint32_t i = 0; i < str.size(); i++){
		SDL_Delay(DISPLAY_SPEED);          
		curr_text += str[i];
		m_text_surface[line] = TTF_RenderText_Blended(m_font, curr_text.c_str(), m_font_color);
		SDL_BlitSurface(m_text_surface[line], NULL, screen, &(m_pos_text[line]));
		SDL_Flip(screen);
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
	SDL_FreeSurface(m_text_surface[0]);
	for (int i = 0; i < LINES_NUMBER - 1; i++){
		m_text_surface[i] = m_text_surface[i+1];
		SDL_BlitSurface(m_text_surface[i], NULL, screen, &(m_pos_text[i]));
	}
	m_text_surface[LINES_NUMBER - 1] = NULL;
	SDL_Flip(screen);
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
	ifstream file((TEXT_TALKS_DIR + filename).c_str(), ios::in);
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
