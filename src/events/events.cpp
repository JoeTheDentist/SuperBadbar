#include <iostream>
#include <stdint.h>

#include "events.h"
#include "../util/debug.h"

Event::Event()
{
	PRINT_CONSTR(3, "Construction d'un event");
	m_can_be_destroyed = false;
}

Event::~Event()
{
	
}

void Event::update()
{
	
}

bool Event::can_start()
{
	return false;

}

void Event::start()
{
}

bool Event::can_be_destroyed() 
{
	return m_can_be_destroyed;
}

void Event::destroy()
{
	
}

SDL_Surface *Event::current_picture()
{
	return NULL;
}

SDL_Rect Event::current_pos()
{
	SDL_Rect defaut;
	defaut.x = 0;
	defaut.y = 0;
	defaut.w = 0;
	defaut.h = 0;
	return defaut;
}
