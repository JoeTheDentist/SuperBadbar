#ifndef _BABAR_MENU_H
#define _BABAR_MENU_H

#include "../video/surface.h"
#include "../menus/list_menu_actions.h"

class Surface_uniform;


class Menu {
	protected:	
	List_menu_actions m_menu_actions;
	Rect m_pos_menu;
	Menu *m_parent;
	Menu *m_son;
	bool m_leave_game;
	bool m_leave_menu;

	
	public:
	Menu(Menu *parent = NULL);
	virtual ~Menu();
	virtual void loop();
	
	/*!
	*	@brief Mise a jour du menu (sauf affichage)
	*/
	virtual void update();
	
	/*!
	*	@brief Mise a jour de l'affichage du menu
	*/	
	virtual void update_graphics() const;
	
	bool end_menu() const {return m_leave_menu;}
	bool end_game() const {return m_leave_game;}
	

	
	// appelee a chaque tour de loop
	// ne fait rien a priori mais peut etre redefinie
	virtual void aux_loop() {}
	
	protected:
	virtual void set_leave_menu_true();
	virtual void set_leave_game_true();
	virtual void refresh_screen(bool flip = true);
	virtual void treat_choice(int choice) = 0;
	virtual void set_son(Menu *menu);
};


#endif
