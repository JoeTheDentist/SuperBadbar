/**
 * 	@file font.cpp
 * 	@brief Implémentation de la classe Font
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date mars 2011
 *
 */

#include "Font.h"

#include "../lib/SDL/include/SDL/SDL_ttf.h"
#include "../lib/SDL/include/SDL/SDL.h"

#include "util/utils.h"






Font::Font(int size, int r, int g, int b, std::string font_name):
	m_font(NULL),
	m_font_color()
{
	m_font = TTF_OpenFont((FONTS_R + font_name).c_str(), size);
	m_font_color.r = r;
	m_font_color.g = g;
	m_font_color.b = b;
}

Font::Font(Font &font)
{
	PRINT_DEBUG(1, "Attention, cet objet (Font) ne doit pas etre copie")
}

Font::~Font()
{
	if (m_font)
		TTF_CloseFont(m_font);
}

TTF_Font *Font::get_TTF_font()
{
	return m_font;
}

SDL_Color& Font::get_color()
{
	return  m_font_color;
}

void Font::set_color(int r, int g, int b)
{
	m_font_color.r = r;
	m_font_color.g = g;
	m_font_color.b = b;
}
