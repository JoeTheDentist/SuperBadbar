/**
 * 	@file LifeBarPossessor.cpp
 * 	@brief Implementation de la classe virtuelle LifeBarPossessor
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juin 2011
 *
 */

#include "LifeBarPossessor.h"
#include "../video/Dashboard.h"

Dashboard *LifeBarPossessor::m_dashboard = NULL;

void LifeBarPossessor::connect_to_dashboard()
{
	m_dashboard->set_life_bar_possessor(this);
}

void LifeBarPossessor::disconnect_from_dashboard()
{
	m_dashboard->remove_life_bar_possessor();
}

void LifeBarPossessor::setDashboard(Dashboard *dashboard)
{
	m_dashboard = dashboard;
}
