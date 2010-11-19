#include <iostream>

#include "event_item.h"
#include "../sprites/babar.h"
#include "../util/collisions.h"
#include "../util/debug.h"
#include "../util/globals.h"




Event_item::Event_item(Babar *target, SDL_Rect pos) : m_pos(pos)
{
	PRINT_CONSTR(3, "CONSTRUCTION D'UN EVENT ITEM");
	m_target = target;
	m_can_be_destroyed = false;
	m_phase = 0;
}

Event_item::~Event_item()
{
	PRINT_CONSTR(3, "DESTRUCTION D'UN EVENT ITEM");	
}

void Event_item::update()
{
	m_phase++;
	if ((m_phase/5)%2)
		m_pos.y += 5;
	else
		m_pos.y -= 5;
}

bool Event_item::can_start()
{
	return check_collision(m_pos, m_target->position());
}

void Event_item::start()
{
	m_can_be_destroyed = true;
}

//~ bool Event_item::can_be_destroyed()
//~ {
//~ 	return m_can_be_destroyed;
//~ }

//~ void Event_item::destroy()
//~ {
//~ 	
//~ }

SDL_Surface *Event_item::current_picture()
{
	return NULL;
}

SDL_Rect Event_item::current_pos()
{
	return m_pos;
}
