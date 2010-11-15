#include "events_manager.h"

#include "../events/events.h"
#include "../game/dynamic_data.h"
#include "../game/static_data.h"
#include "../util/debug.h"
#include "../events/event_weapon.h"


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
	m_event = new Event_weapon(m_dynamic_data->babar());
}

void Events_manager::update()
{
	if(m_event->can_start())
		m_event->start();
}
