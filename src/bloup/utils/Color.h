#ifndef COLOR_H
#define COLOR_H

namespace bloup
{


/*!
  * @class Color
  * @brief Represents a RGBA color
  *
  * Values are from 0 to 1
  *
  * Alpha channel is 0 for full transparency
  * and 1 for full opacity
  */
class Color
{
public:
    /*!
      * @brief Constructor
      * @param r Red composant
      * @param g Green composant
      * @param b Blue composant
      * @param alpha Alpha composant
      */
    Color(float r = 0, float g = 0, float b = 0, float alpha = 1);

    /*!
      * brief Change the color values
      * @param r Red composant
      * @param g Green composant
      * @param b Blue composant
      */
    inline void set(float r, float g, float b);

    /*!
      * brief Change the color values
      * @param r Red composant
      * @param g Green composant
      * @param b Blue composant
      * @param alpha Alpha composant
      */
    inline void set(float r, float g, float b, float alpha);

    /*!
      * @brief Change the alpha value
      * @param alpha
      */
    inline void setAlpha(float alpha);

    /*!
      * @brief Accessor on the red composant
      * @return The red composant
      */
    inline float getR() const;

    /*!
      * @brief Accessor on the green composant
      * @return The green composant
      */
    inline float getG() const;

    /*!
      * @brief Accessor on the blue composant
      * @return The blue composant
      */
    inline float getB() const;

    /*!
      * @brief Accessor on the alpha composant
      * @return The alpha composant
      */
    inline float getAlpha() const;

    /*!
      * @brief Accessor on the red composant
      * @return The red composant between 0 and 255
      */
    inline int getIntR() const;

    inline int getIntG() const;

    inline int getIntB() const;

    inline int getIntAlpha() const;



private:
    float m_color[4]; // R G B A
};


void Color::set(float r, float g, float b)
{
    m_color[0] = r;
    m_color[1] = g;
    m_color[2] = b;
}

void Color::set(float r, float g, float b, float alpha)
{
    set(r, g, b);
    setAlpha(alpha);
}

void Color::setAlpha(float alpha)
{
    m_color[3] = alpha;
}

float Color::getR() const
{
    return m_color[0];
}

float Color::getG() const
{
    return m_color[1];
}

float Color::getB() const
{
    return m_color[2];
}

float Color::getAlpha() const
{
    return m_color[3];
}

int Color::getIntR() const
{
    return getR() * 255;
}

int Color::getIntG() const
{
    return getG() * 255;
}

int Color::getIntB() const
{
    return getB() * 255;
}

int Color::getIntAlpha() const
{
    return getAlpha() * 255;
}


} // namespace bloup

#endif // COLOR_H
