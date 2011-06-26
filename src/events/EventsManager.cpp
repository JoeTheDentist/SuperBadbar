/**
 * 	@file EventsManager.cpp
 * 	@brief implémentation de la classe EventsManager
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

 #include "EventsManager.h"
#include "../events/Trigger.h"
#include "../events/Event.h"
#include "../game/GameEngine.h"
#include "../game/StaticData.h"
#include "../util/debug.h"
#include "../util/Analyser.h"
#include "../events/Event.h"
#include "../video/Camera.h"
#include "../actors/Babar.h"
#include "../video/PicturesContainer.h"
#include <sstream>


EventsManager::EventsManager()
{
	PRINT_CONSTR(1, "Construction de EventsManager")
}

EventsManager::~EventsManager()
{
	PRINT_CONSTR(1, "Destruction de EventsManager")
	std::list<Event*>::iterator curs;
	std::list<Trigger*>::iterator curs2;
	for (curs = m_list_events.begin(); curs != m_list_events.end(); curs++ ) {
		delete (*curs);
	}
	for (curs2 = m_list_triggers.begin(); curs2 != m_list_triggers.end(); curs2++ ) {
		delete (*curs2);
	}

}

void EventsManager::init_EventsManager(StaticData *StaticData, GameEngine *GameEngine, PicturesContainer *PicturesContainer)
{
	PRINT_TRACE(1, "Initialisation de EventsManager")
	m_GameEngine = GameEngine;
	m_StaticData = StaticData;
	m_pictures_container = PicturesContainer;
	m_level_name = StaticData->level_name();
	std::cout << "LEVEL NAME " << m_level_name << std::endl;
}

void EventsManager::load_events(Analyser *analyser)
{
	PRINT_TRACE(1, "Chargement des evenements");
	int x, y;
	analyser->find_string("#Events#");
	int events_number = analyser->read_int();
	for (int i = 0; i < events_number; i++) {
		std::string event_class = analyser->read_string();
		if (event_class == "event") {
			std::string event_name = analyser->read_string();
			x = analyser->read_int();
			y = analyser->read_int();
			Event *event = new Event(event_name, x, y);
			m_list_events.push_back(event);
		} else {
			PRINT_DEBUG(1, "Event %s non reconnu", event_class.c_str());
		}
	}
}

void EventsManager::load_triggers(Analyser *analyser)
{
	PRINT_TRACE(1, "Chargement des triggers");
	if (!analyser->find_string("#Triggers#"))
		return;
	int triggers_number = analyser->read_int();
	for (int i = 0; i < triggers_number; i++) {
//~ 		analyser->push_curs();
		analyser->find_next_string("#trig#");
		m_list_triggers.push_back(new Trigger(analyser));
//~ 		analyser->pop_curs();
	}
}

void EventsManager::update()
{
	std::list<Event*>::iterator curs;
	std::list<Trigger*>::iterator curs2;
	for (curs = m_list_events.begin(); curs != m_list_events.end(); ) { // si on met le curs++ dans la boucle, on a un pb de curs après erase!
		(*curs)->update();
		if((*curs)->can_start())
			(*curs)->start();
		if((*curs)->can_be_destroyed()) {
			(*curs)->destroy();
			delete (*curs);
			curs = m_list_events.erase(curs);
		} else {
			++curs;
		}
	}
	for (curs2 = m_list_triggers.begin(); curs2 != m_list_triggers.end(); ) { // si on met le curs++ dans la boucle, on a un pb de curs après erase!
		(*curs2)->update();
		if((*curs2)->can_start())
			(*curs2)->start();
		if((*curs2)->can_be_destroyed()) {
			(*curs2)->destroy();
			delete (*curs2);
			curs2 = m_list_triggers.erase(curs2);
		} else {
			++curs2;
		}
	}
}

void EventsManager::display_events(Camera const * camera)
{
	std::list<Event*>::iterator curs;
	for (curs = m_list_events.begin(); curs != m_list_events.end(); curs++) {
		camera->display_event(*curs);
	}
}

void EventsManager::add_end_level(int x, int y)
{
	Event *event = new Event("victory", x, y);
	m_list_events.push_back(event);
}
