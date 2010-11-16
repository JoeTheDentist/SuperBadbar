#ifndef _EVENTS_MANAGER_
#define _EVENTS_MANAGER_

#include <list>

class Event;
class Dynamic_data;
class Static_data;


class Events_manager {
private:
	Dynamic_data *m_dynamic_data;
	Static_data *m_static_data;
	std::list<Event*> m_list_events;	
public:
	Events_manager();
	~Events_manager();
	void init_events_manager(Static_data *static_data, Dynamic_data *dynamic_data);
	void load_events();
	void update ();
};

#endif
