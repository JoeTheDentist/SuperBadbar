
#include "EventOrderer.h"
#include "../control/Keyboard.h"
#include "../control/SdlKeyConverter.h"

EventOrderer::EventOrderer():
	m_event_recieved(false)
{

}

void EventOrderer::order_event(Keyboard *keyboard)
{
	m_event_recieved = false;
	keyboard->order_event(this);
}

bool EventOrderer::event_recieved()
{
	return m_event_recieved;
}

void EventOrderer::answer_event_order(SDLKey event)
{
	m_event = event;
	m_event_recieved = true;
}


SDLKey EventOrderer::get_event()
{
	return m_event;
}

std::string EventOrderer::get_string_event()
{
	return SdlKeyConverter::sdlkey_to_stdstring(m_event);
}
