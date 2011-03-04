#include "main_menu.h"

#include "../video/surface.h"
#include "../video/camera.h"
#include "../util/repertories.h"
#include "../util/globals.h"
#include "../control/keyboard.h"

Main_menu::Main_menu()
{
	m_menu_background = new Surface(PIC_MAINMENU_R + "mainmenu.png");
	Rect pos_background;
	pos_background.x = 0;
	pos_background.y = 0;
	gGraphics->get_camera()->display_picture(m_menu_background, &pos_background, true);
	gGraphics->get_camera()->flip_camera();
	loop();
}

Main_menu::~Main_menu()
{
	
}

void Main_menu::loop()
{
	Keyboard *keyboard = new Keyboard();
	menu_key key = keyboard->get_menu_key();
//~ 	switch (key) {
//~ 	case mk_exit:
//~ 		
//~ 	
//~ 	}
}
