/**
 * 	@file talks.cpp
 * 	@brief Implémentation de la classe Talks
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>
#include <stdint.h>
#include <string>
#include <fstream>

#include "Talks.h"
#include "param/param_talks.h"
#include "util/debug.h"
#include "util/repertories.h"
#include "control/Keyboard.h"
#include "control/KeyboardConfig.h"
#include "video/PicturesContainer.h"
#include "util/globals.h"
#include "video/SurfaceUniform.h"
#include "video/SurfaceFrame.h"


Talks::Talks():
	m_font(POSH - 10, 0, 0, 0),
	m_cell_letters()
{
}

Talks::~Talks()
{
	#ifndef DISABLE_TALKS
	clear_lines();
	delete m_text_background;
	delete m_frame_background;
	delete m_talker;
	PRINT_CONSTR(1, "Destruction de la classe Talks");
	#endif
}

void Talks::init_talks(Camera *camera, PicturesContainer *PicturesContainer)
{
	#ifndef DISABLE_TALKS
	PRINT_CONSTR(1, "Initialisation de la classe Talks")
	m_have_to_leave = false;
	m_camera = camera;
	std::string background_name = "talks_background.png";
	m_text_background = new SurfaceUniform(camera->width() - 2 * TALKS_BACKGROUND_OFFSET_W,
											TALKS_BACKGROUND_SIZE_H, TALKS_BACKGROUND_R,
											TALKS_BACKGROUND_G, TALKS_BACKGROUND_B);
	m_text_background->set_alpha(ALPHA_TALKS_BACKGROUND);
	m_pos_background.x = 5;
	m_pos_background.y = camera->height() - TALKS_BACKGROUND_OFFSET_H - m_text_background->h();
	m_pos_background.w = m_text_background->w();
	m_pos_background.h = m_text_background->h();

	m_frame_background = new SurfaceFrame(m_pos_background, TALKS_FRAME_R, TALKS_FRAME_G, TALKS_FRAME_B);
	m_talker = new Surface(PIC_TALKS_R + "babar.png");
	m_pos_talker.x = POSX;
	m_pos_talker.y = POSY;
	m_pos_talker.w = m_talker->w();
	m_pos_talker.h = m_talker->h();
	for (int i = 0; i < LINES_NUMBER; i++) {
		m_pos_text[i].x = m_pos_talker.x + m_pos_talker.w + 10;
		m_pos_text[i].y = POSY + i * POSH;
		m_pos_text[i].w = 0;
	}
	m_font.set_color(TALKS_TEXT_R, TALKS_TEXT_G, TALKS_TEXT_B);
	m_active = false;
	#endif
}

void Talks::display_text(std::string str)
{
	#ifndef DISABLE_TALKS
	m_waiting_for_enter = false;
	m_curr_line = 0;
	m_string_curs = 0;
	m_active = true;
	aux_cut_text(str);
	aux_display_cell(m_cells.front());
	m_cells.pop();
	PRINT_TRACE(2, "Affichage d'un texte par Talks")
	#endif
}

void Talks::load_and_display_text(std::string filename)
{

	char curr;
	std::ifstream file((TALKS_R + filename).c_str(), std::ios::in);
	std::string str;
	if(!file) {
		PRINT_DEBUG(1, "Erreur lors de l'ouverture du fichier de dialogue %s", filename.c_str());
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
	#ifndef DISABLE_TALKS
	if (!aux_end_of_cell() && !m_waiting_for_enter) {
		bool temp = write_letter();
		if (temp)
			move_up();
	}
	if (!aux_end_of_cell() && !m_waiting_for_enter) {
		bool temp = write_letter();
		if (temp)
			move_up();
	}
	if (gKeyboard->is_next_menu_key()) {
		menu_key key = gKeyboard->pop_menu_key();
		switch(key) {
		case mk_enter:
			if (end_of_talks()) {
				clear_lines();
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
				int temp = 0;
				while (!write_letter()) {
					if (temp++ % 2 == 0) {
						update_letters();
					}
				}
				move_up();
			}
			break;
		case mk_exit:
			m_have_to_leave = true;
			break;
		default:
			break;
		}
	}
	update_letters();
	#endif
}

void Talks::update_letters()
{
	for (int i = 0; i < LINES_NUMBER; i++){
		std::list<SpecialLetter *>::iterator it;
		for (it = m_text_surface[i].begin(); it != m_text_surface[i].end(); ++it) {
			if (*it)
				(*it)->update();
		}
	}
}

bool Talks::isActive()
{
	#ifndef DISABLE_TALKS
	return m_active;
	#else
	return false;
	#endif
}

void Talks::display()
{
	#ifndef DISABLE_TALKS
	display_background();
	for (int i = 0; i < LINES_NUMBER; i++){
		std::list<SpecialLetter *>::iterator it;
		Rect pos = m_pos_text[i];
		for (it = m_text_surface[i].begin(); it != m_text_surface[i].end(); ++it) {
			pos.y = m_pos_text[i].y + ((*it)->fake_h() - (*it)->h()) / 2;
			if (*it)
				m_camera->display_picture((*it), &pos, true);
			pos.x += (*it)->w();

		}
	}
	#endif
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
			m_cells.push(newCell);
		}
	}
}

void Talks::aux_display_cell(cell_string cell)
{
	delete m_talker;
	m_talker = new Surface(PIC_TALKS_R + cell.talker + ".png");
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
	prepare_cell_string(cell);
}

bool Talks::aux_end_of_cell()
{
//~ 	return m_string_curs >= m_text.size();
	return m_cell_letters.empty();
}

void Talks::display_background()
{
	m_camera->display_picture(m_text_background, &m_pos_background, true);
	m_camera->display_picture(m_talker, &m_pos_talker, true);
	m_camera->display_picture(m_frame_background, &m_pos_background, true);
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
	clear_line(0);
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
	if (m_cell_letters.front().empty()) {
		m_cell_letters.pop();
		return true;
	}
	SpecialLetter *surf = m_cell_letters.front().front();
	m_cell_letters.front().pop();
	m_text_surface[m_curr_line].push_back(surf);
	return false;
}

bool Talks::end_of_talks()
{
//~ 	return aux_end_of_cell() && m_cells.empty();
	return m_cells.empty() && aux_end_of_cell();
}

void Talks::clear_line(int i)
{
	for (std::list<SpecialLetter *>::iterator it = m_text_surface[i].begin();
			it != m_text_surface[i].end(); ++it) {
		delete (*it);
	}
}

void Talks::clear_lines()
{
	for (int i = 0; i < LINES_NUMBER; ++i) {
		clear_line(i);
		m_text_surface[i].clear();
	}
	m_curr_line = 0;
}

std::list< std::string > Talks::string_to_list_words(std::string str)
{
	std::list < std::string > words;
	unsigned int i = 0;
	while (i < str.size()) {
		std::string newword;
		while (i < str.size() && str[i] != ' ' && str[i] != '\n') {
			newword += str[i];
			i++;
		}
		words.push_back(newword);
		if (str[i] == '\n') {
			words.push_back("\n");
		}
		i++;
	}
	return words;
}

 std::list< word_and_length > Talks::words_to_words_and_length(std::list < std::string > words)
{
	std::list< word_and_length > res;
	for (std::list<std::string>::iterator it = words.begin(); it != words.end(); ++it) {
		std::string str = (*it);
		if (str[0] == '{') {
			treat_special_words(str, res);
			continue;
		}
		word_and_length newword;
		newword.newline = (str == "\n");
		if (!newword.newline) {
			newword.length = 0;
			for (unsigned int i = 0; i < str.length(); i++) {
				SpecialLetter *newletter =  new SpecialLetter(str[i], TALKS_TEXT_SIZE,
						TALKS_TEXT_R, TALKS_TEXT_G, TALKS_TEXT_B);
				newword.length += newletter->fake_w();
				(newword.letters).push_back(newletter);
			}
		}
		res.push_back(newword);
	}
	return res;
}

void Talks::prepare_cell_string(cell_string cell)
{
	std::list < word_and_length > words = Talks::words_to_words_and_length(Talks::string_to_list_words(cell.str));

	std::list < word_and_length >::iterator it = words.begin();
	while (it != words.end()) {
		std::queue <SpecialLetter *> newline;
		int linelength = (*it).length;
		while(it != words.end() && !(*it).newline && (m_pos_text[0].x + linelength + POSX) < POSW) {
			for (std::list<SpecialLetter *>::iterator it2 = (*it).letters.begin(); it2 != (*it).letters.end(); it2++) {
				newline.push((*it2));
			}
			SpecialLetter *spaceletter = new SpecialLetter(' ', TALKS_TEXT_SIZE,
					TALKS_TEXT_R, TALKS_TEXT_G, TALKS_TEXT_B);
			newline.push(spaceletter);
			linelength += spaceletter->fake_w();
			it++;
			linelength += (*it).length;
		}
		newline.push(new SpecialLetter(' ', TALKS_TEXT_SIZE,
					TALKS_TEXT_R, TALKS_TEXT_G, TALKS_TEXT_B));
		m_cell_letters.push(newline);
		if (it == words.end())
			break;
		if ((*it).newline)
			++it;

	}
}

void Talks::treat_special_words(std::string specialword, std::list < word_and_length > &words_list)
{
	specialword.erase(0, 1); // on enleve le '{'
	specialword.erase(specialword.length() - 1, 1); // on enleve le '}'
	std::list < std::string > newwords = Talks::convert_special_word(specialword);
	for (std::list<std::string>::iterator it = newwords.begin(); it != newwords.end(); ++it) {
		word_and_length temp;
		temp.newline = false;
		temp.length = 0;
		for (unsigned int i = 0; i < (*it).length(); ++i) {
			SpecialLetter *l = new SpecialLetter((*it)[i], TALKS_TEXT_SIZE, TALKS_TEXTSPECIAL_R,
					TALKS_TEXTSPECIAL_G, TALKS_TEXTSPECIAL_B);
			temp.letters.push_back(l);
			temp.length += l->fake_w();
		}
		words_list.push_back(temp);
	}
}

#define MACRO_TALKS_KEYBOARD(param) \
	if (specialword == #param) { \
		auxres = gKeyboardConfig->getStringKey(param); \
	} \


std::list<std::string> Talks::convert_special_word(std::string specialword)
{
	std::list < std::string > res;
	std::string auxres;
	MACRO_TALKS_KEYBOARD(k_left)
	MACRO_TALKS_KEYBOARD(k_right)
	MACRO_TALKS_KEYBOARD(k_up)
	MACRO_TALKS_KEYBOARD(k_down)
	MACRO_TALKS_KEYBOARD(k_fire)
	MACRO_TALKS_KEYBOARD(k_jump)
	MACRO_TALKS_KEYBOARD(k_next_weapon)
	MACRO_TALKS_KEYBOARD(k_prev_weapon)
	MACRO_TALKS_KEYBOARD(k_escape)
	MACRO_TALKS_KEYBOARD(k_jump)
	MACRO_TALKS_KEYBOARD(k_exit)
	MACRO_TALKS_KEYBOARD(k_action)

	std::string newword;
	for (unsigned int i = 0; i < auxres.length(); ++i) {
		if (auxres[i] == ' ') {
			res.push_back(newword);
			newword = "";
		} else {
			newword += auxres[i];
		}
	}
	if (auxres[auxres.length()] != ' ')
		res.push_back(newword);
	return res;
}
