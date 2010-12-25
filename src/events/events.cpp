/**
 * 	@file event.cpp
 * 	@brief implémentation de la classe Events
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>
#include <stdint.h>

#include "events.h"
#include "../util/debug.h"
#include "../util/globals.h"
#include "../video/surface.h"

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

bool Event::can_start() const
{
	return false;

}

void Event::start()
{
}

bool Event::can_be_destroyed() const
{
	return m_can_be_destroyed;
}

void Event::destroy()
{

}

Surface *Event::current_picture() const
{
	return NULL;
}

Rect Event::current_pos() const
{
	Rect defaut;
	defaut.x = 0;
	defaut.y = 0;
	defaut.w = 0;
	defaut.h = 0;
	return defaut;
}
