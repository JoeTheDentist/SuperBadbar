/**
 * 	@file monsters_manager.cpp
 * 	@brief Implémentation de la classe Monsters_manager
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#include "monsters_manager.h"
#include "../sprites/babar.h"
#include "../sprites/monsters.h"
#include "../sprites/walking_monsters.h"
#include "../sprites/flying_monster.h"
#include "../sprites/following_walking_monsters.h"
#include "../sprites/following_flying_monsters.h"
#include "../video/camera.h"
#include "../game/static_data.h"
#include "../physic/collisions_manager.h"
#include "../util/analyser.h"
#include "../sound/sound_engine.h"



Monsters_manager::Monsters_manager()
{

}

Monsters_manager::~Monsters_manager()
{
	for(std::list<Monster *>::iterator it = m_monsters.begin();
			it != m_monsters.end(); it++){
		delete (*it);
	}
}

void Monsters_manager::init_monsters_manager(Analyser *analyser)
{
	analyser->find_string("#Monsters#");
	int nombre_monstres = analyser->read_int();
	for (int compteur = 0; compteur < nombre_monstres; compteur++) {
		std::string monster_type = analyser->read_string();
		if (monster_type == "following_walking_monster") {
			Following_walking_monster * curr_monster = new Following_walking_monster(analyser);
			add(curr_monster);
		} else if (monster_type == "walking_monster") {
			Walking_monster * curr_monster = new Walking_monster(analyser);
			add(curr_monster);
		} else if (monster_type == "flying_monster") {
			Flying_monster * curr_monster = new Flying_monster(analyser);
			add(curr_monster);
		} else if (monster_type == "following_flying_monster") {
			Following_flying_monster * curr_monster = new Following_flying_monster(analyser);
			add(curr_monster);
		} else {
            PRINT_CONSTR(1, "                               Erreur dans monstre manager, chargement monstre loupe")
		}
	}
}

void Monsters_manager::add(Monster *monster)
{
	m_monsters.push_back(monster);
}

void Monsters_manager::monsters_update_speed()
{
	for(std::list<Monster *>::iterator it = m_monsters.begin();
			it != m_monsters.end(); it++) {
	    (*it)->update_speed();
	}
}

void Monsters_manager::monsters_update_pos()
{
	for(std::list<Monster *>::iterator it = m_monsters.begin();
			it != m_monsters.end(); it++) {
		(*it)->update_pos();
	}
}

void Monsters_manager::display_monsters(const Camera &camera)
{
	for(std::list<Monster *>::iterator it = m_monsters.begin();
			it != m_monsters.end(); it++){
		if (!(*it)->dead())
			camera.display((*it));
	}
}

void Monsters_manager::babar_monsters_collision()
{
	Rect babar_pos = gBabar->position();
	for(std::list<Monster *>::iterator it = m_monsters.begin();
			it != m_monsters.end(); it++){
		if (!(*it)->dead()) {
			if (Collisions_manager::check_collision((*it)->position(), babar_pos)) {
				gBabar->damage(1);
			}
		}
	}
}

void Monsters_manager::play_sounds()
{
	for(std::list<Monster *>::iterator it = m_monsters.begin();
			it != m_monsters.end(); it++){
		gSound->play_sound((*it));
	}
}

void Monsters_manager::init()
{
	m_it_monsters = m_monsters.begin();
}

bool Monsters_manager::end()
{
	return m_it_monsters == m_monsters.end();
}

void Monsters_manager::next()
{
	m_it_monsters++;
}

Monster *Monsters_manager::element()
{
	return (*m_it_monsters);
}

void Monsters_manager::delete_element()
{
	delete (*m_it_monsters);
	m_it_monsters = m_monsters.erase(m_it_monsters);
}

void Monsters_manager::delete_dead_monsters()
{
	for (std::list<Monster *>::iterator it = m_monsters.begin();
			it != m_monsters.end(); ) {
		if ((*it)->dead()) {
			delete (*it);
			it = m_monsters.erase(it);
		} else {
			++it;
		}
	}
}
