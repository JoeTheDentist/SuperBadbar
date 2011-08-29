#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <utils/Positionned.h>

namespace bloup
{


/*!
*   @class Drawable
*   @brief A drawable entity
*
*   Each drawable entity must inherit Drawable
*/
class Drawable: public Positionned
{
public:
    /*!
      * @brief Default constructor
      */
    Drawable();

    /*!
      * @brief Draws the entity
      *
      * You have to redefine this method
      */
    virtual void draw() const = 0;
};

} // namespace bloup


#endif // DRAWABLE_H
