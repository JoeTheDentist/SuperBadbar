/**
 * 	@file monsters_manager.h
 * 	@brief Header de la classe Monsters_manager
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */





#ifndef _MONSTERS_MANAGER_
#define _MONSTERS_MANAGER_
 

#include "../util/lists.h"
#include <list>
#include <stdint.h>

class Monster;
class Following_walking_monster;
class Camera;
class Babar;
class Static_data;
class Analyser;
class Sound_manager;
class Pictures_container;
class Collisions_manager;


/**
 * 	@class Monsters_manager
 * 	@brief Gestionnaire de monstres
 *
 *	@todo Enlever un accesseur (identifier cet accesseur à enlever :p)
 */

class Monsters_manager {
private:
	std::list<Monster*> m_monsters;    				/* Liste de TOUS les monstres */
	std::list<Monster *>::iterator m_it_monsters;
	std::list<Following_walking_monster*> m_following_monsters;    	/* Liste des monstres qui suivent babar */
	std::list<Monster*> m_not_following_monsters;    /* Liste des monstres qui ne suivent pas babar */

public:

	/*!
	*	@brief Constructeur par defaut
	*/
	Monsters_manager();

	/*!
	* 	@brief Destructeur
	*/
	~Monsters_manager();

	/*!
	* 	@brief remplissage de monsters_manager au debut du niveau
	*/
	void init_monsters_manager(Analyser *analyser, Sound_manager *sound_manager, Pictures_container *pictures_container);


	/*!
	* 	@brief Ajoute le monstre à monsters_manager
	*	@param monster le monstre à ajouter
	*/
	void add(Monster *monster);

	/*!
	* 	@brief Met à jour la position des monstres
	*	@param static_data DOnnées du niveau
	*	@param collisions_manager Gestionnaire de collisions
	*/
	void monsters_update_pos(Static_data *static_data, Collisions_manager *collisions_manager);	
	
	/*!
	* 	@brief Met à jour la vitesse des monstres
	*/	
	void monsters_update_speed(Babar *babar);
	
	/*!
	* 	@brief Affiche les monstres à l'écran
	*	@param camera Camera pour effectuer les affichage
	*	@todo implémenter cette méthode avec un itérateur pour pouvoir la passer en const
	*/
	void display_monsters(const Camera &camera);	
	
	/*!
	* 	@brief check les collisions entre babar et les monstres
	*	et fait perdre des vies à babar si c'est le cas
	*	@param babar le personnage
	*/
	void babar_monsters_collision(Babar *babar);
	
	
	/********************************************************
	*			Fonctions de Parcours
	********************************************************/
	/*!
	*	@brief initialise le "curseur" de monstre manager 
	*/
	void init();
	
	/*!
	*	@brief retourne vrai si on a fini de parcourir l'ensembe des monstres
	*	@return vrai si on a fini de parcourir l'ensemble des monstres
	*/
	bool end();
	
	/*!
	*	@brief incremente le curseur
	*/
	void next();
	
	/*!
	*	@brief supprime l'élément courant de monsters_manager
	*/
	void delete_element();
	

	/*!
	*	@brief accesseur
	*	@return l'élément courant de monsters_manager
	*	@todo passer la méthode en const?
	*/
	Monster *element();
	
	/*!
	* 	@brief vide la liste des monstres
	*/
//~ 	void void_list();
};
 
 
#endif
