/**
 * 	@file event.cpp
 * 	@brief implémentation de la classe Events
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>
#include <stdint.h>

#include "Event.h"
#include "util/debug.h"
#include "util/globals.h"
#include "util/Analyser.h"
#include "util/repertories.h"
#include "actors/Babar.h"
#include "actors/MonstersManager.h"
#include "items/Weapon.h"
#include "video/Talks.h"
#include "players/PlayersManager.h"

Event::Event(std::string event_name, int x, int y):
	m_can_be_destroyed(false),
	m_picture(NULL),
	m_phase(0),
	m_analyser(new Analyser()),
	m_event_name(event_name)
{
	PRINT_CONSTR(3, "Construction d'un event");
	m_pos.x = x;
	m_pos.y = y;
	m_pos.h = 0;
	m_pos.w = 0;
	m_analyser->open(EVENTS_R + event_name + EVENTS_EXT);
	if (m_analyser->find_string("#picture#")) {
		m_picture = new Surface(PIC_EVENTS_R + m_analyser->read_string());
		m_pos.h = m_picture->h();
		m_pos.w = m_picture->w();
	}
	m_analyser->close();
}

Event::~Event()
{
	if (m_analyser)
		delete m_analyser;
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
	return CollisionsManager::check_collision(m_pos, gPlayers->local_player()->position());
}

void Event::start()
{
	m_analyser->open(EVENTS_R + m_event_name + EVENTS_EXT);
	m_can_be_destroyed = true;
	m_analyser->find_string("#start#");
	std::string action;
	while ((action = m_analyser->read_string()) != "") {
		if (action == "weapon") {
			process_weapon();
		} else if (action == "HPup") {
			process_HPup();
		} else if (action == "playsound") {
			process_playsound();
		} else if (action == "victory") {
			process_victory();
		} else if (action == "peanut") {
			process_peanut();
		} else if (action == "talk") {
			process_dialog();
		} else if (action == "monster") {
			process_monster();
		} else {
			PRINT_DEBUG(1, "action non reconnue dans un fichier event:");
		}
	}
	m_analyser->close();
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
		weapon_type = MACHINE_GUN;
	} else if (weapon_name == "gun") {
		weapon_type = GUN;
	} else if (weapon_name == "rocket_launcher") {
		weapon_type = ROCKET_LAUNCHER;
    } else if (weapon_name == "elmar_machine_gun") {
		weapon_type = ELMAR_MACHINE_GUN;
	} else {
		PRINT_DEBUG(1, "nom d'arme inconnu dans l'event weapon, choix du gun par defaut");
		weapon_type = GUN;
	}
	gPlayers->local_player()->add_weapon(weapon_type);
}

void Event::process_HPup()
{
	gPlayers->local_player()->HPup(m_analyser->read_int());
}

void Event::process_playsound()
{
	gSound->play_sound(SOUNDS_R + m_analyser->read_string());
}

void Event::process_victory()
{
	gGameEngine->set_victory();
}

void Event::process_peanut()
{
	gPlayers->local_player()->incr_peanuts(m_analyser->read_int());
}

void Event::process_dialog()
{
	gGraphics->get_talks()->load_and_display_text(m_analyser->read_string());
}

void Event::process_monster()
{
	std::string monster_name = m_analyser->read_string();
	gGameEngine->get_monsters_manager()->load_monster(monster_name, m_pos.x, m_pos.y);
}
