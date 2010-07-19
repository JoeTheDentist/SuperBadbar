/**
 * Classe sprite et ses héritiers:
 * deplacements individuels des objets dynamiques
 **/

#ifndef _SPRITES_
#define _SPRITES_

#define BABAR_SPEED 10
#define ANIMATION_SPEED 4   /* Nombres de cycles entre deux images de l'animation (temps = TIME_LOOP * ANIMATION_SPEED) */
#define GRAVITE 7           /* Constante pour la décélération de saut */

class Animation; /* A cause d'une erreur à la compilation : ISO C++ forbids declaration of 'Animation' with no type */


enum horizontal {
    LEFT, MIDDLE_h, RIGHT
};

enum vertical {
    DOWN, MIDDLE_v, UP
};

enum state {    /* Etat, utile pour les animations, pour savoir quelle serie d'image afficher */
    STATIC, WALK, JUMP, FALL, SHOOT, DIE
};

class Sprite{
protected:
	Animation ** m_animations[3][3]; 	/* tableau d'animations du sprite */
	uint8_t m_nb_animations; 	/* nombre d'animations différentes */
	SDL_Rect m_pos; 		    /* position du sprite et sa taille */
	SDL_Rect m_speed;		    /* vitesse du sprite */
	bool m_cache;			    /* afficher le sprite ou pas */
	horizontal m_horizontal;    /* direction horizontale */
	vertical m_vertical;        /* direction verticale */
	state m_state;              /* etat du sprite */
	uint8_t m_phase;		    /* phase pour alterner les images lors du déplacememnt */
	horizontal m_last_dir;      /* */
public:
	Sprite();			    /* constructeur */
	virtual ~Sprite();		/* destructeur */
	void update_pos();		/* mise à jour de la position */
	SDL_Surface *current_picture(); /* accesseur */	// à modifier pour sélectionner la bonne image
	SDL_Rect position();		/* accesseur */
	uint32_t position_x(); 		/* accesseur */
	uint32_t position_y(); 		/* accesseur */
};


class Babar: public Sprite {
protected:
    horizontal m_last_dir;  /* Se souvient de vers où on regarde */
public:
	Babar();		/* constructeur */
	~Babar();		/* destructeur */
	void update_speed();	/* mise à jour de la vitesse en fonction des touches enfoncées */
	void update_state();    /* mise à jour de l'état de babar et de sa direction */
};


class Monster: public Sprite {
protected:
	uint32_t m_type;		/* type de monstre */
	uint32_t m_area; 		/* taille de la zone d'allez-retour */
public:
	Monster();
	Monster(uint32_t type, SDL_Rect pos, uint32_t area);
	~Monster();
	void update_speed();

};


#endif
