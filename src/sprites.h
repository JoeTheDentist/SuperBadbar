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


enum horizontal {
    LEFT, MIDDLE_h, RIGHT
};

enum vertical {
    DOWN, MIDDLE_v, UP
};

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
public:
	Sprite();			    /* constructeur */
	virtual ~Sprite();		/* destructeur */
	void update_pos();		/* mise à jour de la position */
	SDL_Rect position();		/* accesseur */
	uint32_t position_x(); 		/* accesseur */
	uint32_t position_y(); 		/* accesseur */
	uint32_t phase();           /* accesseur */
};


class Babar: public Sprite {
protected:
    horizontal m_last_dir;  /* Se souvient de vers où on regarde (à cause du tir au et bas) */
    SDL_Surface *m_pics[3][3][3][2]; /* Images des animations : état, gauche droite, bas haut, numéro image */
public:
	Babar();		/* constructeur */
	~Babar();		/* destructeur */
	SDL_Surface * current_picture();  /* Retourne la bonne image de l'animation */
	void update_speed();	/* mise à jour de la vitesse en fonction des touches enfoncées */
	void update_state();    /* mise à jour de l'état de babar et de sa direction */
};


class Monster: public Sprite {
protected:
	uint32_t m_type;					/* type de monstre (sa nature) */
	uint32_t m_area; 					/* taille de la zone d'allez-retour */  // à changer éventuellement
	SDL_Surface * m_pic;                /* temp, faire avec les lvl ensuite */
public:
	Monster();						/* constructeur */
	Monster(uint32_t type, SDL_Rect pos, uint32_t area);	/* constructeur */
	~Monster();						/* destructeur */
	void update_speed();					/* met à jour la vitesse du monstre */
	SDL_Surface * current_picture();  /* Retourne la bonne image de l'animation */
	void set_pos_x(uint32_t x);				/* m_pos.x = x */
	void set_pos_y(uint32_t y);				/* m_pos.y = y */

};


class Projectile: public Sprite {
protected:
    SDL_Surface * m_pic;
public:
    Projectile();
    Projectile(SDL_Rect pos, horizontal h, vertical v);
    ~Projectile();
};


#endif
