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
#include "../video/pictures_container.h"
#include "../sound/sound_manager.h"


Weapons_armory::Weapons_armory(Pictures_container *pictures_container, Sound_manager *sound_manager)
{
	PRINT_CONSTR(2, "Construction de Weapons_armory");
	m_pictures_container = pictures_container;
	m_sound_manager = sound_manager;
	Gun *gun = new Gun(m_pictures_container, sound_manager);
	m_armory.push_back(gun);
	m_current_weapon = m_armory.begin();
}

Weapons_armory::~Weapons_armory()
{
	
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
			PRINT_DEBUG(1, "MEME TYPE!") 
			(*it)->add_munitions();
			return;
		}
	}
	// Cas où l'arme doit etre ajoutée
	switch (type) {
		case GUN:
			m_armory.insert(it,new Gun(m_pictures_container, m_sound_manager));
			break;
		case SHOTGUN:
			m_armory.insert(it,new Shotgun(m_pictures_container, m_sound_manager));
			break;
		case MACHINEGUN:
			m_armory.insert(it,new Machinegun(m_pictures_container, m_sound_manager));
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
		it++;
		m_armory.erase(m_current_weapon);
		m_current_weapon--;
		if (it != m_armory.end()) {
			m_current_weapon = it;
		}
	}
	// Décommenter pour tester le contenu de la liste
//~ 	for ( std::list<Weapon *>::iterator it = m_armory.begin(); it != m_armory.end(); it++)
//~ 		std::cout << (*it)->type_of_weapon();
//~ 	std::cout << std::endl;
}

void Weapons_armory::next_weapon()
{
	PRINT_DEBUG(1, "NEXT WEAPON");
	m_current_weapon++;
	if (m_current_weapon == m_armory.end())
		m_current_weapon = m_armory.begin();
}

void Weapons_armory::previous_weapon()
{
	PRINT_DEBUG(1, "PREVIOUS WEAPON");
	if (m_current_weapon == m_armory.begin()) 
		m_current_weapon = m_armory.end();
	m_current_weapon--;
}
