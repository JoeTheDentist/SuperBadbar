/**
 * 	@file WeaponsArmory.h
 * 	@brief Header de la classe WeaponsArmory
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _WEAPONS_ARMORY_
#define _WEAPONS_ARMORY_

#include <list>
#include "../items/Weapon.h"
class Weapon;

/**
 * 	@class WeaponsArmory
 * 	@brief Contient et gère les armes possédées par un personnage
 */
class WeaponsArmory {
private:
	std::list<Weapon*> m_armory;
	std::list<Weapon *>::iterator m_current_weapon;
public:
	/**
	 *	@brief Constructeur
	 *	@param pictures_container Le gestionnaire d'images
	 *	@param sound_manager Le gestionnaire de son
	*/
	WeaponsArmory();

	/**
	 *	@brief Destructeur
	*/
	~WeaponsArmory();

	/**
	 *	@brief Accesseur
	 *	@return Un pointeur vers l'arme actuelle
	*/
	Weapon *get_current_weapon();

	/**
	 *	@brief Ajout d'une arme �  l'arsenal
	 *	@param type Le type d'arme �  ajouter
	 *
	 *	Si l'arme est déj�  présente dans l'inventaire, on lui rajoute
	 *	des munitions. Sinon, on la crée et on l'ajoute.
	*/
	void add_weapon(weapon_type type);

	/**
	 *	@brief Mise �  jour de l'inventaire
	 *
	 *	Supprime les armes n'ayant plus de munitions
	*/
	void update();

	/**
	 *	@brief Sélectionne l'arme suivante
	 *
	 *	Quand on arrive �  la dernière arme, on repart de la première
	*/
	void next_weapon();

	/**
	 *	@brief Sélectionne l'arme précédente
	 *
	 *	Quand on arrive �  la première arme, on repart de la dernière
	*/
	void previous_weapon();
};


#endif
