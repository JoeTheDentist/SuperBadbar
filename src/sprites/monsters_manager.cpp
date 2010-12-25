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
#include "../video/camera.h"
#include "../game/static_data.h"
#include "../game/collisions_manager.h"
#include "../util/analyser.h"



Monsters_manager::Monsters_manager() {

}

Monsters_manager::~Monsters_manager() {
	for(std::list<Monster *>::iterator it = m_monsters.begin();
			it != m_monsters.end(); it++){
		delete (*it);
	}
}

void Monsters_manager::init_monsters_manager(Analyser *analyser) {
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
		}
	}
}

void Monsters_manager::add(Monster *monster) {
	m_monsters.push_back(monster);
}

void Monsters_manager::monsters_update_speed(Babar *babar){
	for(std::list<Monster *>::iterator it = m_monsters.begin();
			it != m_monsters.end(); it++) {
	    (*it)->update_speed(babar);
	}
}

void Monsters_manager::monsters_update_pos(Static_data*static_data, Collisions_manager *collisions_manager) {
	for(std::list<Monster *>::iterator it = m_monsters.begin();
			it != m_monsters.end(); it++) {
		(*it)->update_pos(static_data, collisions_manager);
	}
}

void Monsters_manager::display_monsters(const Camera &camera) {
	for(std::list<Monster *>::iterator it = m_monsters.begin();
			it != m_monsters.end(); it++){
		camera.display_sprite((*it));
	}
}

void Monsters_manager::babar_monsters_collision(Babar *babar) {
	Rect babar_pos = babar->position();

	for(std::list<Monster *>::iterator it = m_monsters.begin();
			it != m_monsters.end(); it++){
		if (Collisions_manager::check_collision((*it)->position(), babar_pos)) {
			babar->damage(1);
		}
	}
}

void Monsters_manager::init() {
	m_it_monsters = m_monsters.begin();
}

bool Monsters_manager::end() {
	return m_it_monsters == m_monsters.end();
}

void Monsters_manager::next() {
	m_it_monsters++;
}

Monster *Monsters_manager::element() {
	return (*m_it_monsters);
}

void Monsters_manager::delete_element() {
	delete (*m_it_monsters);
	m_it_monsters = m_monsters.erase(m_it_monsters);
}

