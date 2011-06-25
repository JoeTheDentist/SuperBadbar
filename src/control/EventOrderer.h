#ifndef _BABAR_EventOrderer_H
#define _BABAR_EventOrderer_H

#include "../../lib/SDL/include/SDL/SDL.h"
#include <string>

class Keyboard;

class EventOrderer {

protected:
	SDLKey m_event;
	bool m_event_recieved;
public:
	EventOrderer();
	void order_event(Keyboard *keyboard);
	bool event_recieved();
	void answer_event_order(SDLKey event);
	SDLKey get_event();
	std::string get_string_event();

};

#endif
