/**
 * 	@file events_manager.cpp
 * 	@brief implémentation de la classe Events_manager
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
 
 #include "events_manager.h"

#include "../events/events.h"
#include "../game/game_engine.h"
#include "../game/static_data.h"
#include "../util/debug.h"
#include "../util/analyser.h"
#include "../events/event_weapon.h"
#include "../events/event_item.h"
#include "../events/events.h"
#include "../video/camera.h"
#include "../sprites/babar.h"
#include "../video/pictures_container.h"


Events_manager::Events_manager()
{
	PRINT_CONSTR(1, "Construction de Events_manager")
}

Events_manager::~Events_manager()
{
	PRINT_CONSTR(1, "Destruction de Events_manager")
	std::list<Event*>::iterator curs;
	for (curs = m_list_events.begin(); curs != m_list_events.end(); curs++ ) {
		delete (Event*)(*curs);
	}
}

void Events_manager::init_events_manager(Static_data *static_data, Game_engine *game_engine, Pictures_container *pictures_container)
{
	PRINT_TRACE(1, "Initialisation de Events_manager")
	m_game_engine = game_engine;
	m_static_data = static_data;
	m_pictures_container = pictures_container;
}

void Events_manager::load_events(Analyser *analyser)
{
	PRINT_TRACE(1, "Chargement des evenements");
	analyser->find_string("#Events#");
	int events_number = analyser->read_int();
	for (int i = 0; i < events_number; i++) {
		std::string event_class = analyser->read_string(); 
		if (event_class == "event_weapon") {
			Event_weapon *event = new Event_weapon(m_game_engine->babar(), m_pictures_container, analyser);
			m_list_events.push_back(event);
		} else {
			PRINT_DEBUG(1, "Event %s non reconnu", event_class.c_str());
		}
	}
}

void Events_manager::update()
{
	std::list<Event*>::iterator curs;
	for (curs = m_list_events.begin(); curs != m_list_events.end(); ) { // si on met le curs++ dans la boucle, on a un pb de curs après erase!
		(*curs)->update();
		if((*curs)->can_start())
			(*curs)->start();
		if((*curs)->can_be_destroyed()) {
			(*curs)->destroy();
			m_list_events.erase(curs++);
		} else {
			curs++;
		}
	}
}

void Events_manager::display_events(Camera *const camera) 
{
	std::list<Event*>::iterator curs;
	for (curs = m_list_events.begin(); curs != m_list_events.end(); curs++) {
		camera->display_event(*curs);
	}
}


