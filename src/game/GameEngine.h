/**
 * 	@file GameEngine.h
 * 	@brief header de la classe GameEngine
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */



#ifndef _GameEngine
#define _GameEngine

#define SPAWN_TIME 20   /* temps avant respawn, en nombre de cycles */

#include <stdint.h>

class StaticData;
class Game;
class Camera;
class Keyboard;
class Babar;
class Monsters_manager;
class EventsManager;
class CollisionsManager;
class ProjectilesManager;
class PicturesContainer;
class SoundEngine;
class AnimatedSetManager;

/**
 * 	@class GameEngine
 * 	@brief Moteur de jeu: traite les données
 *
 *	Contient notamment les listes de sprites, la matrice
 *	de collision.
 */
class GameEngine {
private:
	unsigned int m_matrix_weight;					/* Largeur de la matrice */
	unsigned int m_matrix_height;					/* Hauteur de la matrice */
	Monsters_manager *m_monsters_manager;
	AnimatedSetManager * m_sets;
	int m_spawn;                                    /* temps d'attente avant respawn */
	bool m_victory;

public:
	/**
	 * 	@brief Constructeur
	*/
	GameEngine();

	/**
	 * 	@brief Destructeur
	*/
	~GameEngine();

	/**
	 * 	@brief Initialisation des données
	 * 	@param level_name Le chemin depuis le repertoire des niveaux vers le niveau a charger
	 * 	@param camera La camera qui servira �  afficher les images
	 * 	@param StaticData Données du niveau
	 * 	@param keyboard Gestionnaire du clavier
	 *	@param PicturesContainer Le gestionnaire d'images
	*/
	void init_GameEngine(std::string level_name, Camera *camera, PicturesContainer *PicturesContainer);

	/**
	 *	@brief Met a jour le GameEngine
	*/
	void update();

	/**
	 * 	@brief Mise �  jour des positions des éléments du jeu
	 *	@todo �  déplacer
	*/
	void update_pos();

	/**
	 * 	@brief Mise �  jour des vitesses des éléments du jeu
	*/
	void update_speed();

	/**
	 * 	@brief Supprimer les projectiles et monstres "morts"
	 *	@param StaticData données du niveau
	*/
	void delete_dead_things();

	/**
	 * 	@brief Check les collisions monstres/projectiles
	*/
	void update_monsters_projectiles();

	/**
	 * 	@brief Check les collisions babar/projectiles
	*/
	void update_babar_projectiles();

	/**
	 *  @brief Regarde si Babar doit perdre des vies �  cause du décor.
	 */
	void update_babar_damage();

	/**
	 * 	@brief Affichage des monstres
	 *	@param camera La camera d'affichage
	*/
	void display_monsters(Camera * const camera) const;

 	/**
	 * 	@brief Affichage des projectiles amis
	 *	@param camera La camera d'affichage
	 *	@todo �  déplacer
	*/
	void display_projectiles_friend(Camera *camera);

	/**
	 * 	@brief Affiche les événements affichables
	 *	@param camera La camera qui affichera les événéments
	*/
	void display_events(Camera *camera);

	/**
	 * 	@brief Joue les sons �  jouer ce cycle
	 *	@param SoundEngine Gestionnaire de son
	 *
	 * Gère pour l'instant les sons de babar et des monstres
	*/
	void play_sounds();

	/**
	 *	@brief Fait gagner le niveau
	*/
	void set_victory();

	/**
	 *	@brief Accesseur
	 *	@return Vrai si le joueur a gagne
	*/
	bool has_won();

	/**
	 *	@brief Accesseur
	 *	@return Vrai si le joueur a perdu
	*/
	bool has_lost();

	/**
	 *	@brief Accesseur
	 *	@return Pointeur vers le gestionnaire de monstres
	*/
	Monsters_manager *get_monsters_manager() { return m_monsters_manager;}

    /**
	 *	@brief Accesseur
	 *	@return Pointeur vers le gestionnaire des sets
	*/
	AnimatedSetManager * get_sets() { return m_sets;}
};



#endif
