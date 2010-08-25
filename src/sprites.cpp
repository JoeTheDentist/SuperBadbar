
#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "game.h"
#include "sprites.h"
#include "globals.h"
#include "events.h"
#include "analyser.h"
#include "weapons.h"

/*********************************
**	Méthodes de Sprite 	**
**********************************/
Sprite::Sprite()
{
	Analyser analyser;
	m_pos.x = 10;
	m_pos.y = 1700;
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
	//~ m_pos.x += m_speed.x;
	m_phase++;
	
	/* cas où le sprite descend */
	for (int32_t speed_y = m_speed.y ; speed_y > 0 ; speed_y -= BOX_SIZE){
		if (curr_lvl.down_collision(m_pos)){
			speed_y = 0;
			m_speed.y = 0;
			if (m_state == JUMP)
				m_state = STATIC;
		}
		else {
			m_pos.y += BOX_SIZE;
			if (m_pos.y + m_pos.h > curr_lvl.level_height())
				m_pos.y = curr_lvl.level_height() - m_pos.h;
		}
	}

	/* cas où le sprite monte */
	for (int32_t speed_y = m_speed.y ; speed_y < 0 ; speed_y += BOX_SIZE){
		if (curr_lvl.up_collision(m_pos)){
			speed_y = 0;
			m_speed.y = 0;
		}
		else {
			if (m_pos.y < 0)
				m_pos.y = 0;
			m_pos.y -= BOX_SIZE;
		}
	}

	/* cas où le sprite va à droite */
	for (int32_t speed_x = m_speed.x ; speed_x > 0 ; speed_x -= BOX_SIZE){
			m_pos.x += BOX_SIZE;
			if (m_pos.x + m_pos.w > curr_lvl.level_weight())
				m_pos.x = curr_lvl.level_weight() - m_pos.w;
	}
	
	/* cas où le sprite va à gauche */
	for (int32_t speed_x = m_speed.x ; speed_x < 0 ; speed_x += BOX_SIZE){
			m_pos.x -= BOX_SIZE;		
			if (m_pos.x < 0)
				m_pos.x = 0;
	}

	//~ if (m_pos.x < 0)
		//~ m_pos.x = 0;
	//~ if (m_pos.y < m_pos.h)
		//~ m_pos.y = m_pos.h;y	//~ if ((uint32_t)m_pos.x  > curr_lvl.level_weight())
		//~ m_pos.x =  curr_lvl.level_weight();
	//~ if ((uint32_t)(m_pos.y + m_pos.h) > curr_lvl.level_height())
		//~ m_pos.y =  curr_lvl.level_height() - m_pos.h;
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

	m_last_dir = LEFT;
	m_fire_phase = 0;
	m_weapon = Weapon(SHOTGUN);

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
	m_pos.w = m_pic[0][0][0]->w;
	m_pos.h = m_pic[0][0][0]->h;
    /* Transparence */
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
	fprintf(stderr, "hauteur de babar: %d", m_pos.y);

	m_speed.y += GRAVITE;


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

    if (Events_stat.key_down(k_fire)&&(m_fire_phase>m_weapon.reload_time())) {
        if(Events_stat.key_down(k_up)||Events_stat.key_down(k_down)) {
            m_weapon.fire(m_pos,m_horizontal,m_vertical);
        }
        else {
            m_weapon.fire(m_pos,m_last_dir,m_vertical);
        }
        m_fire_phase = 0;
    }
    else {
        m_fire_phase++;
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

Monster::Monster(uint32_t type, SDL_Rect pos)
{
	m_pos = pos;
	m_type = type;
}

Monster::~Monster()
{
}

SDL_Surface *Monster::current_picture()
{
    return m_pics[0][0][0]; /* Temp */
}

void Monster::update_speed()
{
	if (m_pos.x<m_area_begin||m_pos.x>m_area_end)
		m_speed.x = -m_speed.x;
}

void Monster::set_pos_x(uint32_t x)
{
	m_pos.x = x;
}

void Monster::set_pos_y(uint32_t y)
{
	m_pos.y = y;
}

void Monster::set_type(uint32_t type)
{
    m_type = type;
}

void Monster::set_life(uint32_t life)
{
    m_life = life;
}

void Monster::set_begin(uint32_t begin)
{
    m_area_begin = begin;
}

void Monster::set_end(uint32_t end)
{
    m_area_end = end;
}

void Monster::set_fire(bool can_fire)
{
    m_can_fire = can_fire;
}

void Monster::set_speed(uint32_t speed)
{
    m_speed_def = speed;
    m_speed.x = speed;
}

void Monster::set_pic(SDL_Surface * pic, uint32_t i, uint32_t j, uint32_t k)
{
    m_pics[i][j][k] = pic;
    m_pos.h = pic->h;
    m_pos.w = pic->w;
}

void Monster::damage(uint32_t damage)
{
    m_life -= damage;
}

bool Monster::dead()
{
    return (m_life <= 0);
}

uint32_t Monster::type()
{
    return m_type;
}


/**************************
**  Méthodes projectiles **
**************************/

Projectile::Projectile()
{

}

Projectile::Projectile(SDL_Rect pos, horizontal h, vertical v, uint32_t speedx, uint32_t speedy, uint32_t damage)
{
    m_pos = pos;
    m_horizontal = h;
    m_vertical = v;
    m_damage = damage;

    /*** Remplissage des images des projectiles (voir level.ccp) ***/
    if(((h == LEFT)&&(v == UP))||((h == RIGHT)&&(v == DOWN))) {
        m_pic = game.proj(2);
    }
    if(((h == LEFT)&&(v == MIDDLE_v))||((h == RIGHT)&&(v == MIDDLE_v))) {
        m_pic = game.proj(0);
    }
    if(((h == LEFT)&&(v == DOWN))||((h == RIGHT)&&(v == UP))) {
        m_pic = game.proj(3);
    }
    if(((h == MIDDLE_h)&&(v == UP))||((h == MIDDLE_h)&&(v == DOWN))) {
        m_pic = game.proj(1);
    }

    m_pos.h = m_pic->h;
    m_pos.w = m_pic->w;

    m_speed.x = speedx;
    m_speed.y = speedy;
}

Projectile::~Projectile()
{

}

SDL_Surface *Projectile::current_picture()
{
    return m_pic;
}

uint32_t Projectile::damage()
{
    return m_damage;
}


/*** Fonctions ***/

bool too_old(Projectile * p)
{
    return p->phase()>PROJ_LIFE_SPAN;
}
