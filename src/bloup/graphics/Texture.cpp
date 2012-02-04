#include "Texture.h"

#include <iostream>

namespace bloup
{

Texture::Texture():
    Sized()
  , m_texture(0)
{
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_texture);
}

bool Texture::loadFromFile(std::string filename)
{
    QImage b;
    if (!b.load( QString::fromStdString(filename))) {
        return false;
    } else {
        return loadFromQImage(b);
    }
}

bool Texture::loadUniformTexture(const Point2f &size, const Color &color)
{
    QPixmap johnnythedentist(QSize(size.getX(), size.getY()));
    johnnythedentist.fill(QColor(color.getIntR(),
                                 color.getIntG(),
                                 color.getIntB(),
                                 color.getIntAlpha()));
    return loadFromQImage(johnnythedentist.toImage());
}

bool Texture::loadFromQImage(const QImage &image)
{
    QImage t = QGLWidget::convertToGLFormat(image);
    glGenTextures( 1, &m_texture );
    glBindTexture( GL_TEXTURE_2D, m_texture );
    glTexImage2D(GL_TEXTURE_2D, 0, 4, t.width(), t.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    setSize(t.width(), t.height());
    return true;
}



void Texture::glBindMe() const
{
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

} // namespace bloup
