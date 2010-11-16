#include <iostream>
#include <stdint.h>

#include "events.h"


Event::Event()
{
	
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
	return false;
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
