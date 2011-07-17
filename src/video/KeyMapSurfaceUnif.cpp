/**
 * 	@file KeyMapSurfaceUnif.cpp
 * 	@brief Implementation de la classe KeyMapSurfaceUnif
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juin 2011
 *
 */
 
 #include "KeyMapSurfaceUnif.h"

KeyMapSurfaceUnif::KeyMapSurfaceUnif(int width, int height, int r, int g, int b, int alpha):
	m_width(width),
	m_height(height),
	m_r(r),
	m_g(g),
	m_b(b),
	m_alpha(alpha)
{
	
}

KeyMapSurfaceUnif::~KeyMapSurfaceUnif()
{
	
}


bool KeyMapSurfaceUnif::operator<(const KeyMapSurfaceUnif &key) const
{
	// haha c'est beau!
	#define COMPARE_KEYMAPST(attribut) \
	if (attribut != key.attribut) \
		return attribut < key.attribut;  
	COMPARE_KEYMAPST(m_width);
	COMPARE_KEYMAPST(m_height);
	COMPARE_KEYMAPST(m_r);
	COMPARE_KEYMAPST(m_g);
	COMPARE_KEYMAPST(m_b);
	COMPARE_KEYMAPST(m_alpha);
	return false;
}

