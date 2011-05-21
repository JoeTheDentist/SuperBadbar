/**
 * 	@file keyboard.cpp
 * 	@brief implémentation de la Classe Keyboard
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
#include <iostream>

#include "../../lib/SDL/include/SDL/SDL.h"

#include <stdint.h>

#include "keyboard.h"
#include "../util/analyser.h"
#include "../util/debug.h"
#include "../util/repertories.h"
#include "../util/analyser.h"

void display_config();

Keyboard::Keyboard(bool record_on, bool replay_on,  std::string output_name, std::string input_name)
{
	PRINT_CONSTR(1, "Construction de Keyboard")
	for (uint32_t i = 0; i < SDLK_LAST; i++)
		m_key_config[i] = k_none;
	for (uint32_t i = 0; i <= k_fire; i++)
		set_key(i, 0);
	m_key_config[SDLK_i] = k_up;
	m_key_config[SDLK_k] = k_down;
	m_key_config[SDLK_j] = k_left;
	m_key_config[SDLK_l] = k_right;
	m_key_config[SDLK_q] = k_jump;
	m_key_config[SDLK_d] = k_fire;
	m_key_config[SDLK_ESCAPE] = k_escape;
	m_key_config[SDLK_SPACE] = k_action;
	m_key_config[SDLK_a] = k_prev_weapon;
	m_key_config[SDLK_z] = k_next_weapon;
	display_config();
//~ 	load_config("defaultkey.cfg");
	m_record_on = record_on;
	m_replay_on = replay_on;
	if (m_replay_on) {
		m_analyser = new Analyser();
		m_analyser->open(input_name);
	} else {
		m_analyser = NULL;
	}
	if (m_record_on) {
		m_record_file = new std::ofstream(output_name.c_str(), std::ios::out | std::ios::trunc);
	} else {
		m_record_file = NULL;
	}
	update_plop();
	update_plop();
	update_plop();
}

Keyboard::~Keyboard()
{
	PRINT_CONSTR(1, "Destruction d'Keyboard")
	if (m_record_file)
		delete m_record_file;
	if (m_analyser)
		delete m_analyser;
}

void Keyboard::load_config(std::string config_name)
{
	Analyser analyser;
	analyser.open(CONFIG_R + config_name);
	PRINT_DEBUG(1, "1");
	analyser.find_string("#k_up#");
	m_key_config[analyser.read_int()] = k_up;
	PRINT_DEBUG(1, "1");
	analyser.find_string("#k_down#");
	m_key_config[analyser.read_int()] = k_down;
	analyser.find_string("#k_left#");
	m_key_config[analyser.read_int()] = k_left;
	analyser.find_string("#k_right#");
	m_key_config[analyser.read_int()] = k_right;
	analyser.find_string("#k_jump#");
	m_key_config[analyser.read_int()] = k_jump;
	PRINT_DEBUG(1, "1");
	analyser.find_string("#k_fire#");
	m_key_config[analyser.read_int()] = k_fire;
	analyser.find_string("#k_escape#");
	m_key_config[analyser.read_int()] = k_escape;
	analyser.find_string("#k_prev_weapon#");
	m_key_config[analyser.read_int()] = k_prev_weapon;
	analyser.find_string("#k_next_weapon#");
	m_key_config[analyser.read_int()] = k_next_weapon;
	analyser.find_string("#k_action#");
	m_key_config[analyser.read_int()] = k_action;
	PRINT_DEBUG(1, "1");
	analyser.close();	
}

void Keyboard::update_events()
{
	update_plop();
	if (!m_replay_on) {
		if (m_record_on)
			*m_record_file << std::endl;
		for (int i = k_none; i < k_fire + 1 ; i++)
			if (key_down((enum key)i))
				incr_key_down(i);
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT :
				set_key(k_exit, 1);
				if (m_record_on)
					*m_record_file << k_exit << " " << key_down(k_exit) << " ";
				break;
			case SDL_KEYDOWN:
				set_key(m_key_config[event.key.keysym.sym],  1);
				if (m_record_on)
					*m_record_file << m_key_config[event.key.keysym.sym] <<
						" " << key_down(m_key_config[event.key.keysym.sym]) << " ";
				break;
			case SDL_KEYUP:
				set_key(m_key_config[event.key.keysym.sym], 0);
				if (m_record_on)
					 *m_record_file <<  m_key_config[event.key.keysym.sym] <<
						" " << key_down(m_key_config[event.key.keysym.sym]) << " ";
				break;
			default:
				break;
			}
		}
		if (m_record_on)
			*m_record_file << "666 666";
	} else {
		int x = m_analyser->read_int();
		int y = m_analyser->read_int();
		while (x != 666 && y != 666) {
			set_key(x, y);
			x = m_analyser->read_int();
			y = m_analyser->read_int();
		}
	}
}

void Keyboard::update_plop() 
{	
//~ 	for (uint32_t i = 0; i <= k_fire; i++) {
//~ 		m_key_down_bis[(enum key)i] = m_key_down_bis2[(enum key)i];
//~ 		m_key_down[(enum key)i] = m_key_down_bis[(enum key)i];
//~ 	}
}

bool Keyboard::key_down(enum key k) const
{
	return m_key_down[k];
}

int Keyboard::time_pressed(enum key k) const
{
	return m_key_down[k];
}

bool Keyboard::key_dir_down() const
{
    return (key_down(k_left)||key_down(k_right));
}

void Keyboard::disable_key(enum key k)
{
	set_key(k, 0);
}

void Keyboard::disable_all_keys()
{
	for (uint32_t i = 0; i <= k_fire; i++)
		disable_key((enum key)i);
}

menu_key Keyboard::treat_menu_key(SDL_Event event)
{
	switch(event.type)
	{
		case SDL_QUIT:
			return mk_exit;
		case SDL_KEYDOWN: /* Si appui d'une touche */
			// priorite aux touches en dur
			switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
					return mk_escape;
					break;
				case SDLK_UP:
					return mk_up;
				case SDLK_DOWN:
					return mk_down;
				case SDLK_LEFT:
					return mk_left;
				case SDLK_RIGHT:
					return mk_right;
				case SDLK_RETURN: case SDLK_KP_ENTER: case SDLK_SPACE:
					return mk_enter;
				default:
					break;
			}
			// sinon on regarde les touches du joueur
			switch (m_key_config[event.key.keysym.sym]) {
				case k_jump: case k_fire:
					return mk_enter;
				case k_up:
					return mk_up;
				case k_down:
					return mk_down;
				case k_right:
					return mk_right;
				case k_left:
					return mk_left;
				default:
					break;
			}
			break;
		default:
			break;
	}	
	return mk_none;
}

menu_key Keyboard::poll_menu_key()
{
	SDL_Event event;	
	menu_key res;
	while(SDL_PollEvent(&event)) {
		res = treat_menu_key(event);
		if (res != mk_none)
			return res;	
	}	
	return mk_none;	
}

menu_key Keyboard::wait_menu_key()
{
	SDL_Event event;
	menu_key res;
	while (true) {
		SDL_WaitEvent(&event);
		res = treat_menu_key(event);
		if (res != mk_none)
			return res;
	}
	return mk_none;
}

void Keyboard::wait_key(enum key k)
{
	SDL_Event event;
	bool leave = false;
	while(!leave){
		SDL_WaitEvent(&event);
		if(event.type == SDL_KEYDOWN)
			if(m_key_config[event.key.keysym.sym] == k)
				leave = true;
	}	
}

void Keyboard::enable_key_repeat()
{
	SDL_EnableKeyRepeat(500, 10);
}

void Keyboard::disable_key_repeat()
{
	SDL_EnableKeyRepeat(0, 10);
}

void Keyboard::set_key(enum key k, int val) 
{
	m_key_down[k] = val;
}

void Keyboard::set_key(int k, int val) 
{
	set_key((enum key) k, val);
}

void Keyboard::incr_key_down(enum key k)
{
	m_key_down[k]++;
}
void Keyboard::incr_key_down(int k)
{
	incr_key_down((enum key)k);
}


void Keyboard::reset_menu_keys() 
{
	while (is_next_menu_key()) {
		m_menu_input.pop();
	}
}

bool Keyboard::is_next_menu_key() const
{
	return m_menu_input.empty();
}

menu_key Keyboard::pop_menu_key()
{
	menu_key res = m_menu_input.front();
	m_menu_input.pop();
	return res;
}

// Fonction pour aider au debug, n'est pas utile au vrai programme
void display_config()
{
	std::cout << "#k_up# " << SDLK_i << std::endl;
	std::cout << "#k_down# " << SDLK_k << std::endl;
	std::cout << "#k_left# " << SDLK_j << std::endl;
	std::cout << "#k_right# " << SDLK_l << std::endl;
	std::cout << "#k_jump# " << SDLK_q << std::endl;
	std::cout << "#k_fire# " << SDLK_d << std::endl;
	std::cout << "#k_escape# " << SDLK_ESCAPE << std::endl;
	std::cout << "#k_action# " << SDLK_SPACE << std::endl;
	std::cout << "#k_prev_weapon# " << SDLK_a << std::endl;
	std::cout << "#k_next_weapon# " << SDLK_z << std::endl;	
}
