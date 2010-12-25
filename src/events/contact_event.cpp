/**
 * 	@file contact_event.h
 * 	@brief implémentation de la classe Contact_event
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>

#include "contact_event.h"
#include "../sprites/babar.h"
#include "../game/collisions_manager.h"
#include "../util/debug.h"
#include "../util/globals.h"
#include "../video/surface.h"



Contact_event::Contact_event()
{
	PRINT_CONSTR(3, "CONSTRUCTION D'UN CONTACT EVENT");
	m_can_be_destroyed = false;
	m_phase = 0;
}


Contact_event::Contact_event(Babar *target, Rect pos) : m_pos(pos)
{
	PRINT_CONSTR(3, "CONSTRUCTION D'UN CONTACT EVENT");
	m_target = target;
	m_can_be_destroyed = false;
	m_phase = 0;
}

Contact_event::~Contact_event()
{
	PRINT_CONSTR(3, "DESTRUCTION D'UN CONTACT EVENT ");
}

void Contact_event::update()
{
	m_phase++;
	if ((m_phase/5)%2)
		m_pos.y += 5;
	else
		m_pos.y -= 5;
}

bool Contact_event::can_start() const
{
	return Collisions_manager::check_collision(m_pos, m_target->position());
}

void Contact_event::start()
{
	m_can_be_destroyed = true;
}

Surface *Contact_event::current_picture() const
{
	PRINT_DEBUG(1, "CONTACT");
	return NULL;
}

Rect Contact_event::current_pos() const
{
	return m_pos;
}
