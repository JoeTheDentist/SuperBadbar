
#include "event_orderer.h"
#include "../control/keyboard.h"
#include "../control/sdl_key_converter.h"

Event_orderer::Event_orderer():
	m_event_recieved(false)
{
	
}

void Event_orderer::order_event(Keyboard *keyboard)
{
	m_event_recieved = false;
	keyboard->order_event(this);
}

bool Event_orderer::event_recieved()
{
	return m_event_recieved;
}

void Event_orderer::answer_event_order(SDLKey event)
{
	m_event = event;
	m_event_recieved = true;
}


SDLKey Event_orderer::get_event()
{
	return m_event;
}

std::string Event_orderer::get_string_event()
{
	return Sdl_key_converter::sdlkey_to_stdstring(m_event);
}
