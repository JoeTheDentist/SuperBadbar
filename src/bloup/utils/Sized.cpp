#include "Sized.h"

namespace bloup
{

Sized::Sized(float w, float h):
    m_size(w, h)
{

}


Sized::Sized(const Point2f &point):
    m_size(point)
{

}


} // namespace bloup
