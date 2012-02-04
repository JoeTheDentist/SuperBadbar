#ifndef RENDERER_H
#define RENDERER_H

#include <graphics/Drawable.h>

class QGLWindow;


namespace bloup
{


class Renderer
{
public:
    /*!
      * @brief Default constructor
      */
    Renderer();

    /*!
      * @brief Opengl initialization
      */
    void init();

    /*!
      * @brief Draw the scene
      */
    void draw() ;

    void draw( Drawable &drawable) ;

    void refresh() const;

    /*!
      * @brief Resize the window
      * @param width
      * @param height
      */
    void resize(int width, int height);

    float getW() const {return m_width;}

    float getH() const {return m_height;}

private:
    float m_width;
    float m_height;
};

} // namespace bloup

#endif // RENDERER_H
