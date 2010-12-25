/**
 * 	@file projectiles_manager.cpp
 * 	@brief Implémentation de la classe Projectiles_manager
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
 
#include <iostream>
#include "projectiles_manager.h"
#include "../sprites/projectiles.h"
#include "../game/static_data.h"
#include "../game/collisions_manager.h"
#include "../video/camera.h"
#include "../util/debug.h"


Projectiles_manager::Projectiles_manager() {
	
}

Projectiles_manager::~Projectiles_manager() {
	// suppression de projectiles amis
	for (std::list<Projectile *>::iterator it = m_projectiles_friend.begin();
		it != m_projectiles_friend.end(); ) {
		delete (*it);
		it = m_projectiles_friend.erase(it);

	}
	// suppression de projectiles ennemis
	for (std::list<Projectile *>::iterator it = m_projectiles_ennemy.begin();
		it != m_projectiles_ennemy.end(); it++) {
		m_projectiles_ennemy.erase(it);
		it--;
	}	
}


void Projectiles_manager::update_pos(Collisions_manager *collisions_manager) {
	// position des projectiles amis
	for (std::list<Projectile *>::iterator it = m_projectiles_friend.begin();
			it != m_projectiles_friend.end(); it++) {
	    (*it)->update_pos(collisions_manager);
	}	
	// position des projectiles ennemis
	for (std::list<Projectile *>::iterator it = m_projectiles_ennemy.begin();
			it != m_projectiles_ennemy.end(); it++) {
	    (*it)->update_pos(collisions_manager);
	}	
}

void Projectiles_manager::delete_old_projectiles(Static_data *static_data)
{
	// suppression de projectiles amis
	for (std::list<Projectile *>::iterator it = m_projectiles_friend.begin();
			it != m_projectiles_friend.end(); ) {
		if ((*it)->dead()) {
			delete (*it);
			it = m_projectiles_friend.erase(it);
		} else {
			++it;
		}
	}
	// suppression de projectiles ennemis
	for (std::list<Projectile *>::iterator it = m_projectiles_ennemy.begin();
			it != m_projectiles_ennemy.end(); it++) {
		if ((*it)->dead()) {
			m_projectiles_ennemy.erase(it);
			it--;
		}
	}
}

void Projectiles_manager::add_friend_proj(Projectile *proj) {
	m_projectiles_friend.push_back(proj);
}

void Projectiles_manager::add_friend_proj(std::list<Projectile*> *proj) {
	for (std::list<Projectile *>::iterator it = proj->begin();
			it != proj->end(); it++) {	
		add_friend_proj(*it);
	}				
	delete proj;
}

void Projectiles_manager::add_ennemy_proj(Projectile *proj) {
	m_projectiles_ennemy.push_back(proj);
}

void Projectiles_manager::add_ennemy_proj(std::list<Projectile*> *proj) {
	for (std::list<Projectile *>::iterator it = proj->begin();
			it != proj->end(); it++) {	
		add_ennemy_proj(*it);
	}				
	delete proj;
}

void Projectiles_manager::display(Camera *camera) {
	for (std::list<Projectile *>::iterator it = m_projectiles_friend.begin();
			it != m_projectiles_friend.end(); it++) {
		if (!(*it)->dead())
			camera->display_sprite(*it);		
	}
	for (std::list<Projectile *>::iterator it = m_projectiles_ennemy.begin();
			it != m_projectiles_ennemy.end(); it++) {
		if (!(*it)->dead())
			camera->display_sprite(*it);		
	}
}

std::list<Projectile *>::iterator Projectiles_manager::proj_friend_begin() {
	return m_projectiles_friend.begin();
}

std::list<Projectile *>::iterator Projectiles_manager::proj_friend_end() {
	return m_projectiles_friend.end();
}

std::list<Projectile *>::iterator Projectiles_manager::proj_ennemy_begin() {
	return m_projectiles_ennemy.begin();
}

std::list<Projectile *>::iterator Projectiles_manager::proj_ennemy_end() {
	return m_projectiles_ennemy.end();
}



