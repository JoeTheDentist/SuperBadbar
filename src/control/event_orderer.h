#ifndef _BABAR_EVENT_ORDERER_H
#define _BABAR_EVENT_ORDERER_H

#include "../../lib/SDL/include/SDL/SDL.h"
#include <string>

class Keyboard;

class Event_orderer {
	
protected:
	SDLKey m_event;
	bool m_event_recieved;
public:
	Event_orderer();
	void order_event(Keyboard *keyboard);
	bool event_recieved();
	void answer_event_order(SDLKey event);
	SDLKey get_event();
	std::string get_string_event();

};

#endif
