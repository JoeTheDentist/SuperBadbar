#ifndef BLOUP_TEXT_H
#define BLOUP_TEXT_H

#include <QtGlobal>

class QChar;
class QFont;
class QFontMetrics;
class QString;

#include <string>
#include <graphics/SizedDrawable.h>
#include <utils/Color.h>

namespace bloup
{

class TextPrivate;

/*!
  * @class Text
  * @brief A displayable text
  */
class Text: public SizedDrawable
{
public:
    /*!
      * @brief Constructor
      * @param str The text to display
      * @param size Font's size
      * @param color Font's color
      */
    Text(std::string str, int size, Color color);

    /*!
      * @brief Destructor
      */
    virtual ~Text();

    /*!
      * @brief Draws the entity
      */
    virtual void draw() const;

private:
    void renderText(float x, float y, const QString &text) const;
    QFont font() const;
    QFontMetrics fontMetrics() const;

private:
    Q_DISABLE_COPY(Text)
    std::string m_text;
    TextPrivate *m_d;
};


} // namespace bloup

#endif // mi_opengl_Text_h
