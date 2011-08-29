#include "Picture.h"

namespace bloup
{

Picture::Picture():
    SizedDrawable()
  , m_texture(NULL)
  , m_zBuffer(5)
  , m_enableAlpha(true)
{
}

void Picture::draw() const
{
    if (!m_texture)
        return;
    float x2 = getX(), x1 = getX() + getW();
    float y1 = getY() + getH(), y2 = getY(), z = m_zBuffer;
    if (m_enableAlpha) {
        glEnable(GL_BLEND);
        glDisable(GL_DEPTH_TEST);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    }
    glEnable(GL_TEXTURE_2D);
    m_texture->glBindMe();
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x2, y2, z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x1, y2,  z);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x1,  y1,  z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x2,  y1,  z);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

} // namespace bloup
