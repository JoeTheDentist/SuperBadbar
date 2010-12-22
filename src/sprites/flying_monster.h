/**
 * 	@file walking_monsters.h
 * 	@brief Header de la classe Flying_monster
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
 
#ifndef _FLYING_MONSTER_
#define _FLYING_MONSTER_

#include "../sprites/monsters.h"

class Pictures_container;
class Sound_manager;
class Analyser;


/**
 * 	@class Flying_monster
 * 	@brief Monstre qui vole
 *
 */
class Flying_monster : public Monster {
private:
	int m_high_min;

public:
	/**
	 * 	@brief Constructeur
	 *	@param sound_manager Gestionnaire de son
	 *	@param analyserLevel Analyseur se fichier
	 *	@param pictures_container Gestionnaire de chargement d'images
	*/          
	Flying_monster(Sound_manager *sound_manager, Analyser *analyserLevel, Pictures_container *pictures_container);

	/**
	 * 	@brief Destructeur
	 */
	~Flying_monster();

	/**
	 * 	@brief Met à jour la vitesse du monstre
	 *	
	 *	Le monstre avance par défaut en direction de Babar
	 */
	void update_speed();
};



#endif


