#ifndef MENUWAITFORPLAYERS_H
#define MENUWAITFORPLAYERS_H

#include <string>

#include "menus/Menu.h"

class MenuWaitForPlayers : public Menu
{
public:
	/**
	 *  Constructeur
	 */
	MenuWaitForPlayers(Menu *parent, std::string lvl_name = "");

	/**
	 *  Destructeur
	 */
	virtual ~MenuWaitForPlayers();

	/**
	 *  Choix
	 */
	void treat_choice(int choice);

	/**
	 *  Redef
	 */
	void update();

	/**
	 *  Redef
	 */
	void refreshList();

	/**
	 *  Redef
	 */
	void close();

private:
	std::string m_lvlSelected;
};

#endif // MENUWAITFORPLAYERS_H
