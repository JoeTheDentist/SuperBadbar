/**
 * 	@file following_walking_monsters.h
 * 	@brief Header de la classe Following_walking_monster
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
 
#ifndef _FOLLOWING_WALKING_MONSTERS_
#define _FOLLOWING_WALKING_MONSTERS_

#include "../sprites/monsters.h"

class Pictures_container;
class Sound_manager;
class Analyser;


/**
 * 	@class Following_walking_monster
 * 	@brief Monstre qui suit babar en marchant
 *
 */
class Following_walking_monster : public Monster {
private:


public:
	/**
	 * 	@brief Constructeur
	 *	@param sound_manager Gestionnaire de son
	 *	@param analyserLevel Analyseur se fichier
	 *	@param pictures_container Gestionnaire de chargement d'images
	*/          
	Following_walking_monster(Sound_manager *sound_manager, Analyser *analyserLevel, Pictures_container *pictures_container);

	/**
	 * 	@brief Destructeur
	 */
	~Following_walking_monster();

	/**
	 * 	@brief Met à jour la vitesse du monstre
	 *	
	 *	Le monstre avance par défaut en direction de Babar
	 */
	void update_speed(Babar *babar);
};



#endif


