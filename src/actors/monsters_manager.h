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


#include <list>
#include <stdint.h>
#include <string>

#include "../actors/projectiles_manager.h"

class Monster;
class Camera;
class Babar;
class Static_data;
class Analyser;
class Collisions_manager;
class Sound_engine;

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
	void init_monsters_manager(Analyser *analyser);


	/*!
	*	@brief Charge un monstre depuis l'analyser 
	*	@param analyser L'analyser avec le curseur place avant un monstre
	*/
	void load_monster(Analyser *analyser);
	/*!
	*	@brief Charge un monstre a partir de son nom et de sa position
	*	@param name Le nom du monstre
	*	@param posx Position intiale du monstres
	*	@param posy Position intiale du monstres
	*/
	void load_monster(std::string name, int posx, int posy);

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
	void monsters_update_pos();

	/*!
	* 	@brief Met à jour la vitesse des monstres
	*/
	void monsters_update_speed();

    /**
     *
     */
	void make_monsters_fire();

	/*!
	* 	@brief check les collisions entre babar et les monstres
	*	et fait perdre des vies à babar si c'est le cas
	*	@param babar le personnage
	*/
	void babar_monsters_collision();

	/*!
	 * 	@brief Joue les sons à jouer ce cycle
	 *	@param sound_engine Gestionnaire de son
	*/
	void play_sounds();

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
	*	@warning la suppression fait passerle curseur à l'élément suivant
	*/
	void delete_element();


	/*!
	*	@brief accesseur
	*	@return l'élément courant de monsters_manager
	*	@todo passer la méthode en const?
	*/
	Monster *element();

	/*!
	* 	@brief Supprime les monstres qui n'ont plus de vies
	*/
	void delete_dead_monsters();

};


#endif
