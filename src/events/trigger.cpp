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
#include "../events/events.h"

Trigger::Trigger(std::string filename)
{
	PRINT_CONSTR(3, "Construction d'un trigger");
	m_triggered = false;
	Analyser analyser;
	analyser.open(LEVELS_R + filename);
	if (analyser.find_string("#zone#")) {
		int nb_zone = analyser.read_int();
		for (int i = 0; i < nb_zone; ++i) {
			Rect rec;
			rec.x = analyser.read_int();
			rec.y = analyser.read_int();
			rec.w = analyser.read_int();
			rec.h = analyser.read_int();
			addPos(rec);
		}
	}
	if (analyser.find_string("#events#")) {
		int nb_events = analyser.read_int();
		for (int i = 0; i < nb_events; ++i) {
			analyser.read_string(); // on saute le "event"
			std::string eventtype = analyser.read_string();
			int x = analyser.read_int();
			int y = analyser.read_int();
			addEvent(new Event(eventtype, x, y));
		}
	}
	analyser.close();
}

Trigger::~Trigger()
{
	PRINT_CONSTR(3, "Destruction d'un trigger");
}

void Trigger::update()
{
	
	for (std::list<Event*>::iterator curs = m_events.begin(); curs != m_events.end(); ) { 
		(*curs)->update();
		if((*curs)->can_start())
			(*curs)->start();
		if((*curs)->can_be_destroyed()) {
			(*curs)->destroy();
			delete (*curs);
			curs = m_events.erase(curs);
		} else {
			++curs;
		}
	}
}

bool Trigger::can_start() const
{
	if (m_triggered)
		return false;
	for (std::list<Rect>::const_iterator it = m_zone.begin(); it != m_zone.end(); ++it) {
		if (Collisions_manager::check_collision((*it), gBabar->position()))
			return true;
	}
	return false;
}

void Trigger::start()
{
	PRINT_DEBUG(1, "PULL THE TRIGGER");
	m_triggered = true;
	for (std::list<Event*>::iterator it = m_events.begin(); it != m_events.end(); ++it) {
		(*it)->start();
	}
}

bool Trigger::can_be_destroyed() const
{
	return m_triggered && m_events.empty();
	
}

void Trigger::destroy()
{
}

void Trigger::addPos(Rect pos) 
{
	m_zone.push_back(pos);
}

void Trigger::addEvent(Event *event)
{
	m_events.push_back(event);
}
