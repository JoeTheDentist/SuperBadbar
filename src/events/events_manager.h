#ifndef _EVENTS_MANAGER_
#define _EVENTS_MANAGER_

#include <list>

class Event;
class Game_engine;
class Static_data;
class Camera;
class Pictures_container;

class Events_manager {
private:
	std::list<Event*> m_list_events;	
	
	Game_engine *m_game_engine;
	Static_data *m_static_data;
	Pictures_container *m_pictures_container;
public:
	Events_manager();
	~Events_manager();
	void init_events_manager(Static_data *static_data, Game_engine *game_engine);
	void load_events();
	void update();
	void display_events(Camera *camera);

};

#endif
