/**
 * 	@file SurfaceFrame.cpp
 * 	@brief Implementation de la classe SurfaceFrame
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juin 2011
 *
 */

#include "SurfaceFrame.h"

#include "util/debug.h"
#include <util/Rect.h>
#include <video/SurfaceUniform.h>

SurfaceFrame::SurfaceFrame (Rect rect, int r, int g, int b) :
    Surface(),
    m_line_w (5),
    m_line_h (5)
{
//~ 	SurfaceUniform background(rect.w, rect.h, 0, 0xFF, 0xFF);
//~ 	m_surface = background.get_copy_surface();
//~ 	SDL_SetColorKey( m_surface, SDL_RLEACCEL | SDL_SRCCOLORKEY,  SDL_MapRGB( m_surface->format, 0, 0xFF, 0xFF ) );
//~ 	SurfaceUniform vertical(m_line_w, rect.h, r, g, b);
//~ 	SurfaceUniform horizontal(rect.w, m_line_h, r, g, b);
//~ 	Rect pos;
//~ 	vertical.blit_surface(this, pos);
//~ 	pos.x = rect.w - vertical.w();
//~ 	vertical.blit_surface(this, pos);
//~ 	pos.x = 0;
//~ 	horizontal.blit_surface(this, pos);
//~ 	pos.y = rect.h - horizontal.h();
//~ 	horizontal.blit_surface(this, pos);
}

SurfaceFrame::~SurfaceFrame()
{
}
