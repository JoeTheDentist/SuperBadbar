/**
 * 	@file life_bar_possessor.cpp
 * 	@brief Implementation de la classe virtuelle Life_bar_possessor
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date juin 2011
 *
 */

#include "life_bar_possessor.h"
#include "../video/dashboard.h"

Dashboard *Life_bar_possessor::m_dashboard = NULL;

void Life_bar_possessor::connect_to_dashboard()
{
	m_dashboard->set_life_bar_possessor(this);
}

void Life_bar_possessor::disconnect_from_dashboard()
{
	m_dashboard->remove_life_bar_possessor();
}

void Life_bar_possessor::setDashboard(Dashboard *dashboard)
{
	m_dashboard = dashboard;
}
