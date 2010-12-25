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
#include "../video/pictures_container.h"
#include "../sound/sound_manager.h"
#include "../game/static_data.h"
#include "../game/collisions_manager.h"
#include "../util/analyser.h"



Monsters_manager::Monsters_manager() {

}

Monsters_manager::~Monsters_manager() {

}

void Monsters_manager::init_monsters_manager(Analyser *analyser, Sound_manager *sound_manager, Pictures_container *pictures_container) {
    void_list();
	analyser->find_string("#Monsters#");
	int nombre_monstres = analyser->read_int();
	for (int compteur = 0; compteur < nombre_monstres; compteur++) {
		std::string monster_type = analyser->read_string();
		if (monster_type == "following_walking_monster") {
			Following_walking_monster * curr_monster = new Following_walking_monster(sound_manager, analyser, pictures_container);
			add(curr_monster);
			m_following_monsters.push_back(curr_monster);
		} else if (monster_type == "walking_monster") {
			Walking_monster * curr_monster = new Walking_monster(sound_manager, analyser, pictures_container);
			add(curr_monster);
			m_not_following_monsters.push_back(curr_monster);
		} else if (monster_type == "flying_monster") {
			Flying_monster * curr_monster = new Flying_monster(sound_manager, analyser, pictures_container);
			add(curr_monster);
			m_not_following_monsters.push_back(curr_monster);
		}
	}
}

void Monsters_manager::add(Monster *monster) {
	m_monsters.add(monster);
}

void Monsters_manager::monsters_update_speed(Babar *babar){
	for(std::list<Following_walking_monster *>::iterator it = m_following_monsters.begin();
			it != m_following_monsters.end(); it++) {
	    (*it)->update_speed(babar);
	}

	for(std::list<Monster *>::iterator it = m_not_following_monsters.begin();
			it != m_not_following_monsters.end(); it++) {
	    (*it)->update_speed();
	}



}

void Monsters_manager::monsters_update_pos(Static_data*static_data, Collisions_manager *collisions_manager) {
    m_monsters.init();
	while(!m_monsters.end()) {
		m_monsters.element()->update_pos(static_data, collisions_manager);
		m_monsters.next();
	}
}

void Monsters_manager::display_monsters(const Camera &camera) {
    m_monsters.init();
	while(!m_monsters.end()) {
	    camera.display_sprite(m_monsters.element());
	    m_monsters.next();
	}
}

void Monsters_manager::babar_monsters_collision(Babar *babar) {
	Rect babar_pos = babar->position();

	m_monsters.init();
	while(!m_monsters.end()) {
		if (Collisions_manager::check_collision(m_monsters.element()->position(), babar_pos)) {
			babar->damage(1);
		}
	    m_monsters.next();
	}
}

void Monsters_manager::init() {
	m_monsters.init();
}

bool Monsters_manager::end() {
	return m_monsters.end();
}

void Monsters_manager::next() {
	m_monsters.next();
}

Monster *Monsters_manager::element() {
	return m_monsters.element();
}

void Monsters_manager::delete_element() {
	m_monsters.delete_element(true);
}

void Monsters_manager::void_list() {
	m_monsters.void_list();
}
