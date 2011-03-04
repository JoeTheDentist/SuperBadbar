#ifndef _MAIN_MENU_H
#define _MAIN_MENU_H

class Surface;

class Main_menu {
	private:
	Surface *m_menu_background;
	
	
	public:
	Main_menu();
	~Main_menu();
	void loop();
};


#endif
