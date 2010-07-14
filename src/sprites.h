/**
 * Classe sprite et ses héritiers:
 * deplacements individuels des objets dynamiques
 **/

#ifndef _SPRITES_
#define _SPRITES_

#define BABAR_SPEED 10
#define ANIMATION_SPEED 5 /* Nombres de cycles entre deux images de l'animation (temps = TIME_LOOP * ANIMATION_SPEED) */

class Animation; /* A cause d'une erreur à la compilation : ISO C++ forbids declaration of 'Animation' with no type*/

enum direction {
    RIGHT, LEFT, UP, DOWN
};

enum state {    /* Etat, utile pour les animations, pour savoir quelle serie d'image afficher */
    STATIC, RUN, JUMP, FALL, SHOOT, DIE
};

class Sprite{
protected:
	Animation ** m_animations; 	/* tableau d'animations du sprite */
	uint8_t m_nb_animations; 	/* nombre d'animations différentes */
	SDL_Rect m_pos; 		    /* position du sprite et sa taille */
	SDL_Rect m_speed;		    /* vitesse du sprite */
	bool m_cache;			    /* afficher le sprite ou pas */
	direction m_direction;		/* direction du sprite */
	state m_state;              /* etat du sprite */
	uint8_t m_phase;		    /* phase pour alterner les images lors du déplacememnt */
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

public:
	Babar();		/* constructeur */
	~Babar();		/* destructeur */
	void update_speed();	/* mise à jour de la vitesse en fonction des touches enfoncées */
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
