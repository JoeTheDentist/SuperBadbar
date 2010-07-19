
#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "sprites.h"
#include "animations.h"
#include "globals.h"
#include "events.h"


/*********************************
**	Méthodes de Sprite 	**
**********************************/
Sprite::Sprite()
{
	m_nb_animations = 1;
	m_pos.x = 0;
	m_pos.y = 0;
	m_pos.w = 0;
	m_pos.h = 0;
	m_speed.x = 0;
	m_speed.y = 0;
	m_cache = true;
	m_horizontal = MIDDLE_h;
	m_vertical = MIDDLE_v;
	m_state = STATIC;
	m_phase = 0;
	for(int i = 0; i<3; i++)
        for(int j = 0; j<3; j++)
            m_animations[i][j] = new Animation*[m_nb_animations];
    m_last_dir = RIGHT;
}

Sprite::~Sprite()
{
    for(int i = 0; i<m_nb_animations; i++) {
        m_animations[0][0][i]->~Animation();          /* ??? est-ce c'est ce qu'il faut faire ??? */
        delete m_animations[0][0];                   /* Il va y avoir des fuites partout => faire sur toutes les cases ? */
    }
    delete[] m_animations;
}

void Sprite::update_pos()
{
	m_pos.x += m_speed.x;
	m_pos.y += m_speed.y;
	m_phase++;
}

SDL_Surface *Sprite::current_picture()
{
    /* On change d'image tous les ANIMATION_SPEED cycles */
    if (m_phase%ANIMATION_SPEED==0) {
        m_animations[m_last_dir][m_vertical][m_state]->next_pic();
    }
	if (m_animations != NULL)
		return m_animations[m_last_dir][m_vertical][m_state]->current_pic();
	else
		return NULL;
}

SDL_Rect Sprite::position()
{
	return m_pos;
}

uint32_t Sprite::position_x()
{
	return m_pos.x;
}

uint32_t Sprite::position_y()
{
	return m_pos.y;
}


/*********************************
**	Méthodes de Babar 	**
**********************************/
Babar::Babar()
{
    m_pos.w = 163;
	m_pos.h = 234;
	m_nb_animations = 3;

    /*** Chargement des images ***/

    SDL_Surface *babar_static_right = SDL_LoadBMP("../pic/babar_static_right.bmp");
    SDL_Surface *babar_static_left = SDL_LoadBMP("../pic/babar_static_left.bmp");
    SDL_Surface *babar_walk_right = SDL_LoadBMP("../pic/babar_walk_right.bmp");
    SDL_Surface *babar_walk_left = SDL_LoadBMP("../pic/babar_walk_left.bmp");

    SDL_SetColorKey(babar_static_right, SDL_SRCCOLORKEY, SDL_MapRGB(babar_static_right->format, 0, 0, 255)); /* transparence bleu 255 */
    SDL_SetColorKey(babar_static_left, SDL_SRCCOLORKEY, SDL_MapRGB(babar_static_left->format, 0, 0, 255));
    SDL_SetColorKey(babar_walk_right, SDL_SRCCOLORKEY, SDL_MapRGB(babar_walk_right->format, 0, 0, 255));
    SDL_SetColorKey(babar_walk_left, SDL_SRCCOLORKEY, SDL_MapRGB(babar_walk_left->format, 0, 0, 255));

	/* Déclarations des animations de Babar */
	/*** Animation position fixe ***/
        /* Droite */
	SDL_Surface **array_static_right;
    array_static_right = new SDL_Surface*[1];

    array_static_right[0] = babar_static_right;

    Animation *a_static_right;
    a_static_right = new Animation(1, array_static_right);

    m_animations[RIGHT][DOWN][STATIC] = a_static_right;
    m_animations[RIGHT][MIDDLE_v][STATIC] = a_static_right;
    m_animations[RIGHT][UP][STATIC] = a_static_right;

        /* Gauche */
    SDL_Surface **array_static_left;
    array_static_left = new SDL_Surface*[1];

    array_static_left[0] = babar_static_left;

    Animation *a_static_left;
    a_static_left = new Animation(1, array_static_left);

    m_animations[LEFT][DOWN][STATIC] = a_static_left;
    m_animations[LEFT][MIDDLE_v][STATIC] = a_static_left;
    m_animations[LEFT][UP][STATIC] = a_static_left;

        /* Milieu : inutile mais pour éviter des pb */
    m_animations[MIDDLE_h][DOWN][STATIC] = a_static_right;
    m_animations[MIDDLE_h][MIDDLE_v][STATIC] = a_static_right;
    m_animations[MIDDLE_h][UP][STATIC] = a_static_right;

	/*** Animation de marche ***/
        /* Droite */
	SDL_Surface **array_walk_right;
    array_walk_right = new SDL_Surface*[2];

    array_walk_right[0] = babar_static_right;
    array_walk_right[1] = babar_walk_right;

    Animation *a_walk_right;
    a_walk_right = new Animation(2, array_walk_right);

    m_animations[RIGHT][DOWN][WALK] = a_walk_right;
    m_animations[RIGHT][MIDDLE_v][WALK] = a_walk_right;
    m_animations[RIGHT][UP][WALK] = a_walk_right;

        /* Gauche */
    SDL_Surface **array_walk_left;
    array_walk_left = new SDL_Surface*[2];

    array_walk_left[0] = babar_static_left;
    array_walk_left[1] = babar_walk_left;

    Animation *a_walk_left;
    a_walk_left = new Animation(2, array_walk_left);

    m_animations[LEFT][DOWN][WALK] = a_walk_left;
    m_animations[LEFT][MIDDLE_v][WALK] = a_walk_left;
    m_animations[LEFT][UP][WALK] = a_walk_left;


    /*** Animation saut ***/
        /* Droite */
    SDL_Surface **array_jump_right;
    array_jump_right = new SDL_Surface*[1];

    array_jump_right[0] = babar_static_right;

    Animation *a_jump_right;
    a_jump_right = new Animation(1, array_jump_right);

    m_animations[RIGHT][DOWN][JUMP] = a_jump_right;
    m_animations[RIGHT][MIDDLE_v][JUMP] = a_jump_right;
    m_animations[RIGHT][UP][JUMP] = a_jump_right;

        /* Gauche */
    SDL_Surface **array_jump_left;
    array_jump_left = new SDL_Surface*[1];

    array_jump_left[0] = babar_static_left;

    Animation *a_jump_left;
    a_jump_left = new Animation(1, array_jump_left);

    m_animations[LEFT][DOWN][JUMP] = a_jump_left;
    m_animations[LEFT][MIDDLE_v][JUMP] = a_jump_left;
    m_animations[LEFT][UP][JUMP] = a_jump_left;

        /* Milieu : ... */
    m_animations[MIDDLE_h][DOWN][JUMP] = a_jump_left;
    m_animations[MIDDLE_h][MIDDLE_v][JUMP] = a_jump_left;
    m_animations[MIDDLE_h][UP][JUMP] = a_jump_left;
}

Babar::~Babar()
{

}

void Babar::update_speed()
{
    if ((m_pos.y+m_pos.h)<bottom) {         /* On regarde si Babar ne touche pas le sol => on remplacera avec des collision de static */
        m_speed.y += GRAVITE;
    }
    else {
        m_pos.y = bottom-m_pos.h+1;         /* Si il est sur le sol, on fixe sa position */
    }

    m_speed.x = 0;                          /* Pour pouvoir se diriger (ttlt) */
    if (Events_stat.key_down(k_left))
        m_speed.x -= BABAR_SPEED;
    if (Events_stat.key_down(k_right))
        m_speed.x += BABAR_SPEED;

}

void Babar::update_state()
{
    m_horizontal = MIDDLE_h;
    m_vertical = MIDDLE_v;
    if(m_state != JUMP) {
        m_state = STATIC;
    }
	if (Events_stat.key_down(k_left)) {
		m_horizontal = LEFT;
		m_last_dir = LEFT;
	}
	if (Events_stat.key_down(k_right)) {
		m_horizontal = RIGHT;
		m_last_dir = RIGHT;
	}
	if (Events_stat.key_down(k_up)) {
		m_vertical = UP;
	}
	if (Events_stat.key_down(k_down)) {
		m_vertical = DOWN;
	}
    if (Events_stat.key_down(k_jump)&&(m_state!=JUMP)) {    /* Début du saut */
        m_state = JUMP;
        m_speed.y = -5*BABAR_SPEED; /* Vitesse de saut */
    }
    if ((m_pos.y+m_pos.h)>bottom) {                           /* On remet le bon état à la fin du saut */
        m_state = STATIC;
    }
    if ((Events_stat.key_down(k_right)||Events_stat.key_down(k_left))&&(m_state!=JUMP)) {
        m_state = WALK;
    }

}


/*********************************
**	Méthodes de Monster	**
**********************************/

Monster::Monster()
{

}

Monster::Monster(uint32_t type, SDL_Rect pos, uint32_t area)
{
    SDL_Surface **array_static;
    array_static = new SDL_Surface*[1];

	m_pos = pos;
	m_area = area;
	m_type = type;
	m_nb_animations = 1;
	m_last_dir = MIDDLE_h;

	array_static[0] = SDL_LoadBMP("../pic/blob.bmp");
    SDL_SetColorKey(array_static[0], SDL_SRCCOLORKEY, SDL_MapRGB(array_static[0]->format, 0, 0, 255));

    Animation *a_static;
    a_static = new Animation(1, array_static);
    m_animations[MIDDLE_h][MIDDLE_v][0] = a_static; /* Attention on prend pas tout en compte ici... */
}

Monster::~Monster()
{
}

void Monster::update_speed()
{
	if (m_phase % m_area < m_area / 2)
		m_speed.x = 5;
	else
		m_speed.x = -5;
}
