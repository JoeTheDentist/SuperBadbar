#include "MainMenu.h"

#include "../video/Camera.h"
#include "../util/repertories.h"
#include "../util/globals.h"
#include "../control/Keyboard.h"
#include "../game/game.h"
#include "../game/LevelsManager.h"
#include "../menus/MenuAction.h"
#include "../menus/OptionsMenu.h"
#include "../video/SurfaceText.h"
#include "../video/Maintitle.h"

MainMenu::MainMenu() :
	Menu(),
	m_menu_background(new Surface(PIC_MAINMENU_R + "mainmenu.png")),
	m_pos_background(),
	m_main_title(new MainTitle("Super Badbar"))
{
	m_menu_actions.add_action_classic("New game", 1);
	m_menu_actions.add_action_classic("Options", 2);
	m_menu_actions.add_action_classic("Leave", 3);
	gSound->load_music("MainMenu.mp3");
	gSound->play_music();
	loop();
}

MainMenu::~MainMenu()
{
//~ 	delete m_menu_background;
}

void MainMenu::update_graphics()
{
	Camera *camera = gGraphics->get_camera();
	camera->display_picture(m_menu_background, &m_pos_background, true);
	m_main_title->update();
	m_main_title->display(camera);
	Menu::update_graphics();
	gGraphics->flip_camera();
}

void MainMenu::loop()
{
	while(!end_menu() &	 !end_game()) {
		gKeyboard->update_events();
		update();
		update_graphics();
	}
}

void MainMenu::treat_choice(int choice)
{
	switch(choice) {
		case 1: // nouvelle partie
			launch_game();
			gSound->load_music("MainMenu.mp3");
			gSound->play_music();
			break;
		case 2: // options
			launch_options();
			break;
		case 3: // quitter le jeu
			set_leave_game_true();
			break;
		default:
			break;
	}
}

void MainMenu::launch_game()
{
	LevelsManager * levelsmanager = new LevelsManager();
	levelsmanager->play();
	delete levelsmanager;
}

void MainMenu::launch_options()
{
	set_son(new OptionsMenu(this));
}

