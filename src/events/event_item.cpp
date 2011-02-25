/**
 * 	@file event_item.h
 * 	@brief implémentation de la classe Event_item
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>

#include "event_item.h"
#include "../sprites/babar.h"
#include "../game/collisions_manager.h"
#include "../util/debug.h"
#include "../video/surface.h"
#include "../util/globals.h"

Event_item::Event_item()
{
}

Event_item::Event_item(Babar *target, Rect pos) : Contact_event(target, pos)
{

}

Event_item::~Event_item()
{
	PRINT_CONSTR(3, "DESTRUCTION D'UN EVENT ITEM");
}
