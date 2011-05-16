/**
 * 	@file projectiles_manager.h
 * 	@brief Header de la classe Projectiles_manager
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _PROJECTILES_MANAGER
#define _PROJECTILES_MANAGER

#include <list>

/* Canaux des groupes de dommage, on pourra utiliser la suite pour les différents joueurs */
enum dmg_chan {
    ALL, MONSTERS, PLAYER1, PLAYER2, PLAYER3, PLAYER4, LAST_dmg_chan
};

class Projectile;
class Static_data;
class Collisions_manager;
class Camera;

/**
 * 	@class Projectiles_manager
 * 	@brief Gestionnaire de projectiles
 *
 *	@warning pour le moment on ne dispose que des projectiles de babar
 *
 *	La version actuelle différencie deux types de projectiles:\n
 *	- Ceux du héros et de ses éventuels amis
 *	- Ceux des ennemis du héros
 *
 *	Le héros est sensible aux projectiles de ses ennemis et vice versa
 */
class Projectiles_manager {
private:
	std::list<Projectile*> m_proj[LAST_dmg_chan];
public:

	/*!
	 *	@brief Constructeur
	*/
	Projectiles_manager();

	/*!
	 *	@brief Destructeur
	*/
	~Projectiles_manager();

	/*!
	 *	@brief Met à jour la position de l'ensemble des projectiles
	*/
	void update_pos();

	/*!
	 *	@brief Met à jour la vitesse de l'ensemble des projectiles
	*/
	void update_speed();

	/*!
	 *	@brief Met à jour les états de l'ensemble des projectiles
	*/
	void update_state();

	/*!
	 *	@brief Supprime les projectiles à supprimer
	 *	@param static_data Les données du niveau
	*/
	void delete_old_projectiles();

	/*!
	 *	@brief Ajoute un projectile à la liste des projectiles sur un channel
	 *	@param proj un pointeur vers le projectile à ajouter
	*/
	void add_proj(Projectile *proj, dmg_chan chan);

	/*!
	 *	@brief Vide la liste passée en parametre dans la liste des projectiles sur un channel
	 *	@param proj un pointeur vers la liste de projectiles à ajouter
	*/
	void add_proj(std::list<Projectile*> *proj, dmg_chan chan);

	/*!
	 *	@brief Accesseur
	 *	@return Iterator pointant sur le début de la liste de projectiles amis
	 *	@todo voir si on peut rendre cette methode constante
	*/
	std::list<Projectile *>::iterator proj_begin(dmg_chan chan);

	/*!
	 *	@brief Accesseur
	 *	@return Iterator pointant sur la fin de la liste de projectiles amis
	*/
	std::list<Projectile *>::iterator proj_end(dmg_chan chan);
};


#endif
