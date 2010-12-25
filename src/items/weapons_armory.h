/**
 * 	@file weapons_armory.h
 * 	@brief Header de la classe Weapons_armory
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _WEAPONS_ARMORY_
#define _WEAPONS_ARMORY_

#include <list>
#include "../items/weapons.h"
class Weapon;

/**
 * 	@class Weapons_armory
 * 	@brief Contient et gère les armes possédées par un personnage
 */
class Weapons_armory {
private:
	std::list<Weapon*> m_armory; 
	std::list<Weapon *>::iterator m_current_weapon;
public:
	/*!
	 *	@brief Constructeur
	 *	@param pictures_container Le gestionnaire d'images
	 *	@param sound_manager Le gestionnaire de son
	*/
	Weapons_armory();

	/*!
	 *	@brief Destructeur
	*/
	~Weapons_armory();

	/*!
	 *	@brief Accesseur
	 *	@return Un pointeur vers l'arme actuelle
	*/
	Weapon *get_current_weapon();

	/*!
	 *	@brief Ajout d'une arme à l'arsenal
	 *	@param type Le type d'arme à ajouter
	 *
	 *	Si l'arme est déjà présente dans l'inventaire, on lui rajoute 
	 *	des munitions. Sinon, on la crée et on l'ajoute.
	*/
	void add_weapon(weapon_type type);

	/*!
	 *	@brief Mise à jour de l'inventaire
	 *
	 *	Supprime les armes n'ayant plus de munitions
	*/
	void update();
	
	/*!
	 *	@brief Sélectionne l'arme suivante
	 *
	 *	Quand on arrive à la dernière arme, on repart de la première
	*/
	void next_weapon();
	
	/*!
	 *	@brief Sélectionne l'arme précédente
	 *
	 *	Quand on arrive à la première arme, on repart de la dernière
	*/
	void previous_weapon();
};


#endif
