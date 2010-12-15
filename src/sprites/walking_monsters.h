/**
 * 	@file walking_monsters.h
 * 	@brief Header de la classe Walking_monster
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
 
#ifndef _WALKING_MONSTERS_
#define _WALKING_MONSTERS_

#include "../sprites/monsters.h"

class Pictures_container;
class Sound_manager;
class Analyser;


/**
 * 	@class Walking_monster
 * 	@brief Monstre qui marche
 *
 */
class Walking_monster : public Monster {
private:


public:
	/**
	 * 	@brief Constructeur
	 *	@param sound_manager Gestionnaire de son
	 *	@param analyserLevel Analyseur se fichier
	 *	@param pictures_container Gestionnaire de chargement d'images
	*/          
	Walking_monster(Sound_manager *sound_manager, Analyser *analyserLevel, Pictures_container *pictures_container);

	/**
	 * 	@brief Destructeur
	 */
	~Walking_monster();

	/**
	 * 	@brief Met à jour la vitesse du monstre
	 *	
	 *	Le monstre avance par défaut en direction de Babar
	 */
	void update_speed(Babar *babar);
};



#endif


