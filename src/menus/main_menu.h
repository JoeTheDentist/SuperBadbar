#ifndef _MAIN_MENU_H
#define _MAIN_MENU_H

#include "../video/surface.h"

class Main_menu {
	private:
	Surface *m_menu_background;
	Rect m_pos_background;

	
	public:
	Main_menu();
	~Main_menu();
	void loop();
	
	private:
	void refresh_screen();
	void launch_game();
};


#endif
