/**
 * Classe sprite et ses héritiers:
 * deplacements individuels des objets dynamiques
 **/


#ifndef _SPRITES_
#define _SPRITES_

#define GRAVITE 7           /* Constante pour la décélération de saut */

#include "SDL/SDL.h"
#include "../items/weapons.h"
#include "../video/animation.h"

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
	Rect m_pos; 		    /* position du sprite et sa taille */
	Rect m_speed;		    /* vitesse du sprite */
	horizontal m_horizontal;    /* direction horizontale */
	state m_state;              /* etat du sprite */
	uint32_t m_phase;		    /* phase pour alterner les images lors du déplacememnt */
	Sound_manager *m_sound_manager;
public:
	Sprite();			    /* constructeur */
	virtual ~Sprite();		/* destructeur */
    virtual SDL_Surface * current_picture();    /* Returne le pointeur sur image */
    void update_pos(Static_data *static_data);		/* mise à jour de la position */
	Rect position();	/* accesseur */
	uint32_t position_x(); 	/* accesseur */
	uint32_t position_y(); 	/* accesseur */
	uint32_t phase();       /* accesseur */
	int direction_h(); /* retourne la direction horizontale du sprite (-1 pour gauche, 0 pour middle, 1 pour droite*/
};







#endif
