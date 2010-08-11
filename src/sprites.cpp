
#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "sprites.h"
#include "globals.h"
#include "events.h"
#include "analyser.h"


/*********************************
**	Méthodes de Sprite 	**
**********************************/
Sprite::Sprite()
{
	Analyser analyser;
	m_pos.x = 10;
	m_pos.y = 1800;
	m_pos.w = 0;
	m_pos.h = 0;
	m_speed.x = 0;
	m_speed.y = 0;
	m_cache = true;
	m_horizontal = MIDDLE_h;
	m_vertical = MIDDLE_v;
	m_state = STATIC;
	m_phase = 0;
}

Sprite::~Sprite()
{

}

void Sprite::update_pos()
{
	m_pos.x += m_speed.x;
	m_pos.y += m_speed.y;
	m_phase++;
	if (m_pos.x < 0)
		m_pos.x = 0;
	if (m_pos.y < m_pos.h)
		m_pos.y = m_pos.h;
	if ((uint32_t)m_pos.x  > curr_lvl.level_weight())
		m_pos.x =  curr_lvl.level_weight();
	if ((uint32_t)(m_pos.y + m_pos.h) > curr_lvl.level_height())
		m_pos.y =  curr_lvl.level_height() - m_pos.h;
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

uint32_t Sprite::phase()
{
    return m_phase;
}


/*********************************
**	Méthodes de Babar 	**
**********************************/
Babar::Babar()
{
    m_pos.w = 163;
	m_pos.h = 234;
	m_last_dir = LEFT;

    /*** Stockage et chargement dans le tableau des images ***/

    for(int i = 0; i<3;i++) {
        for(int j = 0;j<2;j++) {
            m_pics[STATIC][LEFT][i][j] = SDL_LoadBMP("../pic/videl_static_left_0.bmp");
            m_pics[STATIC][MIDDLE_h][i][j] = SDL_LoadBMP("../pic/videl_static_left_0.bmp");
        }
    }
    for(int i = 0; i<3;i++) {
        for(int j = 0;j<2;j++) {
            m_pics[STATIC][RIGHT][i][j] = SDL_LoadBMP("../pic/videl_static_right_0.bmp");
        }
    }
    /***/
    for(int i = 0; i<3;i++) {
            m_pics[WALK][LEFT][i][0] = SDL_LoadBMP("../pic/videl_walk_left_0.bmp");
            m_pics[WALK][MIDDLE_h][i][0] = SDL_LoadBMP("../pic/videl_walk_left_0.bmp");
    }
    for(int i = 0; i<3;i++) {
            m_pics[WALK][LEFT][i][1] = SDL_LoadBMP("../pic/videl_walk_left_1.bmp");
            m_pics[WALK][MIDDLE_h][i][1] = SDL_LoadBMP("../pic/videl_walk_left_1.bmp");
    }
    for(int i = 0; i<3;i++) {
            m_pics[WALK][RIGHT][i][0] = SDL_LoadBMP("../pic/videl_walk_right_0.bmp");
    }
    for(int i = 0; i<3;i++) {
            m_pics[WALK][RIGHT][i][1] = SDL_LoadBMP("../pic/videl_walk_right_1.bmp");
    }
    /***/
    for(int i = 0; i<3;i++) {
        for(int j = 0;j<2;j++) {
            m_pics[JUMP][LEFT][i][j] = SDL_LoadBMP("../pic/videl_jump_left_0.bmp");
            m_pics[JUMP][MIDDLE_h][i][j] = SDL_LoadBMP("../pic/videl_jump_left_0.bmp");
        }
    }
    for(int i = 0; i<3;i++) {
        for(int j = 0;j<2;j++) {
            m_pics[JUMP][RIGHT][i][j] = SDL_LoadBMP("../pic/videl_jump_right_0.bmp");
        }
    }

    for(int i = 0;i<3;i++) {
	    for(int j = 0;j<3;j++) {
	        for(int k = 0;k<3;k++) {
	            for(int l = 0;l<2;l++) {
	                SDL_SetColorKey(m_pics[i][j][k][l], SDL_SRCCOLORKEY, SDL_MapRGB(m_pics[i][j][k][l]->format, 0, 0, 255));
	            }
	        }
	    }
	}
}

Babar::~Babar()
{
    for(int i = 0;i<3;i++) {
	    for(int j = 0;j<3;j++) {
	        for(int k = 0;k<3;k++) {
	            for(int l = 0;l<2;l++) {
	                SDL_FreeSurface(m_pics[i][j][k][l]);
	            }
	        }
	    }
	}
}

SDL_Surface *Babar::current_picture()
{
    return m_pics[m_state][m_last_dir][m_vertical][(m_phase/ANIMATION_SPEED)%2];
}

void Babar::update_speed()
{
    //~ uint32_t x = m_pos.x;
    //~ uint32_t y = m_pos.y;
    //~ uint32_t xx = m_pos.x/BOX_SIZE;
    //~ uint32_t yy = m_pos.y/BOX_SIZE;
    //~ uint32_t a = curr_lvl.collision(m_pos.x,m_pos.y);

    if ((curr_lvl.collision(m_pos.x,m_pos.y)!=1)) {         /* On regarde si Babar ne touche pas le sol => on remplacera avec des collision de static */
        m_speed.y += GRAVITE;
    }
    else {
        if (m_speed.y<0) {
            m_pos.y = 1900;
            m_speed.y = 0;
        }
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
    if ((m_pos.y + m_pos.h) > (int32_t)bottom) {                           /* On remet le bon état à la fin du saut */
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
	m_pos = pos;
	m_area = area;
	m_type = type;
	m_pic = SDL_LoadBMP("../pic/blob.bmp");
}

Monster::~Monster()
{
}

SDL_Surface *Monster::current_picture()
{
    return m_pic;
}

void Monster::update_speed()
{
	if (m_phase % m_area < m_area / 2)
		m_speed.x = 5;
	else
		m_speed.x = -5;
}

void Monster::set_pos_x(uint32_t x)
{
	m_pos.x = x;
}

void Monster::set_pos_y(uint32_t y)
{
	m_pos.y = y;
}


/**************************
**  Méthodes projectiles **
**************************/

Projectile::Projectile()
{

}

Projectile::Projectile(SDL_Rect pos, horizontal h, vertical v)
{
    m_pos = pos;
    m_horizontal = h;
    m_vertical = v;

    /*** Remplissage des images des projectiles (voir level.ccp) ***/
    if(((h == LEFT)&&(v == UP))||((h == RIGHT)&&(v == DOWN))) {
        m_pic = curr_lvl.proj(0);
    }
    if(((h == LEFT)&&(v == MIDDLE_v))||((h == RIGHT)&&(v == MIDDLE_v))) {
        m_pic = curr_lvl.proj(1);
    }
    if(((h == LEFT)&&(v == DOWN))||((h == RIGHT)&&(v == UP))) {
        m_pic = curr_lvl.proj(2);
    }
    if(((h == MIDDLE_h)&&(v == UP))||((h == MIDDLE_h)&&(v == DOWN))) {
        m_pic = curr_lvl.proj(3);
    }
}

Projectile::~Projectile()
{

}
