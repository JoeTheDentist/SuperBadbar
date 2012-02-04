#ifndef QGLWINDOW_H
#define QGLWINDOW_H


#include <QGLWidget>
#include <window/Renderer.h>
#include <events/InputsManager.h>

namespace bloup
{

/*!
  * @class QGLWindow
  * @brief THE window: handles rendering and events (by delegation)
  */
class QGLWindow : public QGLWidget
{
public:
    QGLWindow(QWidget *parent = 0);

    /*!
      * @brief Accessor
      * @return The renderer instance
      */
    inline Renderer &getRenderer();

    /*!
      * @brief Accessor
      * @return The InputsManager instance
      */
    inline InputsManager &getInputsManager();

protected:
    /*!
      * @brief Opengl initialization
      *
      * (delegated to the renderer instance)
      */
    void initializeGL();

    /*!
      * @brief Opengl draw
      *
      * (delegated to the renderer instance)
      */
    void paintGL();

    /*!
      * @brief Window's resize
      * @param width
      * @param height
      */
    void resizeGL(int width, int height);

    /*!
      * @brief Reimplemented from QWidget
      * @param event
      */
    virtual void keyPressInput(QKeyEvent *event);

    /*!
      * @brief Reimplemented from QWidget
      * @param event
      */
    virtual void keyReleaseInput(QKeyEvent *event);

    /*!
      * @brief Reimplemented from QWidget
      * @param event
      */
    virtual void leaveInput(QEvent *event);

private:
    Renderer m_renderer;
    InputsManager m_eventsManager;
};



/*******************************/
/*    INLINE DEFINITIONS       */
/*******************************/

Renderer &QGLWindow::getRenderer()
{
    return m_renderer;
}

InputsManager &QGLWindow::getInputsManager()
{
    return m_eventsManager;
}


} // namespace bloup

#endif // QGLWINDOW_H
