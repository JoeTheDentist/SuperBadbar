#ifndef _EVENT_WEAPON_
#define _EVENT_WEAPON_

#include "../events/events.h"
#include <SDL/SDL.h>

class Babar;
class Weapon;

class Event_weapon: public Event{
private:
	Babar *m_target;
//~ 	SDL_Surface *m_picture;
	SDL_Rect m_pos;
	weapon_type m_weapon_type;
public:
	Event_weapon(Babar *target);
	~Event_weapon();
	bool can_start();
	void start();

}; 



#endif
