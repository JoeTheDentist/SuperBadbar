/**
 * 	@file game_engine.h
 * 	@brief header de la classe Game_engine
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */



#ifndef _DYNAMIC_DATA_
#define _DYNAMIC_DATA_

#include "../util/lists.h"
#include <stdint.h>

class Static_data;
class Game;
class Projectile;
class Monster;
class Camera;
class Sound_manager;
class Keyboard;
class Babar;
class Monsters_manager;
class Events_manager;
class Collisions_manager;



 
/**
 * 	@class Game_engine
 * 	@brief Moteur de jeu: traite les données 
 *	
 *	Contient notamment les listes de sprites, la matrice
 *	de collision.
 */
class Game_engine {
private:
	List<Projectile*> m_projectiles_friend;    	/* Liste des projectiles de Babar à l'écran */
	List<Projectile*> m_projectiles_ennemy;    	/* Liste des projectiles ennemis */
	uint32_t m_matrix_weight;					/* Largeur de la matrice */
	uint32_t m_matrix_height;					/* Hauteur de la matrice */
	Sound_manager *m_sound_manager;
	Babar *m_babar;
	Monsters_manager *m_monsters_manager;
	Events_manager *m_events_manager;
	Collisions_manager *m_collisions_manager;

public:
	/**
	 * 	@brief Constructeur
	*/
	Game_engine();

	/**
	 * 	@brief Destructeur
	*/
	~Game_engine();

	/**
	 * 	@brief Initialisation des données 
	 * 	@param level Le numéro du niveau à charger
	 * 	@param camera La camera qui servira à afficher les images
	 * 	@param static_data données du niveau
	 * 	@param sound_manager gestionnaire de son
	 * 	@param keybord gestionnaire du clavier
	*/
	void init_game_engine(int level, Camera *camera, Static_data *static_data, Sound_manager *sound_manager, Keyboard *keyboard);

	/**
	 * 	@brief Indique la fin de la liste des projectiles amis
	 * 	@return Vrai quand on arrive à la fin de la liste des projectiles amis
	 *	@todo deplacer
	*/
	bool projectiles_friend_end();									
	
	/**
	 * 	@brief Mise à jour des positions des projectiles amis
	 *	@param static_data données du niveau
	 *	@todo à déplacer
	*/
	void projectiles_friend_update_pos(Static_data *static_data);
	
	/**
	 * 	@brief Mise à jour de la position de babar
	 *	@param static_data données du niveau
	*/
	void babar_update_pos(Static_data *static_data);
	
	/**
	 * 	@brief Mise à jour de la position des monstres
	 *	@param static_data données du niveau
	*/
	void monsters_update_pos(Static_data *static_data);

	/**
	 * 	@brief Mise à jour de la vitesse de babar
	*/
	void babar_update_speed();
	
	/**
	 * 	@brief Mise à jour de l'état de babar
	 *	@brief static_data données du niveau
	*/
	void babar_update_state(Static_data *static_data);
	
	/*!
	* 	@brief check les collisions entre babar et les monstres
	*	et fait perdre des vies à babar si c'est le cas
	*/
	void babar_monsters_collision();
	
	/**
	 * 	@brief Mise à jour de la vitesse des monstres
	*/
	void monsters_update_speed();	

	/**
	 * 	@brief Affichage des monstres
	 *	@param camera La camera d'affichage
	*/
	void display_monsters(Camera *camera);	

 	/**
	 * 	@brief Affichage des projectiles amis
	 *	@param camera La camera d'affichage
	 *	@todo à déplacer
	*/
	void display_projectiles_friend(Camera *camera);	


	/**
	 * 	@brief Supprimer les projectiles amis à supprimer
	 *	@param static_data données du niveau
	 *	@todo à revoir / changer
	*/
	void delete_old_projectiles_friend(Static_data *static_data);
	
	/**
	 * 	@brief Check les collisions monstres/projectiles
	 *	@todo à revoir / changer
	*/
	void update_monsters_projectiles();


	/**
	 * 	@brief Ne fait rien pour le moment
	 *	@todo voir pourquoi ça ne fait rien :p
	*/
    void update(Camera *m_camera);  
	
	/**
	 * 	@brief Accesseur
	 *	@return projectiles_friend La liste des projectiles amis
	*/
	List<Projectile*> *projectiles_friend();	
	
	/**
	 * 	@brief Accesseur
	 *	@return Le sprite Babar
	*/
	Babar *babar();
	
	/**
	 * 	@brief Met à jour les événements
	*/
	void update_events_manager();
	
	/**
	 * 	@brief Affiche les événements affichables
	 *	@param La camera qui affichera les événéments
	*/
	void display_events(Camera *camera);

};



#endif
