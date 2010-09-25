#ifndef _MONSTERS_
#define _MONSTERS_

#include "sprites.h"

class Monster: public Sprite {
protected:
	int m_type;						/* type de monstre (sa nature) */
	int m_area_begin; 			 	/* début de la zone d'allez-retour */
	int m_area_end;                	/* fin de la zone d'aller-retrou */
	int m_speed_def;               	/* vitesse en norme */
	int m_life;                    	/* vies */
	bool m_can_fire;                /* si le monstre tire ou non */
	SDL_Surface * m_pics[2][4];  /* Images du monstre : state, gauche droite, num image */
public:
	Monster(Sound_manager *sound_manager);						        /* constructeur */
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
	void set_pic(SDL_Surface * pic, uint32_t i, uint32_t j); /* ... */
	void damage(uint32_t damage);           /* fait perdre des vies */
	bool dead();                            /* Si les pt de vies sont >= 0 */
	int32_t type();                        /* Accesseur */

};

#endif
