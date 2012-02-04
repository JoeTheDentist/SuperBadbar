#include "Renderer.h"
#include <QGLWidget>
#include <graphics/Picture.h>
#include <graphics/Texture.h>
#include <window/QGLWindow.h>

namespace bloup
{

Renderer::Renderer():
    m_width(640)
  , m_height(480)
{
}

void Renderer::init()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);                   // Black Background
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Really Nice Perspective
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void Renderer::draw()
{

}

void Renderer::draw( Drawable &drawable)
{
    drawable.draw();
}

void Renderer::refresh() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


}


void Renderer::resize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    #ifdef QT_OPENGL_ES_1
    glOrthof(0, m_width, m_height, 0, -15.0, 15.0);
    #else
    glOrtho(0, m_width, m_height, 0, -15.0, 15.0);
    #endif
    glMatrixMode(GL_MODELVIEW);
}


} // namespace bloup
