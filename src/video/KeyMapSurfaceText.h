/**
 * 	@file KeyMapSurfaceText.h
 * 	@brief Header de la classe KeyMapSurfaceText
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juin 2011
 *
 */

#ifndef _BABAR_KEYMAPSURFACETEXT_H_
#define _BABAR_KEYMAPSURFACETEXT_H_

#include <string>

class KeyMapSurfaceText
{
public:
    /**
    *	@brief Constructeur
    *	@param str Le texte
    *	@param size La taille de la police (sans l'offset)
    *	@param r Composante rouge
    *	@param g Composante verte
    *	@param b Composante bleue
    *	@param font_name Le nom de la police a utiliser
    */
    KeyMapSurfaceText (std::string str, int size = 30, int r = 255, int g = 255, int b = 255, std::string fontName = "defaultfont.ttf");

    /**
    *	@brief Destructeur
    */
    ~KeyMapSurfaceText();

    bool operator< (const KeyMapSurfaceText &key) const;

private:
    std::string m_text;
    int m_size;
    int m_r;
    int m_g;
    int m_b;
    std::string m_fontName;

};


#endif
