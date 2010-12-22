/**
 * 	@file projectiles.h
 * 	@brief Header de la classe Projectile
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#ifndef _PROJECTILES_
#define _PROJECTILES_

#include "sprites.h"

class Static_data;
class Collisions_manager;
class Pictures_container;


/**
 * 	@class Projectile
 * 	@brief Projectiles du jeu
 */
class Projectile: public Sprite {
protected:
    SDL_Surface * m_pic;    /* Image du projectile */
    uint32_t m_damage;      /* Nombre de pt des vies que le projectile va faire perdre */
	bool m_dead;				/* Indique si le projectile est à supprimer */
public:
	
	/*!
	 *	@brief Constructeur
	*/
    Projectile(Rect pos, horizontal h, uint32_t speedx, uint32_t speedy, uint32_t damage, Pictures_container *pictures_container);

	/*!
	 *	@brief Constructeur
	*/
    Projectile(Rect pos, horizontal h, uint32_t speedx, uint32_t speedy, uint32_t damage, SDL_Surface **pics);

	/*!
	 * 	@brief Destructeur
	*/
    ~Projectile();

	/*!
	 * 	@brief Met à jour la position du Projectile
	 *	@param collisions_manager Gestionnaire de collisions
	*/
	void update_pos(Collisions_manager *collisions_manager);

	/*!
	 * 	@brief Accesseur
	 *	@return Un pointeur vers l'image actuelle
	*/
    SDL_Surface * current_picture() const;
	
	/*!
	 * 	@brief Accesseur
	 *	@return Le nombre de points de vies que fait perdre le projectile
	*/
    uint32_t damage() const;
	
	/*!
	 * 	@brief Accesseur
	 *	@return La vitesse du projectile
	*/
    Rect speed() const;   /* Accesseur */
	
	/*!
	 *	@brief Accesseur
	 *	@return Vrai si le Projectile doit etre supprimé
	*/
	bool dead() const;
	
	/*!
	 *	@brief Mutateur: "tue" le projectile
	*/
	void kill();
	
	
};



bool too_old(Projectile * p,  Collisions_manager *collisions_manager);   /* Retourne si un projectile est trop "vieux" (pour la suppression) */

#endif
