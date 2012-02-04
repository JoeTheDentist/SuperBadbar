#ifndef SIZEDDRAWABLE_H
#define SIZEDDRAWABLE_H

#include <graphics/Drawable.h>
#include <utils/Sized.h>

namespace bloup
{

class SizedDrawable : public Drawable, public Sized
{
public:
    /*!
      * @brief Constructor
      * @param w Width
      * @param h Height
      */
    SizedDrawable(float w = 0, float h = 0);

    /*!
      * @brief Constructor
      * @param size
      */
    SizedDrawable(Point2f size);



    /*!
      * @brief Accessor
      * @return The drawable's size
      */
    inline Point2f getSize() const;

};

} // namespace bloup

#endif // SIZEDDRAWABLE_H
