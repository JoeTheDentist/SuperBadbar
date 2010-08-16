#ifndef WEAPONS_H_INCLUDED
#define WEAPONS_H_INCLUDED

#include "sprites.h"
#include "globals.h"

#define PROJ_LIFE_SPAN 15   /* Durée de vie d'un projectile */
#define PROJ_SPEED 30       /* Vitesse des projectiles */

/* Pas à leur place ! */
enum horizontal {
    LEFT, MIDDLE_h, RIGHT
};

enum vertical {
    UP, MIDDLE_v, DOWN
};
/*---*/

enum weapon_type {
    GUN, MACHINEGUN, SHUTGUN
};

class Weapon
{
    private:
        weapon_type m_weapon_type;              /* type de l'arme */
        uint32_t m_reload_time;                 /* temps entre deux tirs */
    public:
        Weapon();
        Weapon(weapon_type type);
        ~Weapon();
        void fire(SDL_Rect pos, horizontal h, vertical v);    /* crée les projectiles de l'arme */
        uint32_t reload_time();                 /* accesseur */
};

#endif // WEAPONS_H_INCLUDED
