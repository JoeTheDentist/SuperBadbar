#include "Text.h"

#include <cmath>
#include <iostream>
#include <QtCore/QHash>
#include <QtCore/QSysInfo>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>
#include <QtOpenGL/QGLFormat>
#include <QtOpenGL/QGLFramebufferObject>

#include <utils/Color.h>

namespace bloup
{
    const int TEXTURE_SIZE = 256;

    struct CharData
    {
        GLuint textureId;
        uint width;
        uint height;
        GLfloat s[2];
        GLfloat t[2];
    };




struct TextPrivate
{
    TextPrivate(const QFont &f, const bloup::Color &color);
    ~TextPrivate();

    void allocateTexture();
    void createCharacter(QChar c);
    CharData getCharacter(QChar c) const;

    QFont font;
    QFontMetrics fontMetrics;


    QHash<ushort, CharData> m_characters;
    QList<GLuint> m_textures;

    GLint xOffset;
    GLint yOffset;
    bloup::Point2f m_size;

    QColor m_color;

};

TextPrivate::TextPrivate(const QFont &f, const bloup::Color &color)
    : font(f), fontMetrics(f), xOffset(0), yOffset(0),
      m_color(color.getIntR(), color.getIntG(), color.getIntB(), color.getIntAlpha())
{
}

TextPrivate::~TextPrivate()
{
    foreach (GLuint texture, m_textures)
        glDeleteTextures(1, &texture);
}

void TextPrivate::allocateTexture()
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    QImage image(TEXTURE_SIZE, TEXTURE_SIZE, QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    image = QGLWidget::convertToGLFormat(image);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, TEXTURE_SIZE, TEXTURE_SIZE,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    m_textures += texture;
}

CharData TextPrivate::getCharacter(QChar c) const
{
    return m_characters[c.unicode()];
}

void TextPrivate::createCharacter(QChar c)
{
    ushort unicodeC = c.unicode();
    if (m_characters.contains(unicodeC))
        return;
    if (m_textures.empty())
        allocateTexture();

    GLuint texture = m_textures.last();

    GLsizei width = fontMetrics.width(c);
    GLsizei height = fontMetrics.height();

    QPixmap pixmap(width, height);
    pixmap.fill(Qt::transparent);
    QPainter painter;
    painter.begin(&pixmap);

    painter.setFont(font);
    painter.setPen(m_color);

    painter.drawText(0, fontMetrics.ascent(), c);
    painter.end();

    QImage image = QGLWidget::convertToGLFormat(pixmap.toImage());
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexSubImage2D(GL_TEXTURE_2D, 0, xOffset, yOffset, width, height, GL_RGBA,
                    GL_UNSIGNED_BYTE, image.bits());

    CharData& character = m_characters[unicodeC];
    character.textureId = texture;
    character.width = width;
    character.height = height;
    character.s[0] = static_cast<GLfloat>(xOffset) / TEXTURE_SIZE;
    character.t[0] = static_cast<GLfloat>(yOffset) / TEXTURE_SIZE;
    character.s[1] = static_cast<GLfloat>(xOffset + width) / TEXTURE_SIZE;
    character.t[1] = static_cast<GLfloat>(yOffset + height) / TEXTURE_SIZE;

    xOffset += width;
    m_size.move(width, 0);
    if (m_size.getY() < height)
        m_size.getY() = height;
    if (xOffset + fontMetrics.maxWidth() >= TEXTURE_SIZE)
    {
        xOffset = 1;
        allocateTexture();
    }

}

Text::Text(std::string str, int size, Color color) :
    m_text(str)
  , m_d(0)
{
    QFont font;
    font.setPixelSize(size);
    m_d = new TextPrivate(font, color);
    for (unsigned int i = 0; i < str.length(); ++i) {
        m_d->createCharacter(str[i]);
    }
    setSize(m_d->m_size);
}

Text::~Text()
{
    delete m_d;
}

QFont Text::font() const
{
    return m_d->font;
}

QFontMetrics Text::fontMetrics() const
{
    return m_d->fontMetrics;
}

void Text::draw() const
{

    renderText(getX(), getY(), QString::fromStdString(m_text));
}

//! Renders text at given x, y.
void Text::renderText(float x, float y, const QString &text) const
{


    glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_TEXTURE_BIT);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    GLuint texture = 0;
    glTranslatef(x, y, 0);
    for (int i = 0; i < text.length(); ++i)
    {
        const CharData &c = m_d->getCharacter(text[i]);
        if (texture != c.textureId)
        {
            texture = c.textureId;
            glBindTexture(GL_TEXTURE_2D, texture);
        }


        glBegin(GL_QUADS);
        glTexCoord2f(c.s[0], c.t[1]);
        glVertex2f(0, 0);

        glTexCoord2f(c.s[1], c.t[1]);
        glVertex2f(c.width, 0);

        glTexCoord2f(c.s[1], c.t[0]);
        glVertex2f(c.width, c.height);

        glTexCoord2f(c.s[0], c.t[0]);
        glVertex2f(0, c.height);
        glEnd();

        glTranslatef(c.width, 0, 0);
    }

    glPopMatrix();
    glPopAttrib();
}

}

