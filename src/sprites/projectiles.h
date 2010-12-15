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



/**
 * 	@class Projectile
 * 	@brief Projectiles du jeu
 */
class Projectile: public Sprite {
protected:
    SDL_Surface * m_pic;    /* Image du projectile */
    uint32_t m_damage;      /* Nombre de pt des vies que le projectile va faire perdre */
public:
	
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
	 *	@param static_data Données du niveau
	 *	@param collisions_manager Gestionnaire de collisions
	*/
	void update_pos(Static_data *static_data, Collisions_manager *collisions_manager);

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
};



bool too_old(Projectile * p,  Collisions_manager *collisions_manager);   /* Retourne si un projectile est trop "vieux" (pour la suppression) */

#endif
