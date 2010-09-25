#ifndef WEAPONS_H_INCLUDED
#define WEAPONS_H_INCLUDED

#include "SDL/SDL.h"
#include "../util/lists.h"
#include "../sound/sound_manager.h"


#define PROJ_LIFE_SPAN 15   /* Durée de vie d'un projectile */
#define PROJ_SPEED 30       /* Vitesse des projectiles */  

/* nombre maximal de munitions par armes */
#define MUN_GUN 999
#define MUN_MACHINEGUN 300
#define MUN_SHOTGUN 10

/* temps de recharge des armes */

#define RELOAD_GUN 2
#define RELOAD_MACHINEGUN 0
#define RELOAD_SHOTGUN 10


class Sprites;
class Babar;
class Sound_manager;

/* Pas à leur place ! */
enum horizontal {
    LEFT, MIDDLE_h, RIGHT
};

enum vertical {
    UP, MIDDLE_v, DOWN
};
/*---*/

enum weapon_type {
    GUN, MACHINEGUN, SHOTGUN // ATTENTION: SHOTGUN doit rester la derniere arme de l'enum pour que l'ensemble du programme ne bug pas 
};

class Projectile;
class Sound_manager;

class Weapon
{
    private:
        weapon_type m_weapon_type;              /* type de l'arme */
        uint32_t m_reload_time;                 /* temps entre deux tirs */
		List<Projectile*> *m_projectiles_list;				/* liste de projectiles dans laquelle "tire" l'arme */
		SDL_Surface **m_proj_pics;
		Sound_manager *m_sound_manager;
		int m_munitions;
		float m_last_dir_v;
		float m_last_dir_h;
		int m_phase_diago;
    public:
        Weapon(List<Projectile*> *projectiles_list, SDL_Surface **proj_pics);
        Weapon(weapon_type type, List<Projectile*> *projectiles_list, SDL_Surface **proj_pics, Sound_manager *sound_manager);
        ~Weapon();
        void fire(SDL_Rect pos, horizontal h, vertical v);    /* crée les projectiles de l'arme */
        uint32_t reload_time();                 /* accesseur */
		void change_weapon(weapon_type type);

};

#endif // WEAPONS_H_INCLUDED
