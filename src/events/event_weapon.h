#ifndef _EVENT_WEAPON_
#define _EVENT_WEAPON_

#include "../events/events.h"
#include "../events/event_item.h"
#include "../items/weapons.h"
#include <SDL/SDL.h>

class Pictures_container;
class Babar;
class Weapon;

class Event_weapon: public Event_item{
private:
	weapon_type m_weapon_type;
public:
	Event_weapon(Babar *target, SDL_Rect pos, Pictures_container *pictures_container);
	~Event_weapon();
	void start();
	SDL_Surface *current_picture();
}; 


#endif
