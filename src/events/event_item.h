#ifndef _EVENT_ITEM_
#define _EVENT_ITEM_

#include "../events/events.h"
#include "../util/globals.h"
class Babar;

class Event_item: public Event{
protected:
	Babar *m_target;
	SDL_Surface *m_picture;
	Rect m_pos;
	int m_phase;
public:
	Event_item(Babar *target, Rect pos);
	~Event_item();
	virtual void update();
	virtual bool can_start();
	virtual void start();
//~ 	virtual bool can_be_destroyed();
//~ 	virtual void destroy();
	virtual SDL_Surface *current_picture();
	virtual Rect current_pos();
};

#endif
