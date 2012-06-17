
#include "MenuJoin.h"

#include <map>
#include <string>

#include "util/globals.h"
#include "menus/MenuWaitForPlayers.h"

MenuJoin::MenuJoin(Menu *parent) :
	Menu(parent)
{
	//gNetwork->initClient();
	m_menu_actions.add_action_string("IP", 1, "192.168.1.1");
	m_menu_actions.add_action_classic("Refresh", 2);
	m_menu_actions.add_action_classic("Return", 3);
	m_size = 0;
}

MenuJoin::~MenuJoin()
{
	//gNetwork->clearAll();
}

void MenuJoin::treat_choice(int choice)
{
	if ( choice == 1 ) { //join
		//
	} else if ( choice == 2 ) { //refresh
		//gNetwork->clearServers();
		m_menu_actions.clearList();
		m_menu_actions.add_action_string("IP", 1, "192.168.1.1");
		m_menu_actions.add_action_classic("Refresh", 2);
		m_menu_actions.add_action_classic("Return", 3);
		m_size = 0;
	} else if ( choice == m_size+3 ) { //return
		set_leave_menu_true();
	} else { //map choisie en choice-3

		/*int i=0;
		std::map<std::string,std::string>::iterator it = gNetwork->beginServers();
		while ( it != gNetwork->endServers() && ( i < choice-3 ) ) {
			++it;
			++i;
		}
		std::string ip = (*it).first;
		gNetwork->setHostIp(ip);*/

		set_son(new MenuWaitForPlayers(this));
	}
}

void MenuJoin::update()
{
	//gNetwork->setMenuId(m_id);
	Menu::update();
	//updateNetwork();
}

void MenuJoin::refreshList()
{
	int i=0;
	m_menu_actions.clearList();
	m_menu_actions.add_action_string("IP", 1, "192.168.1.1");
	m_menu_actions.add_action_classic("Refresh", 2);

	/*std::map<std::string,std::string>::iterator it = gNetwork->beginServers();
	while ( it != gNetwork->endServers() ) {
		m_menu_actions.add_action_classic((*it).second, i+3);
		++it;
		++i;
	}
	m_size = i;
	m_menu_actions.add_action_classic("Return", m_size+3);*/
}

void MenuJoin::close()
{
	//Rien...
	//Bah oui on va pas lui fermer la fenetre ou
	//il choisit les serveurs... Non mais !!!
	//Vous etes vraiment pas cool, vous les petits zapotecques
	//tout velus.
	//Sinon bonne journee a vous.
}
