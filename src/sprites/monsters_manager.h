/*!
	ATTENTION IL FAUDRAIT ENLEVER L'ACCESSEUR
*/






#ifndef _MONSTERS_MANAGER_
#define _MONSTERS_MANAGER_
 

#include "../util/lists.h"
#include <stdint.h>

class Monster;
class Camera;
class Babar;
class Static_data;
class Analyser;
class Sound_manager;
class Pictures_container;
class Collisions_manager;

class Monsters_manager {
private:
	List<Monster*> m_monsters;    				/* Liste des monstres */


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
	*	@param static_data contient la matrice des collisions du niveau
	*/
	void monsters_update_pos(Static_data *static_data, Collisions_manager *collisions_manager);	
	
	/*!
	* 	@brief Met à jour la vitesse des monstres
	*/	
	void monsters_update_speed(Babar *babar); // le faire passer au constructeur pour les walking monsters?
	
	/*!
	* 	@brief Affiche les monstres à l'écran
	*	@param camera Camera pour effectuer les affichage
	*/
	void display_monsters(Camera *camera);	
	
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
	*/
	Monster *element();
	
	/*!
	* 	@brief vide la liste des monstres
	*/
	void void_list(); 
};
 
 
#endif
