#include "ChoseLevelMenu.h"



ChoseLevelMenu::ChoseLevelMenu(Menu *parent):
	Menu(parent)
{
	m_menu_actions.add_action_classic("plop", 1);
	m_menu_actions.add_action_selectmap(2);
}


void ChoseLevelMenu::treat_choice(int choice)
{
	
}
