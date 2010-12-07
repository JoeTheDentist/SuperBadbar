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
	* 	@brief Ajout le monstre à monsters_manager
	*	@param monster le monstre à ajouter
	*/
	void add(Monster *monster);

	/*!
	* 	@brief Met à jour la position des monstres
	*	@param static_data contient la matrice des collisions du niveau
	*/
	void monsters_update_pos(Static_data *static_data);	
	
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
	
	/*!
	* 	@brief accesseur à virer
	*	@return la liste des monstres de monsters_manager
	*/
	List<Monster*> *monsters(); // ACCESSEUR TEMPORAIRE, A SUPPRIMER!!!!!!!!
	
	/*!
	* 	@brief vide la liste des monstres
	*/
	void void_list(); 
};
 
 
#endif
