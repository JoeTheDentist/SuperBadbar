/**
 * 	@file weapons_armory.cpp
 * 	@brief Implémentation de la classe Weapons_armory
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include "weapons_armory.h"
#include "../util/debug.h"
#include "../items/weapons.h"
#include "../items/gun.h"
#include "../items/shotgun.h"
#include "../items/machinegun.h"
#include "../items/rocket_launcher.h"
#include "../video/pictures_container.h"
#include "../sound/sound_manager.h"


Weapons_armory::Weapons_armory()
{
	PRINT_CONSTR(2, "Construction de Weapons_armory");
	Gun *gun = new Gun();
	m_armory.push_back(gun);
	m_current_weapon = m_armory.begin();
}

Weapons_armory::~Weapons_armory()
{
	PRINT_CONSTR(2, "Destruction de Weapons_armory");
	for (std::list<Weapon *>::iterator it = m_armory.begin();
			it != m_armory.end(); it++)
		delete (*it);
}

Weapon *Weapons_armory::get_current_weapon()
{
	return *m_current_weapon;
}

void Weapons_armory::add_weapon(weapon_type type)
{
	std::list<Weapon *>::iterator it;
	// Positionnement dans la liste
	for (it = m_armory.begin(); it != m_armory.end() && (*it)->type_of_weapon() < type; it++) {}
	// Cas où l'arme est déjà présente
	if (it != m_armory.end()) {
		if ((*it)->type_of_weapon() == type) {
			(*it)->add_munitions();
			return;
		}
	}
	// Cas où l'arme doit etre ajoutée
	switch (type) {
		case GUN:
			m_armory.insert(it,new Gun());
			break;
		case SHOTGUN:
			m_armory.insert(it,new Shotgun());
			break;
		case MACHINEGUN:
			m_armory.insert(it,new Machinegun());
			break;
		case ROCKET_LAUNCHER:
			m_armory.insert(it, new Rocket_launcher());
			break;
		default:
			PRINT_DEBUG(1, "type d'arme inconnu dans add_weapon de weapon_armory");
	}
	// Changement d'arme actuelle ou non
	it--;
	if ((*it)->type_of_weapon() > get_current_weapon()->type_of_weapon())
		m_current_weapon = it;
}

void Weapons_armory::update()
{
	if ((*m_current_weapon)->munitions() <= 0) {
		std::list<Weapon *>::iterator it = m_current_weapon;
		it--;
		m_armory.erase(m_current_weapon);
		m_current_weapon = it;
	}
}

void Weapons_armory::next_weapon()
{
	m_current_weapon++;
	if (m_current_weapon == m_armory.end())
		m_current_weapon = m_armory.begin();
}

void Weapons_armory::previous_weapon()
{
	if (m_current_weapon == m_armory.begin())
		m_current_weapon = m_armory.end();
	m_current_weapon--;
}
