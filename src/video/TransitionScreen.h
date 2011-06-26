/**
 * 	@file TransitionScreen.h
 * 	@brief Header de la classe TransitionScreen
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date juin 2011
 *
 */

#ifndef _BABAR_TransitionScreen_H
#define _BABAR_TransitionScreen_H

#include "../video/Surface.h"
#include <string>

class Camera;


/*!
*	@class TransitionScreen
*	@brief Ecran de transition, skipable ou bout d'un certain temps
*/
class TransitionScreen {
	private:
	bool m_skipable;
	bool m_ended;
	Surface *m_background;
	Surface *m_text1;
	Surface *m_text2;
	Rect m_pos_text1;
	Rect m_pos_text2;

	public:
	/*!
	*	@brief Constructeur
	*	@param picture_path Le chemin vers l'image de fond depuis le repertoire
	*	des images des ecrans de transition (avec l'extension)
	*	@param text1 Le texte a afficher tant que l'ecran n'est pas skipable
	*	@param text2 Le texte a afficher tant que l'ecran est skipable
	*/
	TransitionScreen(	std::string picture_path,
						std::string text1 = "Chargement...",
						std::string text2 = "Entrez une touche pour continuer");

	/*!
	*	@brief Destructeur
	*/
	~TransitionScreen();

	/*!
	*	@brief Mise a jour des evenements
	*/
	void update();

	/*!
	*	@brief Affichage de l'ecran
	*	@param camera La camera d'affichage
	*/
	void display(Camera *camera);

	/*!
	*	@brief Demande au joueur d'appuyer sur une touche
	*/
	void wait_for_player();

	/*!
	*	@brief Accesseur
	*	@return Vrai si l'ecran de transition doit disparaitre
	*/
	bool ended();
};






#endif
