/**
 * 	@file statics.cpp
 * 	@brief Implémentation de la classe Static
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#include <string>

#include "util/debug.h"
#include "video/SurfaceBig.h"
#include <video/Statics.h>

Static::Static()
{
    PRINT_CONSTR (3, "Construction d'un Static")
    m_image = NULL;
}

Static::Static (std::string dir_image, Rect pos) : m_image (new SurfaceBig (dir_image) )
{
    PRINT_CONSTR (3, "Construction du Static %s", dir_image.c_str() )
    m_pos = pos;
}

Static::Static (Surface * img, Rect pos)
{
    PRINT_CONSTR (3, "Construction d'un Static")
    m_image = img;
    m_pos = pos;
}


Static::~Static()
{
    PRINT_CONSTR (3, "Destruction d'un Static")
    delete m_image;
}

Surface * Static::current_picture() const
{
    return m_image;
}

Rect Static::position() const
{
    return m_pos;
}
