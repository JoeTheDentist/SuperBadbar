/**
 * 	@file monsters_manager.cpp
 * 	@brief Implémentation de la classe Monsters_manager
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#include "MonstersManager.h"

#include "actors/Babar.h"
#include "actors/Monster.h"
#include "actors/WalkingMonster.h"
#include "actors/FlyingMonster.h"
#include "actors/ChargingMonster.h"
#include "actors/FollowingWalkingMonster.h"
#include "actors/FollowingFlyingMonster.h"
#include "actors/Boss.h"
#include "actors/BossElmar.h"
#include "video/Camera.h"
#include "game/StaticData.h"
#include "physic/CollisionsManager.h"
#include "util/Analyser.h"
#include "util/Rect.h"
#include "sound/SoundEngine.h"
#include "actors/ProjectilesManager.h"
#include "util/globals.h"
#include "players/PlayersManager.h"

Monsters_manager::Monsters_manager()
{
	PRINT_CONSTR(1, "Construction de MonstersManager");
}

Monsters_manager::~Monsters_manager()
{
	PRINT_CONSTR(1, "Destruction de MonstersManager");
	for(std::list<Monster *>::iterator it = m_monsters.begin();
		it != m_monsters.end(); ){
		delete (*it);
		(*it) = NULL;
		it = m_monsters.erase(it);
	}

}

void Monsters_manager::init_monsters_manager(Analyser *analyser)
{
	analyser->find_string("#Monsters#");
	int nombre_monstres = analyser->read_int();
	for (int compteur = 0; compteur < nombre_monstres; compteur++) {
		load_monster(analyser);
	}
}

void Monsters_manager::load_monster(std::string name, int posx, int posy)
{
	Analyser analyserMonster;
	analyserMonster.open((MONSTERS_STATS_R + name + MONSTERS_EXT).c_str());
	analyserMonster.find_string("#Class#");
	std::string monsterClass = analyserMonster.read_string();
	if (monsterClass == "FollowingWalkingMonster") {
		add(new FollowingWalkingMonster(name, posx, posy));
	} else if (monsterClass == "WalkingMonster") {
		add(new WalkingMonster(name, posx, posy));
	} else if (monsterClass == "FlyingMonster") {
		add(new FlyingMonster(name, posx, posy));
	} else if (monsterClass == "FollowingFlyingMonster") {
		add(new FollowingFlyingMonster(name, posx, posy));
	} else if (monsterClass == "ChargingMonster") {
		add(new ChargingMonster(name, posx, posy));
	} else if (monsterClass == "BossElmar") {
		add(new BossElmar(name, posx, posy));
	} else {
		PRINT_DEBUG(1, "!!! MonsterManager type %s n'existe pas", name.c_str());
	}
	analyserMonster.close();
}

void Monsters_manager::load_monster(Analyser *analyser)
{
	std::string monster_type = analyser->read_string();
	if (monster_type == "FollowingWalkingMonster") {
		add(new FollowingWalkingMonster(analyser));
	} else if (monster_type == "WalkingMonster") {
		add(new WalkingMonster(analyser));
	} else if (monster_type == "FlyingMonster") {
		add(new FlyingMonster(analyser));
	} else if (monster_type == "FollowingFlyingMonster") {
		add(new FollowingFlyingMonster(analyser));
	} else if (monster_type == "ChargingMonster") {
		add(new ChargingMonster(analyser));
	} else if (monster_type == "BossElmar") {
		add(new BossElmar(analyser));
	} else {
		PRINT_DEBUG(1, "!!! MonsterManager type %s n'existe pas", monster_type.c_str());
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

void Monsters_manager::make_monsters_fire()
{
	for(std::list<Monster *>::iterator it = m_monsters.begin();
		it != m_monsters.end(); it++) {
		(*it)->update();
		if ((*it)->can_fire())
			gProj->add_proj((*it)->fire(), MONSTERS);
	}
}

void Monsters_manager::babar_monsters_collision()
{
	Rect babar_pos = gPlayers->local_player()->damage_box();
	for(std::list<Monster *>::iterator it = m_monsters.begin();
		it != m_monsters.end(); it++){
		if (!(*it)->dead()) {
			if (CollisionsManager::check_collision((*it)->damage_box(), babar_pos)) {
				gPlayers->local_player()->damage(1);
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
			(*it)->kill();
			delete (*it);
			it = m_monsters.erase(it);
		} else if ( (*it)->position().y + (*it)->position().h >= (int)gStatic->StaticData_height() ) {
			gGameEngine->get_sets()->add_set(PIC_ANIMATIONS_R+"splash/splash",(*it)->position().x, (int)gStatic->StaticData_height()-100, false, true, true);
			delete (*it);
			it = m_monsters.erase(it);
		} else {
			++it;
		}
	}
}

Rect Monsters_manager::closer_monster_pos(Rect rect, int radius)
{
	Rect res;
	radius *= radius; // on regarde des normes au carre
	for (std::list<Monster *>::iterator it = m_monsters.begin(); it != m_monsters.end(); it++) {
		int newradius = ((*it)->position() - rect).norm_2();
		if (newradius < radius) {
			radius = newradius;
			res = (*it)->position();
		}
	}
	return res;
}
