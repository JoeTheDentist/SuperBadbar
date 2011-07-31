

#ifndef _SURFACE_SELECTION_MENU_H_
#define _SURFACE_SELECTION_MENU_H_

#include <string>

#include <video/SurfaceComposite.h>

/*!
*	@class SurfaceSelectionMenu
*	@brief Surface composite pour la selection de donnees imagees*
*
*	Elle est composee d'une image centrale, d'un texte affiche sous l'image 
*	et de deux fleches a droite et a gauche de l'image centrale.
*/
class SurfaceSelectionMenu: public SurfaceComposite {
public:
	/*!
	*	@brief Constructeur
	*	@param centerSurface L'image centrale
	*	@param text Le texte a afficher sous l'image
	*/
	SurfaceSelectionMenu(Surface *centerSurface, std::string text);

	/*!
	*	@brief Destructeur	
	*/
	virtual ~SurfaceSelectionMenu() {}
		
	/*!
	*	@brief Accesseur
	*	@return Le text
	*/
	std::string getText() const {return m_text;}
		
protected:
	Surface *m_centralSurface;
	int m_centralSurfaceIndex;
	std::string m_text;
	Surface *m_surfaceText;
	int m_surfaceTextIndex;
	Surface *m_leftArrow;
	int m_leftArrowIndex;
	Surface *m_rightArrow;
	int  m_rightArrowIndex;
};

#endif
