/**
 * 	@file SpecialLetter.h
 * 	@brief Header de la classe SpecialLetter
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juin 2011
 *
 */


#ifndef _BABAR_SPECIAL_LETTER_H_
#define _BABAR_SPECIAL_LETTER_H_

#include <video/SurfaceText.h>
#include <string>

/**
*	@class SpecialLetter
*	@brief Une surface representant une lettre et pouvant etre redimensionnee
*/
class SpecialLetter : public SurfaceText {
private:
	char m_letter;		// la lettre
	int m_offset_size;	// l'offset de la taille de la police
	int m_size;			// taille de la police
	int m_r;			// composante rouge
	int m_g;			// composante verte
	int m_b;			// composante bleue
	std::string m_font_name;	// le nom de la police
public:
	/**
	*	@brief Constructeur
	*	@param letter La lettre
	*	@param size La taille de la police (sans l'offset)
	*	@param r Composante rouge
	*	@param g Composante verte
	*	@param b Composante bleue
	*	@param font_name Le nom de la police a utiliser
	*/
	SpecialLetter(char letter, int size = 30, int r = 255, int g = 255, int b = 255, std::string font_name = "defaultfont.ttf");

	/**
	*	@brief Destructeur
	*/
	virtual ~SpecialLetter();

	/**
	*	@brief appelee a chaque tour, resize la lettre
	*/
	virtual void update();

	/**
	*	@brief Accesseur
	*	@return La largeur de la surface SANS l'offset (dimension finale, pas actuelle)
	*/
	virtual int fake_w();

	/**
	*	@brief Accesseur
	*	@return La hauteur de la surface SANS l'offset (dimension finale, pas actuelle)
	*/
	virtual int fake_h();
};

#endif
