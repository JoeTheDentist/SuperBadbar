/**
 * 	@file SurfaceUniform.cpp
 * 	@brief Implementation de la classe SurfaceUniform
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date mars 2011
 *
 */

#include "SurfaceUniform.h"

#include "util/debug.h"
#include "util/globals.h"
#include "video/Camera.h"
#include "video/GraphicEngine.h"
#include "video/PicturesContainer.h"

SurfaceUniform::SurfaceUniform (int width, int height, int r, int g, int b, int alpha)
{
    m_sprite = PicturesContainer::GetInstance()->loadSurfaceUniform (width, height, r, g, b, alpha);
    setSurface (m_sprite);
}

SurfaceUniform::~SurfaceUniform()
{
}
