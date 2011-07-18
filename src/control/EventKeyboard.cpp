#include "EventKeyboard.h"
#include "../control/SdlKeyConverter.h"


EventKeyboard::EventKeyboard(SDL_Event event):
	m_event(event)
{
	
}

EventKeyboard::~EventKeyboard()
{
	
}

bool EventKeyboard::keyPressed() const
{
	return getSDLEvent().type == SDL_KEYDOWN;
}


bool EventKeyboard::keyReleased() const
{
	return getSDLEvent().type == SDL_KEYUP;	
}


SDL_Event EventKeyboard::getSDLEvent() const
{
	return m_event;
}

SDLKey EventKeyboard::getSDLKey() const
{
	return getSDLEvent().key.keysym.sym;
}

std::string EventKeyboard::getKeyString() const
{
	return SdlKeyConverter::sdlkey_to_stdstring(getSDLKey());
}


//~ bool EventKeyboard::isMenuKey() const
//~ {
//~ 	return false; // TODO
//~ }


//~ menu_key EventKeyboard::getMenuKey() const
//~ {
//~ 	
//~ }
