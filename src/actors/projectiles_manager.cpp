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
#include "../actors/projectiles.h"
#include "../game/static_data.h"
#include "../physic/collisions_manager.h"
#include "../video/camera.h"
#include "../util/debug.h"


Projectiles_manager::Projectiles_manager() {

}

Projectiles_manager::~Projectiles_manager()
{
	for (int i=0; i<LAST_OUILLE_CHAN; i++) {
        for (std::list<Projectile *>::iterator it = m_proj[i].begin();
            it != m_proj[i].end(); it++) {
            m_proj[i].erase(it);
            it--;
        }
	}
}


void Projectiles_manager::update_pos()
{
    for (int i=0; i<LAST_OUILLE_CHAN; i++) {
        for (std::list<Projectile *>::iterator it = m_proj[i].begin();
            it != m_proj[i].end(); it++) {
            (*it)->update_pos(gCollision);
        }
	}
}

void Projectiles_manager::update_speed()
{
	for (int i=0; i<LAST_OUILLE_CHAN; i++) {
        for (std::list<Projectile *>::iterator it = m_proj[i].begin();
            it != m_proj[i].end(); it++) {
            (*it)->update_speed();
        }
	}
}

void Projectiles_manager::update_state()
{
	for (int i=0; i<LAST_OUILLE_CHAN; i++) {
        for (std::list<Projectile *>::iterator it = m_proj[i].begin();
            it != m_proj[i].end(); it++) {
            (*it)->update_state();
        }
	}
}

void Projectiles_manager::delete_old_projectiles()
{
	for (int i=0; i<LAST_OUILLE_CHAN; i++) {
        for (std::list<Projectile *>::iterator it = m_proj[i].begin();
            it != m_proj[i].end(); ) {
            if ((*it)->dead()) {
                delete (*it);
                it = m_proj[i].erase(it);
            } else {
                ++it;
            }
        }
	}
}

void Projectiles_manager::add_proj(Projectile *proj, ouille_chan chan) {
	m_proj[chan].push_back(proj);
}

void Projectiles_manager::add_proj(std::list<Projectile*> *proj, ouille_chan chan) {
	for (std::list<Projectile *>::iterator it = proj->begin();
			it != proj->end(); it++) {
		add_proj(*it, chan);
	}
	delete proj;
}

std::list<Projectile *>::iterator Projectiles_manager::proj_begin(ouille_chan chan) {
	return m_proj[chan].begin();
}

std::list<Projectile *>::iterator Projectiles_manager::proj_end(ouille_chan chan) {
	return m_proj[chan].end();
}
