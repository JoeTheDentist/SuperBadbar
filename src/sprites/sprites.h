/**
 * Classe sprite et ses héritiers:
 * deplacements individuels des objets dynamiques
 **/


#ifndef _SPRITES_
#define _SPRITES_

#define BABAR_SPEED 10
#define ANIMATION_SPEED 4   /* Nombres de cycles entre deux images de l'animation (temps = TIME_LOOP * ANIMATION_SPEED) */
#define GRAVITE 7           /* Constante pour la décélération de saut */

#include "SDL/SDL.h"
#include "../items/weapons.h"

/* /!\ Les enums horizontal et vertical sont dans weapon... */

class Static_data;
class Sound_manager;
class Keyboard;
class Camera;


enum state {    /* Etat, utile pour les animations, pour savoir quelle serie d'image afficher */
    STATIC, WALK, JUMP
};

class Sprite{
protected:
	SDL_Rect m_pos; 		    /* position du sprite et sa taille */
	SDL_Rect m_speed;		    /* vitesse du sprite */
	bool m_cache;			    /* afficher le sprite ou pas */
	horizontal m_horizontal;    /* direction horizontale */
	vertical m_vertical;        /* direction verticale */
	state m_state;              /* etat du sprite */
	uint32_t m_phase;		    /* phase pour alterner les images lors du déplacememnt */
	bool m_climb;
	Sound_manager *m_sound_manager;
public:
	Sprite();			    /* constructeur */
	virtual ~Sprite();		/* destructeur */
    virtual SDL_Surface * current_picture();    /* Returne le pointeur sur image */
    void update_pos(Static_data *static_data);		/* mise à jour de la position */
	SDL_Rect position();	/* accesseur */
	uint32_t position_x(); 	/* accesseur */
	uint32_t position_y(); 	/* accesseur */
	uint32_t phase();       /* accesseur */
};







#endif
