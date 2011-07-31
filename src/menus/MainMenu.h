#ifndef _MAIN_MENU_H
#define _MAIN_MENU_H

#include "../menus/Menu.h"

#include "../video/Surface.h"
#include "../menus/ListMenuActions.h"

class MainTitle;

class MainMenu: public Menu {
	protected:
	Surface *m_menu_background;
	Rect m_pos_background;
	MainTitle *m_main_title;


	public:
	/*!
	*	@brief Constructeur
	*/	
	MainMenu();
	
	/*!
	*	@brief Destructeur
	*/	
	~MainMenu();
	
	/*!
	*	@brief Mise a jour de l'affichage du menu
	*/
	virtual void update_graphics();
	
	/*!
	*	@brief Accesseur
	*	@return Vrai si un fond gris doit etre affiche
	*/	
	virtual bool can_display_grey_background() const {return false;}
	protected:
		
	/*!
	*	@brief Boucle de jeu (qui remplace ici celle de game)
	*/
	void loop();
	
	/*!
	*	@brief Lancement du jeu
	*/
	void launchGame();

	/*!
	*	@brief Lancement menu multi
	*/
	void launchMulti();
	
	/*!
	*	@brief Lancement menu ChoseLevel
	*/
	void launchFastGame();
	
	/*!
	*	@brief Lancement du menu options
	*/
	void launchOptions();
	
	/*!
	*	@brief Traitement du choix
	*	@param l'int correspond au numero de la liste choisi
	*/	
	virtual void treat_choice(int choice);
};


#endif
