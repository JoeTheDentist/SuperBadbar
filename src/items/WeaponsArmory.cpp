/**
 * 	@file WeaponsArmory.cpp
 * 	@brief Implémentation de la classe WeaponsArmory
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include "WeaponsArmory.h"
#include "util/debug.h"
#include "items/ElmarMachineGun.h"
#include "items/Gun.h"
#include "items/MachineGun.h"
#include "items/RocketLauncher.h"
#include "items/Shotgun.h"
#include "sound/SoundEngine.h"
#include "video/PicturesContainer.h"


WeaponsArmory::WeaponsArmory()
{
	PRINT_CONSTR(2, "Construction de WeaponsArmory");
	Gun *gun = new Gun();
	m_armory.push_back(gun);
	m_current_weapon = m_armory.begin();
}

WeaponsArmory::~WeaponsArmory()
{
	PRINT_CONSTR(2, "Destruction de WeaponsArmory");
	for (std::list<Weapon *>::iterator it = m_armory.begin();
			it != m_armory.end(); it++)
		delete (*it);
}

Weapon *WeaponsArmory::get_current_weapon()
{
	return *m_current_weapon;
}

void WeaponsArmory::add_weapon(weapon_type type)
{
	std::list<Weapon *>::iterator it;
	// Positionnement dans la liste
	for (it = m_armory.begin(); it != m_armory.end() && (*it)->type_of_weapon() < type; it++) {}
	// Cas où l'arme est déj�  présente
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
		case MACHINE_GUN:
			m_armory.insert(it,new MachineGun());
			break;
		case ROCKET_LAUNCHER:
			m_armory.insert(it, new RocketLauncher());
			break;
		case ELMAR_MACHINE_GUN:
			m_armory.insert(it, new ElmarMachineGun());
			break;
		default:
			PRINT_DEBUG(1, "type d'arme inconnu dans add_weapon de weapon_armory");
	}
	// Changement d'arme actuelle ou non
	it--;
	if ((*it)->type_of_weapon() > get_current_weapon()->type_of_weapon())
		m_current_weapon = it;
}

void WeaponsArmory::update()
{
	if ((*m_current_weapon)->munitions() <= 0) {
		std::list<Weapon *>::iterator it = m_current_weapon;
		it--;
		m_armory.erase(m_current_weapon);
		m_current_weapon = it;
	}
}

void WeaponsArmory::next_weapon()
{
	m_current_weapon++;
	if (m_current_weapon == m_armory.end())
		m_current_weapon = m_armory.begin();
}

void WeaponsArmory::previous_weapon()
{
	if (m_current_weapon == m_armory.begin())
		m_current_weapon = m_armory.end();
	m_current_weapon--;
}
