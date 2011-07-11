/**
 * 	@file ProjectilesManager.cpp
 * 	@brief Implémentation de la classe ProjectilesManager
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>
#include "ProjectilesManager.h"
#include "../actors/Projectile.h"
#include "../game/StaticData.h"
#include "../physic/CollisionsManager.h"
#include "../video/Camera.h"
#include "../util/debug.h"


ProjectilesManager::ProjectilesManager()
{
    PRINT_CONSTR(1, "Construction de ProjectilesManager");
}

ProjectilesManager::~ProjectilesManager()
{
    PRINT_CONSTR(1, "Destruction de ProjectilesManager");
	for (int i=0; i<LAST_dmg_chan; i++) {
        for (std::list<Projectile *>::iterator it = m_proj[i].begin();
            it != m_proj[i].end(); ++it) {
            delete (*it);        }
	}
}


void ProjectilesManager::update_pos()
{
    for (int i=0; i<LAST_dmg_chan; i++) {
        for (std::list<Projectile *>::iterator it = m_proj[i].begin();
            it != m_proj[i].end(); it++) {
            (*it)->update_pos(gCollision);
        }
	}
}

void ProjectilesManager::update_speed()
{
	for (int i=0; i<LAST_dmg_chan; i++) {
        for (std::list<Projectile *>::iterator it = m_proj[i].begin();
            it != m_proj[i].end(); it++) {
            (*it)->update_speed();
        }
	}
}

void ProjectilesManager::update_state()
{
	for (int i=0; i<LAST_dmg_chan; i++) {
        for (std::list<Projectile *>::iterator it = m_proj[i].begin();
            it != m_proj[i].end(); it++) {
            (*it)->update_state();
        }
	}
}

void ProjectilesManager::delete_old_projectiles()
{
	for (int i=0; i<LAST_dmg_chan; i++) {
        for (std::list<Projectile *>::iterator it = m_proj[i].begin();
            it != m_proj[i].end(); ) {
            if ( (*it)->dead() ) {
                delete (*it);
                it = m_proj[i].erase(it);
            } else {
                ++it;
            }
        }
	}
}

void ProjectilesManager::add_proj(Projectile *proj, dmg_chan chan) 
{
	m_proj[chan].push_back(proj);
	proj->set_chan(chan);
}

void ProjectilesManager::add_proj(std::list<Projectile*> *proj, dmg_chan chan) 
{
	for (std::list<Projectile *>::iterator it = proj->begin();
			it != proj->end(); it++) {
		add_proj(*it, chan);
	}
	delete proj;
}

std::list<Projectile *>::iterator ProjectilesManager::proj_begin(dmg_chan chan) 
{
	return m_proj[chan].begin();
}

std::list<Projectile *>::iterator ProjectilesManager::proj_end(dmg_chan chan) 
{
	return m_proj[chan].end();
}
