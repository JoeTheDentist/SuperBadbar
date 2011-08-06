/**
 * 	@file trigger.cpp
 * 	@brief implémentation de la classe Triggers
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date avril 2011
 *
 */

#include <iostream>
#include <stdint.h>
#include <sstream>

#include "Trigger.h"
#include "util/debug.h"
#include "util/globals.h"
#include "util/Analyser.h"
#include "util/repertories.h"
#include "actors/Babar.h"
#include "events/Triggerable.h"
#include "players/PlayersManager.h"



Trigger::Trigger(Analyser *analyser):
	m_triggered(false)
{
	initZones(analyser);
	initTriggerables(analyser);
}

Trigger::~Trigger()
{
	for (std::list<Triggerable *>::iterator it = m_triggerables.begin();
			it != m_triggerables.end(); ++it) {
		delete (*it);
	}
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
		if (CollisionsManager::check_collision((*it), gPlayers->local_player()->position())) {
			return true;
		}
	}
	return false;
}

void Trigger::start()
{
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

/*************************************************************/
/*******					PRIVATE					*********/
/*************************************************************/

void Trigger::initZones(Analyser *analyser)
{
	if (analyser->find_next_string("#zone#")) {
		int nb_zone = analyser->read_int();
		for (int i = 0; i < nb_zone; ++i) {
			Rect rec;
			rec.x = analyser->read_int();
			rec.y = analyser->read_int();
			rec.w = analyser->read_int() - rec.x;
			rec.h = analyser->read_int() - rec.y;
			addPos(rec);
		}
	}
}

void Trigger::initTriggerables(Analyser *analyser)
{
	if (analyser->find_next_string("#triggerables#")) {
		int nb_triggerables = analyser->read_int();
		for (int i = 0; i < nb_triggerables; ++i) {
			addTriggerable(new Triggerable(*analyser));
		}
	}
}
