/**
 * 	@file rocket.h
 * 	@brief Header de la classe Rocket
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date avril 2011
 *
 */


#ifndef _BABAR_ROCKET_H_
#define _BABAR_ROCKET_H_

#define ROCKET_TURN_SPEED 3
#include "actors/Projectile.h"

/**
 * 	@class Rocket
 * 	@brief Projectile a tete chercheuse
 */
class Rocket: public Projectile {
public:
	/**
	 *	@brief Constructeur
	*/
    Rocket(Rect pos, direction h, unsigned int speedx, unsigned int speedy, unsigned int damage);

	/**
	 * 	@brief Destructeur
	*/
     ~Rocket();


	/**
	 * 	@brief Met Ã  jour la vitesse du Projectile
	*/
	virtual void update_speed();

protected:
	void changeDirDirect();
	void changeDirIndirect();

};



#endif
