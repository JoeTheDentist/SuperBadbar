#ifndef _PAUSE_MENU_H
#define _PAUSE_MENU_H

#include "../menus/Menu.h"

#include "../video/Surface.h"
#include "../menus/ListMenuActions.h"


class PauseMenu: public Menu {

	public:

	/*!
	*	@brief Constructeur
	*	@param parent Le menu appelant
	*/	
	PauseMenu();
	
	/*!
	*	@brief Destructeur
	*/	
	~PauseMenu();

	protected:
	/*!
	*	@brief Lance le menu d'options
	*/
	void launch_options();
	
	/*!
	*	@brief Traitement du choix
	*	@param l'int correspond au numero de la liste choisi
	*/	
	virtual void treat_choice(int choice);
};


#endif
