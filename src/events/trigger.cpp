/**
 * 	@file trigger.cpp
 * 	@brief implémentation de la classe Triggers
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date avril 2011
 *
 */

#include <iostream>
#include <stdint.h>

#include "trigger.h"
#include "../util/debug.h"
#include "../util/globals.h"
#include "../util/analyser.h"
#include "../util/repertories.h"
#include "../actors/babar.h"
#include "../items/weapons.h"
#include "../video/talks.h"


Trigger::Trigger()
{
	PRINT_CONSTR(3, "Construction d'un trigger");
	m_can_be_destroyed = false;
//~ 	m_analyser = new Analyser();
//~ 	m_analyser->open(EVENTS_R + event_name + EVENTS_EXT);
//~ 	if (m_analyser->find_string("#picture#")) {
//~ 		m_picture = new Surface(PIC_EVENTS_R + m_analyser->read_string());
//~ 		m_pos.h = m_picture->h();
//~ 		m_pos.w = m_picture->w();
//~ 	}
//~ 	m_analyser->close();
}

Trigger::~Trigger()
{
	PRINT_CONSTR(3, "Destruction d'un trigger");
}

void Trigger::update()
{
}

bool Trigger::can_start() const
{
	// TODO
//~ 	return Collisions_manager::check_collision(m_pos, gBabar->position());
	return false;
}

void Trigger::start()
{
	PRINT_DEBUG(1, "PULL THE TRIGGER");
	//TODO
//~ 	m_analyser->open(EVENTS_R + m_event_name + EVENTS_EXT);
//~ 	m_can_be_destroyed = true;
//~ 	m_analyser->find_string("#start#");
//~ 	std::string action;
//~ 	while ((action = m_analyser->read_string()) != "") {
//~ 		if (action == "weapon") {
//~ 			process_weapon();
//~ 		} else if (action == "lifeup") {
//~ 			process_lifeup();
//~ 		} else if (action == "playsound") {
//~ 			process_playsound();
//~ 		} else if (action == "victory") {
//~ 			process_victory();
//~ 		} else if (action == "peanut") {
//~ 			process_peanut();
//~ 		} else if (action == "talk") {
//~ 			process_dialog();
//~ 		} else {
//~ 			PRINT_DEBUG(1, "action non reconnue dans un fichier event:");
//~ 		}
//~ 	}
//~ 	m_analyser->close();
}

bool Trigger::can_be_destroyed() const
{
	return m_can_be_destroyed;
}

void Trigger::destroy()
{
}

