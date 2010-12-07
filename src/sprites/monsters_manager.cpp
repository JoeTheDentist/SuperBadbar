

#include "monsters_manager.h"
#include "../sprites/babar.h"
#include "../sprites/monsters.h"
#include "../video/camera.h"
#include "../game/static_data.h"
#include "../util/collisions.h"



Monsters_manager::Monsters_manager() {

}

Monsters_manager::~Monsters_manager() {

}

void Monsters_manager::add(Monster *monster) {
	m_monsters.add(monster);
}


void Monsters_manager::monsters_update_speed(Babar *babar){
    m_monsters.init();
	while (!m_monsters.end()) {
	    m_monsters.element()->update_speed(babar);
	    m_monsters.next();
	}
}

void Monsters_manager::monsters_update_pos(Static_data*static_data)
{
    m_monsters.init();
	while(!m_monsters.end()) {
		m_monsters.element()->update_pos(static_data);
		m_monsters.next();
	}
}

void Monsters_manager::display_monsters(Camera *camera) {
    m_monsters.init();
	while(!m_monsters.end()) {
	    camera->display_sprite(m_monsters.element());
	    m_monsters.next();
	}
}

void Monsters_manager::babar_monsters_collision(Babar *babar)
{
	Rect babar_pos = babar->position();

	m_monsters.init();
	while(!m_monsters.end()) {
		if (check_collision(m_monsters.element()->position(), babar_pos)) {
			babar->damage(1);
		}
	    m_monsters.next();
	}
}


List<Monster*> *Monsters_manager::monsters() {
	return &m_monsters;
}


void Monsters_manager::void_list() {
	m_monsters.void_list();
}
