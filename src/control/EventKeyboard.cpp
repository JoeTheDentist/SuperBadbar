#include "EventKeyboard.h"

#include <control/KeyboardConfig.h>
#include <video/Camera.h>
#include "util/utils.h"
#include "util/globals.h"

sf::Window *EventKeyboard::m_window = NULL;

/************************************************/
/*				PUBLIC METHODS				*/
/************************************************/

EventKeyboard::EventKeyboard():
	m_treated(false)
{
	initMode();
}

EventKeyboard::EventKeyboard(const EventKeyboard &eventKeyboard):
	m_event(eventKeyboard.m_event),
	m_treated(eventKeyboard.m_treated),
	m_ctrl(eventKeyboard.m_ctrl),
	m_altGr(eventKeyboard.m_altGr),
	m_capsLockOn(eventKeyboard.m_capsLockOn),
	m_shift(eventKeyboard.m_shift)
{
}

EventKeyboard::EventKeyboard(sf::Event event):
	m_event(event),
	m_treated(false)

{
	initMode();
}

EventKeyboard::~EventKeyboard()
{

}

bool EventKeyboard::pollEvent(EventKeyboard *eventKeyboard)
{
	sf::Event event;
	if (m_window->GetEvent(event)) {
		eventKeyboard->m_event = event;
		return true;
	}
	return false;
}

void EventKeyboard::waitEvent(EventKeyboard *eventKeyboard)
{
	sf::Event event;
	while (!m_window->GetEvent(event)) 
		{}
	eventKeyboard->m_event = event;
}

void EventKeyboard::setKeyRepeat(bool repeat)
{
	m_window->EnableKeyRepeat(repeat);
}

bool EventKeyboard::keyLeave() const
{
	return getSFMLEvent().Type == sf::Event::Closed;
}

bool EventKeyboard::keyPressed() const
{
	return getSFMLEvent().Type == sf::Event::KeyPressed;
}

bool EventKeyboard::keyReleased() const
{
	return getSFMLEvent().Type == sf::Event::KeyReleased;
}

sf::Event EventKeyboard::getSFMLEvent() const
{
	return m_event;
}

std::string EventKeyboard::getKeyString() const
{
	std::string res;
	res += (char)(getSFMLEvent().Text.Unicode);
	return res;
}

bool EventKeyboard::isMenuKey() const
{
	return getMenuKey() != mk_none;
}

menu_key EventKeyboard::getMenuKey() const
{
	if (keyLeave())
		return mk_exit;
	if (keyPressed()) {
		// priorite aux touches en dur
		switch(getSFMLEvent().Key.Code) {
		case sf::Key::Escape: /* Appui sur la touche Echap, on arrête le programme */
			return mk_escape;
			break;
		case sf::Key::Up:
			return mk_up;
		case sf::Key::Down:
			return mk_down;
		case sf::Key::Left:
			return mk_left;
		case sf::Key::Right:
			return mk_right;
		case sf::Key::Return: case sf::Key::Space:
			return mk_enter;
		default:
			break;
		}
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
	}
	return mk_none;
}

bool EventKeyboard::enterPressed() const
{
	return getSFMLEvent().Key.Code == sf::Key::Return;
}

bool EventKeyboard::enterMenuPressed() const
{
	return mk_enter == getMenuKey();
}

bool EventKeyboard::backspacePressed() const
{
	return getSFMLEvent().Key.Code == sf::Key::Space;
}

char EventKeyboard::unicode() const
{
	return char(getSFMLEvent().Text.Unicode);
}

bool EventKeyboard::hasUnicode() const
{
	return true;
}

bool EventKeyboard::isUndo() const
{
	return keyPressed() && m_ctrl && getSFMLEvent().Key.Code == sf::Key::Z;
}

void EventKeyboard::initEventKeyboard()
{
	m_window = gGraphics->get_camera()->getWindow();
}

/************************************************/
/*				PROTECTED METHODS				*/
/************************************************/

void EventKeyboard::initMode()
{
	m_ctrl =  getSFMLEvent().Key.Control;
	m_altGr =  getSFMLEvent().Key.Alt;
	// todo
	m_capsLockOn = getSFMLEvent().Key.Shift;
	m_shift = getSFMLEvent().Key.Shift;
}

