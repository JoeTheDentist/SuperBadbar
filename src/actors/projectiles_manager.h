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
	std::list<Projectile*> m_projectiles_friend;
	std::list<Projectile*> m_projectiles_ennemy;
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
	 *	@param collisions_manager Le gestionnaire de collisions
	*/
	void update_pos();

	/*!
	 *	@brief Supprime les projectiles à supprimer
	 *	@param static_data Les données du niveau
	*/
	void delete_old_projectiles();

	/*!
	 *	@brief Ajoute un projectile à la liste des projectiles amis
	 *	@param proj un pointeur vers le projectile à ajouter
	*/
	void add_friend_proj(Projectile *proj);

	/*!
	 *	@brief Vide la liste passée en parametre dans la liste des projectiles amis
	 *	@param proj un pointeur vers la liste de projectiles à ajouter
	*/
	void add_friend_proj(std::list<Projectile*> *proj);



	/*!
	 *	@brief Ajoute un projectile à la liste des projectiles ennemis
	 *	@param proj un pointeur vers le projectile à ajouter
	*/
	void add_ennemy_proj(Projectile *proj);

	/*!
	 *	@brief Vide la liste passée en parametre dans la liste des projectiles ennemis
	 *	@param proj un pointeur vers la liste de projectiles à ajouter
	*/
	void add_ennemy_proj(std::list<Projectile*> *proj);


	/*!
	 *	@brief Affiche à l'écran l'ensemble des projectiles
	 *	@param camera Le gestionnaire d'affichage
	*/
	void display(Camera *camera);


	/*!
	 *	@brief Accesseur
	 *	@return Iterator pointant sur le début de la liste de projectiles amis
	 *	@todo voir si on peut rendre cette methode constante
	*/
	std::list<Projectile *>::iterator proj_friend_begin();

	/*!
	 *	@brief Accesseur
	 *	@return Iterator pointant sur la fin de la liste de projectiles amis
	*/
	std::list<Projectile *>::iterator proj_friend_end();


	/*!
	 *	@brief Accesseur
	 *	@return Iterator pointant sur le début de la liste de projectiles ennemis
	*/
	std::list<Projectile *>::iterator proj_ennemy_begin();

	/*!
	 *	@brief Accesseur
	 *	@return Iterator pointant sur la fin de la liste de projectiles ennmis
	*/
	std::list<Projectile *>::iterator proj_ennemy_end();
};


#endif
