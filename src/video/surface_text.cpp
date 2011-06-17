/**
 * 	@file surface_text.cpp
 * 	@brief Implémentation de la classe Surface_text
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date mars 2011
 *
 */

#include "surface_text.h"
#include "../util/repertories.h"
#include "../util/debug.h"
#include "../video/font.h"
#include <iostream>

#include "../../lib/SDL/include/SDL/SDL.h"
#include "../../lib/SDL/include/SDL/SDL_ttf.h"

Surface_text::Surface_text()
{
	
}

Surface_text::Surface_text(std::string text, int size, int r, int g, int b, std::string font_name)
{
	init(text, size, r, g, b, font_name);
}

Surface_text::Surface_text(std::string text, Font &font)
{
	m_surface = TTF_RenderText_Blended(font.get_TTF_font(), text.c_str(), font.get_color());
}

Surface_text::~Surface_text()
{
	if (m_surface)
		SDL_FreeSurface(m_surface);
}

void Surface_text::init(std::string text, int size, int r, int g, int b, std::string font_name)
{
	TTF_Font *font = TTF_OpenFont((FONTS_R + font_name).c_str(), size);
	SDL_Color font_color;
	font_color.r = r;
	font_color.g = g;
	font_color.b = b;
	m_surface = TTF_RenderText_Blended(font, text.c_str(), font_color);
	if (!m_surface)
		PRINT_DEBUG(1, "Erreur dans le chargement d'une surface texte");
	TTF_CloseFont(font);
}
