

#ifndef _EVENTS_
#define _EVENTS_

#include <SDL/SDL.h>


class Event {
private:
	

public:
	Event();
	~Event();
	virtual void update();
	virtual bool can_start();
	virtual void start();
	virtual bool can_be_destroyed();
	virtual void destroy();
	virtual SDL_Surface *current_picture();
	virtual SDL_Rect current_pos();
};


#endif
