#ifndef TEXTURE_H
#define TEXTURE_H

#include <QGLWidget>
#include <string>
#include <utils/Sized.h>
#include <utils/Color.h>

namespace bloup
{

class Texture: public Sized
{
public:
    /*!
      * @brief Default constructor
      */
    Texture();

    /*!
      * @brief Destructor
      */
    ~Texture();

    /*!
      * @brief Loads the texture from filename
      * @param filename The path to a picture file
      * @return true if success, false if fail
      */
    bool loadFromFile(std::string filename);

    /*!
      * @brief Loads a uniform texture
      * @param size Texture's size
      * @param color Texture's color
      * @return true if success, false if fail
      */
    bool loadUniformTexture(const Point2f &size, const Color &color);

    /*!
      * @brief Load a texture from a QImage
      * @param image
      * @return true if success, false if fail
      */
    bool loadFromQImage(const QImage &image);

    /*!
      * @brief Call glBindTexture with GL_TEXTURE2D
      *
      * Used by BloupEngine, you shouldn't need that
      */
    void glBindMe() const;

private:
    GLuint m_texture;
};

} // namespace bloup

#endif // TEXTURE_H
