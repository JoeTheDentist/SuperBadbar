/**
 * 	@file event.cpp
 * 	@brief implémentation de la classe Events
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>
#include <stdint.h>

#include "events.h"
#include "../util/debug.h"
#include "../util/globals.h"
#include "../util/analyser.h"
#include "../util/repertories.h"
#include "../sprites/babar.h"
#include "../items/weapons.h"
#include "../video/talks.h"


Event::Event(std::string event_name, int x, int y):
	m_phase(0)
{
	PRINT_CONSTR(3, "Construction d'un event");
	m_can_be_destroyed = false;
	m_pos.x = x;
	m_pos.y = y;
	m_analyser = new Analyser();
	m_analyser->open(EVENTS_R + event_name + EVENTS_EXT);
	if (m_analyser->find_string("#picture#")) {
		m_picture = new Surface(PIC_EVENTS_R + m_analyser->read_string());
		m_pos.h = m_picture->h();
		m_pos.w = m_picture->w();
	}
}

Event::~Event()
{
	if (m_analyser) {
		m_analyser->close();
		delete m_analyser;
		m_analyser = NULL;
	}
	if (m_picture) 
		delete m_picture;
}

void Event::update()
{
	m_phase++;
	if ((m_phase/5)%2)
		m_pos.y += 5;
	else
		m_pos.y -= 5;
}

bool Event::can_start() const
{
	return Collisions_manager::check_collision(m_pos, gBabar->position());
}

void Event::start()
{
	m_can_be_destroyed = true;
	m_analyser->find_string("#start#");
	std::string action;
	while ((action = m_analyser->read_string()) != "") {
		if (action == "weapon") {
			process_weapon();
		} else if (action == "lifeup") {
			process_lifeup();
		} else if (action == "playsound") {
			process_playsound();
		} else if (action == "victory") {
			process_victory();
		} else if (action == "peanut") {
			process_peanut();
		} else if (action == "talk") {
			process_dialog();
		} else {
			PRINT_DEBUG(1, "action non reconnue dans un fichier event:");
		}
	}
}

bool Event::can_be_destroyed() const
{
	return m_can_be_destroyed;
}

void Event::destroy()
{

}

Surface *Event::current_picture() const
{
	return m_picture;
}

Rect Event::current_pos() const
{
	return m_pos;
}

void Event::process_weapon() 
{
	std::string weapon_name = m_analyser->read_string();
	weapon_type weapon_type;
	if (weapon_name == "shotgun") {
		weapon_type = SHOTGUN;
	} else if (weapon_name == "machinegun"){
		weapon_type = MACHINEGUN;
	} else if (weapon_name == "gun") {
		weapon_type = GUN;
	} else {
		PRINT_DEBUG(1, "nom d'arme inconnu dans l'event weapon, choix du gun par defaut");
		weapon_type = GUN;
	}
	gBabar->add_weapon(weapon_type);
}

void Event::process_lifeup()
{
	gBabar->lifeup(m_analyser->read_int());
}

void Event::process_playsound()
{
	gSound->play_sound(SOUNDS_R + m_analyser->read_string());
}

void Event::process_victory()
{
	gGame_engine->set_victory();
}

void Event::process_peanut()
{
	gBabar->incr_peanuts(m_analyser->read_int());
}

void Event::process_dialog()
{
	std::cout << "plop" << std::endl;
	gGraphics->get_talks()->load_and_display_text(m_analyser->read_string());
}
