#ifndef _PROJECTILES_
#define _PROJECTILES_

#include "sprites.h"

class Static_data;

class Projectile: public Sprite {
protected:
    SDL_Surface * m_pic;    /* Image du projectile */
    uint32_t m_damage;      /* Nombre de pt des vies que le projectile va faire perdre */
public:
    Projectile();       /* Constructeurs */
    Projectile(Rect pos, horizontal h, vertical v, uint32_t speedx, uint32_t speedy, uint32_t damage, SDL_Surface **pics);
    ~Projectile();      /* Destructeur */
	void update_pos(Static_data *static_data);
    SDL_Surface * current_picture();    /* Returne le pointeur sur image */
    uint32_t damage();  /* Accesseur */
    Rect speed();   /* Accesseur */
};



bool too_old(Projectile * p, Static_data *static_data);   /* Retourne si un projectile est trop "vieux" (pour la suppression) */

#endif
