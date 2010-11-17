#include "events_manager.h"

#include "../events/events.h"
#include "../game/dynamic_data.h"
#include "../game/static_data.h"
#include "../util/debug.h"
#include "../events/event_weapon.h"
#include "../video/camera.h"


Events_manager::Events_manager()
{
	PRINT_CONSTR(1, "Construction de Events_manager") 
}

Events_manager::~Events_manager()
{
	PRINT_CONSTR(1, "Destruction de Events_manager") 
}

void Events_manager::init_events_manager(Static_data *static_data, Dynamic_data *dynamic_data)
{
	PRINT_TRACE(1, "Initilisation de Events_manager")
	m_dynamic_data = dynamic_data;
	m_static_data = static_data;
}

void Events_manager::load_events()
{
	PRINT_TRACE(1, "Chargement des evenements");
	Event *event = new Event_weapon(m_dynamic_data->babar());
	m_list_events.push_back(event);	
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

void Events_manager::display_events(Camera *camera)
{
	std::list<Event*>::iterator curs;
	for (curs = m_list_events.begin(); curs != m_list_events.end(); curs++) {
		camera->display_event(*curs);
	}
}


