#ifndef _BABAR_MENU_H
#define _BABAR_MENU_H

#include "video/Surface.h"
#include "menus/ListMenuActions.h"
#include "param/param_menus.h"


class SurfaceUniform;


class Menu {
	protected:
	ListMenuActions m_menu_actions;
	Rect m_pos_menu;
	Menu *m_parent;
	Menu *m_son;
	bool m_leave_game;
	bool m_leave_menu;
	int m_size;


	public:

	/*!
	*	@brief Constructeur
	*	@param parent Le menu appelant
	*/
	Menu(Menu *parent = NULL);


	/*!
	*	@brief Destructeur
	*/
	virtual ~Menu();

	/*!
	*	@brief Mise a jour du menu (sauf affichage)
	*/
	virtual void update();

	/*!
	*	@brief Mise a jour de l'affichage du menu
	*/
	virtual void update_graphics() const;

	/*!
	*	@brief Accesseur
	*	@return Vrai si le menu a termine son traitement (l'interface appelante peut le quitter)
	*/
	bool end_menu() const {return m_leave_menu;}

	/*!
	*	@brief Accesseur
	*	@return Vrai si l'utilisateur a demande de quitter le jeu
	*/
	bool end_game() const {return m_leave_game;}

	/*!
	*	@brief Accesseur
	*	@return Vrai si un fond gris doit etre affiche
	*/
	virtual bool can_display_grey_background() const {return true;}


	protected:
	/*!
	*	@brief Indique que le menu a fini son traitement et peut etre quitte
	*/
	virtual void set_leave_menu_true();

	/*!
	*	@brief Indique qu'on doit fermer le jeu
	*/
	virtual void set_leave_game_true();

	/*!
	*	@brief Traitement du choix
	*	@param l'int correspond au numero de la liste choisi
	*/
	virtual void treat_choice(int choice) = 0;

	/*!
	*	@brief Mutateur du fils du menu
	*/
	virtual void set_son(Menu *menu);
};


#endif
