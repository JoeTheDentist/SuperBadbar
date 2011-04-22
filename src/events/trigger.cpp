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
#include "../events/triggerable.h"

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
	if (analyser.find_string("#triggerables#")) {
		int nb_triggerables = analyser.read_int();
		for (int i = 0; i < nb_triggerables; ++i) {
			PRINT_DEBUG(1, "YEAH");
			addTriggerable(new Triggerable(analyser));
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
	for (std::list<Triggerable *>::iterator it = m_triggerables.begin(); it != m_triggerables.end(); ++it) {
		(*it)->start();
	}
}

bool Trigger::can_be_destroyed() const
{
	return m_triggered;
	
}

void Trigger::destroy()
{
}

void Trigger::addPos(Rect pos) 
{
	m_zone.push_back(pos);
}

void Trigger::addTriggerable(Triggerable *triggerable)
{
	m_triggerables.push_back(triggerable);
}
