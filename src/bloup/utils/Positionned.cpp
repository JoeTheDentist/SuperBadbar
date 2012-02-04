#include "Positionned.h"

namespace bloup
{


Positionned::Positionned(float x, float y):
    m_position(x, y)
{
}

Positionned::Positionned(const Point2f &position):
    m_position(position)
{
}


} // namespace bloup
