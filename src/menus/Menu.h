#ifndef _BABAR_MENU_H
#define _BABAR_MENU_H

#include "../video/surface.h"
#include "../menus/ListMenuActions.h"
#include "../param/param_menus.h"


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
	Menu(Menu *parent = NULL);
	virtual ~Menu();

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

	virtual bool can_display_grey_background() const {return true;}





	protected:
	virtual void set_leave_menu_true();
	virtual void set_leave_game_true();
	virtual void treat_choice(int choice) = 0;
	virtual void set_son(Menu *menu);
};


#endif
