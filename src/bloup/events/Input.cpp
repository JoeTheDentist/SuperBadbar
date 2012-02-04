#include "Input.h"

namespace bloup
{


Input::Input(type eventType, std::string str, int key):
    m_type(eventType)
  , m_string(str)
  , m_key(key)
{
}


Input::type Input::getType() const
{
    return m_type;
}

std::string Input::getString() const
{
    return m_string;
}

int Input::getKey() const
{
    return m_key;
}

} // namespace bloup
