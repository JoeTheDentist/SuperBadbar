#include "surface_text.h"
#include "../util/repertories.h"
#include "../util/debug.h"

#include "../../lib/SDL/include/SDL/SDL.h"
#include "../../lib/SDL/include/SDL/SDL_ttf.h"

Surface_text::Surface_text(std::string text, int size, std::string font_name)
{
	TTF_Font *font = TTF_OpenFont((FONTS_R + font_name).c_str(), size);
	SDL_Color font_color;
	font_color.r = 255;
	font_color.g = 255;
	font_color.b = 255;
	m_surface = TTF_RenderText_Blended(font, text.c_str(), font_color);
	TTF_CloseFont(font);
}

Surface_text::~Surface_text()
{
	if (m_surface)
		SDL_FreeSurface(m_surface);
}
