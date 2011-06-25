/**
 * 	@file monsters_manager.cpp
 * 	@brief Implémentation de la classe Monsters_manager
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#include "monsters_manager.h"
#include "../actors/babar.h"
#include "../actors/monsters.h"
#include "../actors/walking_monsters.h"
#include "../actors/flying_monster.h"
#include "../actors/charging_monster.h"
#include "../actors/following_walking_monsters.h"
#include "../actors/following_flying_monsters.h"
#include "../actors/boss.h"
#include "../actors/boss_elmer.h"
#include "../video/camera.h"
#include "../game/static_data.h"
#include "../physic/collisions_manager.h"
#include "../util/analyser.h"
#include "../util/rect.h"
#include "../sound/sound_engine.h"
#include "../actors/projectiles_manager.h"
#include "../util/globals.h"
#include "../players/players_manager.h"

Monsters_manager::Monsters_manager()
{

}

Monsters_manager::~Monsters_manager()
{
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
	if (monsterClass == "following_walking_monster") {
		add(new Following_walking_monster(name, posx, posy));
	} else if (monsterClass == "walking_monster") {
		add(new Walking_monster(name, posx, posy));
	} else if (monsterClass == "flying_monster") {
		add(new Flying_monster(name, posx, posy));
	} else if (monsterClass == "following_flying_monster") {
		add(new Following_flying_monster(name, posx, posy));
	} else if (monsterClass == "charging_monster") {
		add(new Charging_monster(name, posx, posy));
	} else if (monsterClass == "boss_elmer") {
		add(new Boss_elmer(name, posx, posy));
	} else {
		PRINT_DEBUG(1, "!!!!!! Erreur dans monstre manager, chargement monstre loupe")
	}
}

void Monsters_manager::load_monster(Analyser *analyser)
{
	std::string monster_type = analyser->read_string();
	if (monster_type == "following_walking_monster") {
		add(new Following_walking_monster(analyser));
	} else if (monster_type == "walking_monster") {
		add(new Walking_monster(analyser));
	} else if (monster_type == "flying_monster") {
		add(new Flying_monster(analyser));
	} else if (monster_type == "following_flying_monster") {
		add(new Following_flying_monster(analyser));
	} else if (monster_type == "charging_monster") {
		add(new Charging_monster(analyser));
	} else if (monster_type == "boss_elmer") {
		add(new Boss_elmer(analyser));

	} else {
		PRINT_CONSTR(1, "!!!!!! Erreur dans monstre manager, chargement monstre loupe")
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
			if (Collisions_manager::check_collision((*it)->damage_box(), babar_pos)) {
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
		} else if ( (*it)->position().y + (*it)->position().h >= (int)gStatic->static_data_height() ) {
            gGame_engine->get_sets()->add_set("splash/splash",(*it)->position().x, (int)gStatic->static_data_height()-100, false, true, true);
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
