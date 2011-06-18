/**
 * 	@file surface_frame.cpp
 * 	@brief Implementation de la classe Surface_frame
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date juin 2011
 *
 */
 
#include "../../lib/SDL/include/SDL/SDL.h"

#include "surface_frame.h"
#include "surface_uniform.h"

Surface_frame::Surface_frame(Rect rect, int r, int g, int b):
	Surface(),
	m_line_w(5),
	m_line_h(5)
{
	Surface_uniform background(rect.w, rect.h, 0, 0xFF, 0xFF);
	m_surface = background.get_copy_surface();
	SDL_SetColorKey( m_surface, SDL_RLEACCEL | SDL_SRCCOLORKEY,  SDL_MapRGB( m_surface->format, 0, 0xFF, 0xFF ) );
	Surface_uniform vertical(m_line_w, rect.h, r, g, b);
	Surface_uniform horizontal(rect.w, m_line_h, r, g, b);
	Rect pos;
	pos.x = 0;
	pos.y = 0;
	vertical.blit_surface(this, pos);
	pos.x = rect.w - vertical.w();
	vertical.blit_surface(this, pos);
	pos.x = 0;
	horizontal.blit_surface(this, pos);
	pos.y = rect.h - horizontal.h();
	horizontal.blit_surface(this, pos);
}

Surface_frame::~Surface_frame()
{
	delete m_surface;
}
