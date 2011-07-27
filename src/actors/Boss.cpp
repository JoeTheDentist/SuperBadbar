/**
 * 	@file boss.cpp
 * 	@brief Implementation de la classe Boss
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date mai 2011
 *
 */

#include "Boss.h"


Boss::Boss(std::string name, int posx, int posy):
	Monster(name, posx, posy)
{
	initBoss();
}

Boss::Boss(Analyser *analyserLevel):
	Monster(analyserLevel)
{
	initBoss();
}

void Boss::initBoss()
{
	m_state = WALKING;
	connect_to_dashboard();
}

Boss::~Boss()
{
}

void Boss::update_speed_ai()
{
	update_speed_simple(); 
}

void Boss::update()
{
}

void Boss::kill()
{
	Monster::kill();
	disconnect_from_dashboard(); // suppression de la life bar
}

