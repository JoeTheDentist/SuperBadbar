/**
 * 	@file KeyMapSurfaceText.cpp
 * 	@brief Implementation de la classe KeyMapSurfaceText
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juin 2011
 *
 */
 
 #include "KeyMapSurfaceText.h"

KeyMapSurfaceText::KeyMapSurfaceText(std::string str, int size, int r, int g, int b, std::string fontName):
	m_text(str),
	m_size(size),
	m_r(r),
	m_g(g),
	m_b(b),
	m_fontName(fontName)
{
	
}

KeyMapSurfaceText::~KeyMapSurfaceText()
{
	
}


bool KeyMapSurfaceText::operator<(const KeyMapSurfaceText &key) const
{
	// haha c'est beau!
	#define COMPARE_KEYMAPST(attribut) \
	if (attribut != key.attribut) \
		return attribut < key.attribut;  
	COMPARE_KEYMAPST(m_text);
	COMPARE_KEYMAPST(m_size);
	COMPARE_KEYMAPST(m_r);
	COMPARE_KEYMAPST(m_g);
	COMPARE_KEYMAPST(m_b);
	COMPARE_KEYMAPST(m_fontName);
	return false;
}

