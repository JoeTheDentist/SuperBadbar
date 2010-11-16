#ifndef _EVENT_WEAPON_
#define _EVENT_WEAPON_

#include "../events/events.h"
#include "../items/weapons.h"
#include <SDL/SDL.h>

class Babar;
class Weapon;

class Event_weapon: public Event{
private:
	Babar *m_target;
	SDL_Surface *m_picture;
	SDL_Rect m_pos;
	weapon_type m_weapon_type;
	bool m_can_be_destroyed;
	int m_phase;
public:
	Event_weapon(Babar *target);
	~Event_weapon();
	void update();
	bool can_start();
	void start();
	bool can_be_destroyed();
	void destroy();
	SDL_Surface *current_picture();
	SDL_Rect current_pos();
}; 



#endif
