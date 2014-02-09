#include "InputString.h"

#include <control/EventKeyboard.h>
#include "util/debug.h"

InputString::InputString (std::string str) :
    m_string (str),
    m_itPreviousStrings (0)
{

}

void InputString::treatEvent (const EventKeyboard &event)
{
    if (event.keyPressed() )
    {
        if (event.backspacePressed() )
        {
            if (m_string.length() > 0)
            {
                m_string.resize (m_string.length() - 1);
            }
        }
        else if (event.isUndo() )
        {

        }
        else
        {
            if (event.hasUnicode() )
            {
                m_string += event.unicode();
            }
        }
    }
}

void InputString::setString (std::string str)
{
    m_string = str;
}


void InputString::saveToUndoList()
{
    m_previousStrings.push_back (m_string);
//~ 	m_itPreviousStrings = m_string.length() - 1;
}

void InputString::undo()
{
//~ 	m_string =
}
