#ifndef POINT2F_H
#define POINT2F_H


namespace bloup
{

/*!
  * @class Point
  * @brief 2D point
  */
class Point2f
{
public:
    /*!
      * @brief Constructor
      * @param x First coordinate
      * @param y Second coordinate
      */
    Point2f(float x = 0, float y = 0);

    /*!
      * @brief Change the first value
      * @param x The new value
      */
    inline void setX(float x);

    /*!
      * @brief Change the second value
      * @param y The new value
      */
    inline void setY(float y);

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
    inline void set(float x, float y);

    /*!
      * @brief Accessor on the first coordinate
      * @return The first coordinate
      */
    inline float &getX();

    /*!
      * @brief Accessor on the second coordinate
      * @return The second coordinate
      */
    inline float &getY();

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
private:
    float m_x;
    float m_y;
};



void Point2f::setX(float x)
{
    m_x = x;
}

void Point2f::setY(float y)
{
    m_y = y;
}

void Point2f::set(float x, float y)
{
    m_x = x;
    m_y = y;
}

void Point2f::move(float x, float y)
{
    m_x += x;
    m_y += y;
}

void Point2f::move(const Point2f &vector)
{
    m_x += vector.m_x;
    m_y += vector.m_y;
}

float &Point2f::getX()
{
    return m_x;
}

float &Point2f::getY()
{
    return m_y;
}

float Point2f::getX() const
{
    return m_x;
}

float Point2f::getY() const
{
    return m_y;
}

} // namespace bloup

#endif // POINT_H
