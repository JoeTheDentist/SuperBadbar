#include "OptionsMenu.h"

#include "video/Camera.h"
#include "sound/SoundEngine.h"
#include "util/repertories.h"
#include "util/globals.h"
#include "control/Keyboard.h"
#include "game/Game.h"
#include "game/LevelsManager.h"
#include "menus/MenuAction.h"
#include "menus/KeyconfigMenu.h"
#include "video/SurfaceText.h"
#include "menus/ListMenuActions.h"


OptionsMenu::OptionsMenu (Menu *parent) :
    Menu (parent)
{
    m_menu_actions.add_action_integer ("Sounds", 1, gSound->get_sounds_volume() );
    m_menu_actions.add_action_integer ("Music", 2, gSound->get_music_volume() );
    m_menu_actions.add_action_classic ("Keyboard", 3);
    m_menu_actions.add_action_classic ("Return", 4);
}

OptionsMenu::~OptionsMenu()
{
}

void OptionsMenu::update()
{
    Menu::update();
    // On met a jour le moteur de son en fonction des choix
    switch (m_menu_actions.get_selected_action() )
    {
    case 1:
        gSound->set_sounds_volume (m_menu_actions.getSelectedActionValInteger() );
        break;
    case 2:
        gSound->set_music_volume (m_menu_actions.getSelectedActionValInteger() );
        break;
    default:
        break;
    }
}

void OptionsMenu::treat_choice (int choice)
{
    switch (choice)
    {
    case 1: // son
    case 2: // musique
    case 3: // keyboard
        launch_keyconfig();
        break;
    case 4: // return
        set_leave_menu_true();
        break;
    default:
        break;
    }
}

void OptionsMenu::launch_keyconfig()
{

    set_son (new KeyconfigMenu (this) );
}
