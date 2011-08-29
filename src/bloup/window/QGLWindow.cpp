#include "QGLWindow.h"

#include <QTimer>

namespace bloup
{

QGLWindow::QGLWindow(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    updateGL();
}


void QGLWindow::initializeGL()
{
    m_renderer.init();
}

void QGLWindow::paintGL()
{
    m_renderer.draw();
}

void QGLWindow::resizeGL(int width, int height)
{
    m_renderer.resize(width, height);
}

void QGLWindow::keyPressInput(QKeyEvent *event)
{
    m_eventsManager.keyPressInput(event);
}

void QGLWindow::keyReleaseInput(QKeyEvent *event)
{
    m_eventsManager.keyReleaseInput(event);
}

void QGLWindow::leaveInput(QEvent *event)
{
    m_eventsManager.leaveInput(event);
}

} // namespace bloup
