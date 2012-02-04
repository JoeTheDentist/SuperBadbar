#ifndef PICTURE_H
#define PICTURE_H

#include <graphics/SizedDrawable.h>
#include <graphics/Texture.h>

namespace bloup
{

class Picture : public SizedDrawable
{
public:
    /*!
      * @brief Default constructor
      */
    Picture();

    /*!
      * @brief Set the picture's texture
      * @param texture The texture
      *
      * setTexture is very quick, because the texture's buffer
      * is not copied. Howewer, you have to make the paramater
      * texture stay alive as long as you want to display the picture
      */
    inline void setTexture(Texture &texture);

    /*!
      * @brief Draws the entity
      */
    virtual void draw() const;

private:
    Texture *m_texture;
    float m_zBuffer;
    bool m_enableAlpha;
};

void Picture::setTexture(Texture &texture)
{
    m_texture = &texture;
    setSize(texture.getSize());
}


} // namespace bloup

#endif // PICTURE_H
