#include "InputString.h"
#include "../control/EventKeyboard.h"
#include "../util/debug.h"

InputString::InputString(std::string str):
	m_string(str)
{
	
}

void InputString::treatEvent(const EventKeyboard &event)
{
	if (event.keyPressed()) {
		if (event.backspacePressed()) {
			m_string.resize(m_string.length() - 1);
		} else {
			if (event.hasUnicode())
				m_string += event.unicode();
			PRINT_DEBUG(1, "plop %c", event.unicode());
		}
	}
}
