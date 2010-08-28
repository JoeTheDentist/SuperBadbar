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
#include "weapons.h"


/* /!\ Les enums horizontal et vertical sont dans weapon... */

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

    Weapon m_weapon;
    uint32_t m_fire_phase;
public:
	Babar();		/* constructeur */
	~Babar();		/* destructeur */
	SDL_Surface * current_picture();  /* Retourne la bonne image de l'animation */
	void update_speed();	/* mise à jour de la vitesse en fonction des touches enfoncées */
	void update_state();    /* mise à jour de l'état de babar et de sa direction */
};


class Monster: public Sprite {
protected:
	int m_type;					/* type de monstre (sa nature) */
	int m_area_begin; 			    /* début de la zone d'allez-retour */
	int m_area_end;                /* fin de la zone d'aller-retrou */
	int m_speed_def;               /* vitesse en norme */
	int m_life;                    /* vies */
	bool m_can_fire;                    /* si le monstre tire ou non */
	SDL_Surface * m_pics[3][3][3];      /* Images du monstre : state, gauche droite, num image */
public:
	Monster();						        /* constructeur */
	Monster(uint32_t type, SDL_Rect pos);	/* constructeur */
	~Monster();						        /* destructeur */
	void update_speed();					/* met à jour la vitesse du monstre */
	SDL_Surface * current_picture();        /* Retourne la bonne image de l'animation */
	void set_pos_x(uint32_t x);				/* m_pos.x = x */
	void set_pos_y(uint32_t y);				/* m_pos.y = y */
	void set_type(uint32_t type);           /* modif m_type */
	void set_life(uint32_t life);           /* modif m_life */
	void set_begin(uint32_t begin);         /* ... */
	void set_end(uint32_t end);             /* ... */
	void set_fire(bool can_fire);           /* ... */
	void set_speed(uint32_t speed);         /* ... */
	void set_pic(SDL_Surface * pic, uint32_t i, uint32_t j, uint32_t k); /* ... */
	void damage(uint32_t damage);           /* fait perdre des vies */
	bool dead();                            /* Si les pt de vies sont >= 0 */
	int32_t type();                        /* Accesseur */

};


class Projectile: public Sprite {
protected:
    SDL_Surface * m_pic;    /* Image du projectile */
    uint32_t m_damage;      /* Nombre de pt des vies que le projectile va faire perdre */
public:
    Projectile();       /* Constructeurs */
    Projectile(SDL_Rect pos, horizontal h, vertical v, uint32_t speedx, uint32_t speedy, uint32_t damage);
    ~Projectile();      /* Destructeur */
    SDL_Surface * current_picture();    /* Returne le pointeur sur image */
    uint32_t damage();  /* Accesseur */
};



bool too_old(Projectile * p);   /* Retourne si un projectile est trop "vieux" (pour la suppression) */


#endif
