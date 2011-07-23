#include "EventKeyboard.h"
#include "../control/SdlKeyConverter.h"
#include "../control/KeyboardConfig.h"
#include "../util/globals.h"

EventKeyboard::EventKeyboard():
	m_treated(false)
{
	
}

EventKeyboard::EventKeyboard(SDL_Event event):
	m_event(event),
	m_treated(false)
{
	
}

EventKeyboard::~EventKeyboard()
{
	
}

bool EventKeyboard::pollEvent(EventKeyboard *eventKeyboard)
{
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		eventKeyboard->m_event = event;
		return true;
	}
	return false;
}

void EventKeyboard::waitEvent(EventKeyboard *eventKeyboard)
{
	SDL_Event event;
	SDL_WaitEvent(&event);
	eventKeyboard->m_event = event;
}

void EventKeyboard::setKeyRepeat(bool repeat)
{
	SDL_EnableKeyRepeat((repeat ? 500 : 0), 10);
}

bool EventKeyboard::keyLeave() const
{
	return getSDLEvent().type == SDL_QUIT;	
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

bool EventKeyboard::isMenuKey() const
{
	return getMenuKey() != mk_none;
}

menu_key EventKeyboard::getMenuKey() const
{
	switch(m_event.type)
	{
		case SDL_QUIT:
			return mk_exit;
		case SDL_KEYDOWN: /* Si appui d'une touche */
			// priorite aux touches en dur
			switch (m_event.key.keysym.sym)
			{
				case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
					return mk_escape;
					break;
				case SDLK_UP:
					return mk_up;
				case SDLK_DOWN:
					return mk_down;
				case SDLK_LEFT:
					return mk_left;
				case SDLK_RIGHT:
					return mk_right;
				case SDLK_RETURN: case SDLK_KP_ENTER: case SDLK_SPACE:
					return mk_enter;
				default:
					break;
			}
			// sinon on regarde les touches du joueur
			if (gKeyboardConfig) {
				switch (gKeyboardConfig->getEnumKey(*this)) {
					case k_jump: case k_fire:
						return mk_enter;
					case k_up:
						return mk_up;
					case k_down:
						return mk_down;
					case k_right:
						return mk_right;
					case k_left:
						return mk_left;
					default:
						break;
				}
			}
			break;
		default:
			break;
	}
	return mk_none;	
}
