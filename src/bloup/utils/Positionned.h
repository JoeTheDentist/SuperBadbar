#ifndef POSITIONNED_H
#define POSITIONNED_H

#include <utils/Point2f.h>

namespace bloup
{

/*!
  * @class Positionned
  * @brief Inherited by entities which have a position
  */
class Positionned
{
public:
    /*!
      * @brief Constructor
      * @param x
      * @param y
      */
    Positionned(float x = 0, float y = 0);

    /*!
      * @brief Constructor
      * @param position
      */
    Positionned(const Point2f &point);

    /*!
      * @brief Increments the current coordinates
      * @param x The first value
      * @param y The second value
      */
    inline void move(float x, float y);

    /*!
      * @brief Increments the current coordinates
      * @param vector
      */
    inline void move(const Point2f &vector);



    /*!
      * @brief Change both coordinate
      * @param x The first value
      * @param y The second value
      */
    inline void setPosition(float x, float y);

    /*!
      * @brief Accessor on the first coordinate
      * @return The first coordinate
      */
    inline float getX() const;

    /*!
      * @brief Accessor on the second coordinate
      * @return The second coordinate
      */
    inline float getY() const;

    /*!
      * @brief Accessor on the position
      * @return The position
      */
    inline Point2f getPosition() const;


private:
    Point2f m_position;
};


void Positionned::move(float x, float y)
{
    m_position.move(x, y);
}

void Positionned::move(const Point2f &vector)
{
    m_position.move(vector);
}



void Positionned::setPosition(float x, float y)
{
    m_position.set(x, y);
}

float Positionned::getX() const
{
    return m_position.getX();
}

float Positionned::getY() const
{
    return m_position.getY();
}

Point2f Positionned::getPosition() const
{
    return m_position;
}



} // namespace bloup

#endif // POSITIONNED_H
