#ifndef SIZED_H
#define SIZED_H

#include <utils/Point2f.h>

namespace bloup
{

/*!
  * @class Sized
  * @brief Inheritied by sized items
  */
class Sized
{
public:
    /*!
      * @brief Constructor
      * @param w width
      * @param h height
      */
    Sized(float w = 0, float h = 0);

    /*!
      * @brief Constructor
      * @param point The size
      */
    Sized(const Point2f &point);

    /*!
      * @brief Change the size
      * @param w Width
      * @param h Height
      */
    inline void setSize(float w, float h);

    /*!
      * @brief Change the size
      * @param size The new size
      */
    inline void setSize(Point2f size);


    /*!
      * @brief Accessor on the width
      * @return The width
      */
    inline float getW() const;

    /*!
      * @brief Accessor on the height
      * @return The height
      */
    inline float getH() const;

    /*!
      * @Brief Accessor on the size
      * @return The size
      */
    inline Point2f getSize() const;

private:
    Point2f m_size;
};


void Sized::setSize(float w, float h)
{
    m_size.set(w, h);
}

void Sized::setSize(Point2f size)
{
    m_size = size;
}

float Sized::getW() const
{
    return m_size.getX();
}

float Sized::getH() const
{
    return m_size.getY();
}

Point2f Sized::getSize() const
{
    return m_size;
}

} // namespace bloup

#endif // SIZED_H
