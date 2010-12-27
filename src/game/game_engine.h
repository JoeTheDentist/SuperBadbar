/**
 * 	@file game_engine.h
 * 	@brief header de la classe Game_engine
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */



#ifndef _GAME_ENGINE
#define GAME_ENGINE

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
class Projectiles_manager;
class Pictures_container;
class Sound_engine;

 
/**
 * 	@class Game_engine
 * 	@brief Moteur de jeu: traite les données 
 *	
 *	Contient notamment les listes de sprites, la matrice
 *	de collision.
 */
class Game_engine {
private:
	uint32_t m_matrix_weight;					/* Largeur de la matrice */
	uint32_t m_matrix_height;					/* Hauteur de la matrice */
	Sound_manager *m_sound_manager;
	Babar *m_babar;
	Monsters_manager *m_monsters_manager;
	Events_manager *m_events_manager;
	Collisions_manager *m_collisions_manager;
	Projectiles_manager *m_projectiles_manager;

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
	 * 	@param static_data Données du niveau
	 * 	@param sound_manager Gestionnaire de son
	 * 	@param keyboard Gestionnaire du clavier
	 *	@param pictures_container Le gestionnaire d'images
	*/
	void init_game_engine(int level, Camera *camera, Static_data *static_data, Sound_manager *sound_manager, Keyboard *keyboard, Pictures_container *pictures_container);						
	
	/**
	 * 	@brief Mise à jour des positions des projectiles 
	 *	@todo à déplacer
	*/
	void projectiles_update_pos();
	
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
	
	/*!
	* 	@brief Supprime les monstres qui n'ont plus de vies
	*/
	void delete_dead_monsters();
	
	/**
	 * 	@brief Check les collisions monstres/projectiles
	 *	@todo à revoir / changer
	*/
	void update_monsters_projectiles();


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
	 *	@param camera La camera qui affichera les événéments
	*/
	void display_events(Camera *camera);


	
	/*!
	 * 	@brief Joue les sons à jouer ce cycle
	 *	@param sound_engine Gestionnaire de son
	 *
	 * Gère pour l'instant les sons de babar et des monstres
	*/
	void play_sounds(Sound_engine *sound_engine);		
};



#endif
