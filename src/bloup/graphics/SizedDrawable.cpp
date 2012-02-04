#include "SizedDrawable.h"

namespace bloup
{

SizedDrawable::SizedDrawable(float w, float h):
    Drawable()
  , Sized(w, h)
{
}

SizedDrawable::SizedDrawable(Point2f size):
    Drawable()
  , Sized(size)
{

}




} // namespace bloup
