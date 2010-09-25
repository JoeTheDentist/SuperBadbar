
#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>


#include "debug.h"
#include "game.h"

#include "collisions.h"

/*********************************
**	Méthodes de Sprite 	**
**********************************/
Sprite::Sprite()
{
	m_pos.x = 10;
	m_pos.y = 1700;
	m_speed.x = 0;
	m_speed.y = 0;
	m_cache = true;
	m_horizontal = MIDDLE_h;
	m_vertical = MIDDLE_v;
	m_state = WALK;
	m_phase = 0;
}

Sprite::~Sprite()
{

}

void Sprite::update_pos(Static_data *static_data)
{
	m_phase++;
	uint32_t coll;
	/* cas où le sprite descend */
	for (int32_t speed_y = m_speed.y ; speed_y > 0 ; speed_y -= BOX_SIZE){
		coll = static_data->down_collision_type(m_pos);
		if (is_down_coll(coll)){
			speed_y = 0;
			m_speed.y = 0;
			if (m_state == JUMP)
				m_state = STATIC;
		}
		else {
			m_pos.y += BOX_SIZE;
			if (m_pos.y + m_pos.h > (int32_t)static_data->static_data_height())
				m_pos.y = static_data->static_data_height() - m_pos.h;
		}
	}
	/* cas où le sprite monte */
	for (int32_t speed_y = m_speed.y ; speed_y < 0 ; speed_y += BOX_SIZE){
		if (is_up_coll(static_data->up_collision_type(m_pos))){
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
			m_pos.y -= 	BOX_SIZE;
			if(!is_down_coll(static_data->down_collision_type(m_pos)))
				m_pos.y += BOX_SIZE;
			m_pos.x += BOX_SIZE;
			if (m_pos.x + m_pos.w > (int32_t)static_data->static_data_weight())
				m_pos.x = static_data->static_data_weight() - m_pos.w;
	}
	/* cas où le sprite va à gauche */
	for (int32_t speed_x = m_speed.x ; speed_x < 0 ; speed_x += BOX_SIZE){
			m_pos.y -= 	BOX_SIZE;
			if(!is_down_coll(static_data->down_collision_type(m_pos)))
				m_pos.y += BOX_SIZE;
			m_pos.x -= BOX_SIZE;
			if (m_pos.x < 0)
				m_pos.x = 0;
	}


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
Babar::Babar(List<Projectile*> *projectiles_friend, Keyboard *keyboard, Static_data *static_data, Sound_manager *sound_manager) : m_keyboard(keyboard), m_weapon(MACHINEGUN, projectiles_friend, static_data->proj_pics(), sound_manager)
{
	PRINT_CONSTR(1, "Construction de Babar")
	m_last_dir = LEFT;
	m_fire_phase = 0;
	m_double_jump = false;
	m_sound_manager = sound_manager;

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
	m_pos.w = m_pics[0][0][0][0]->w;
	m_pos.h = m_pics[0][0][0][0]->h;

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
	PRINT_CONSTR(1, "Destruction de Babar")
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
	m_speed.y += GRAVITE;
    m_speed.x = 0;                          /* Pour pouvoir se diriger (ttlt) */
    if (m_keyboard->key_down(k_left))
        m_speed.x -= BABAR_SPEED;
    if (m_keyboard->key_down(k_right))
        m_speed.x += BABAR_SPEED;
}

void Babar::update_state(Static_data *static_data)
{
    if(m_state != JUMP) {
        m_state = STATIC;
		m_double_jump = false;
    }
   	//~ if (m_keyboard->key_down(k_action)) {
		//~ talks.load_and_display_text("test.dial");
	//~ }

	update_direction();

    if (can_fire()) {
		fire();
        m_fire_phase = 0;
    }
    else {
        m_fire_phase++;
    }

    if (can_jump())
		jump();

	if (can_double_jump())
		double_jump();

	if (can_go_down(static_data))
		go_down(static_data);

    if ((uint32_t)(m_pos.y + m_pos.h) > static_data->static_data_height()) {                           /* On remet le bon état à la fin du saut */
        m_state = STATIC;
    }
    if ((m_keyboard->key_down(k_right)||m_keyboard->key_down(k_left))&&(m_state!=JUMP)) {
        m_state = WALK;
    }
}

void Babar::update_direction()
{
	m_horizontal = MIDDLE_h;
    m_vertical = MIDDLE_v;
	if (m_keyboard->key_down(k_left)) {
		m_horizontal = LEFT;
		m_last_dir = LEFT;
	}
	if (m_keyboard->key_down(k_right)) {
		m_horizontal = RIGHT;
		m_last_dir = RIGHT;
	}

	if (m_keyboard->key_down(k_up)) {
		m_vertical = UP;
	}
	if (m_keyboard->key_down(k_down)) {
		m_vertical = DOWN;
	}
}

bool Babar::can_fire()
{
	return m_keyboard->key_down(k_fire)&&(m_fire_phase>m_weapon.reload_time());
}
                                                
void Babar::fire()
{
	PRINT_TRACE(2, "Tir de Babar")
	if(m_keyboard->key_down(k_up)||m_keyboard->key_down(k_down)) {
		m_weapon.fire(m_pos,m_horizontal,m_vertical);
	}
	else {
		m_weapon.fire(m_pos,m_last_dir,m_vertical);
	}
}

bool Babar::can_double_jump()
{
	return m_state == JUMP && m_keyboard->key_down(k_jump) && (!m_double_jump);
}

void Babar::double_jump()
{
	m_double_jump = true;
	PRINT_TRACE(2, "Double-saut de Babar")
	m_speed.y = -5*BABAR_SPEED;
	m_sound_manager->play_babar_jump();

}

bool Babar::can_jump()
{
	return m_keyboard->key_down(k_jump) && (m_state!=JUMP) && !m_keyboard->key_down(k_down);
}

void Babar::jump()
{
	m_state = JUMP;
	m_speed.y = -5*BABAR_SPEED; /* Vitesse de saut */
	PRINT_TRACE(2, "Saut de Babar")
	m_keyboard->disable_key(k_jump);
	m_sound_manager->play_babar_jump();
}

bool Babar::can_go_down(Static_data *static_data)
{
	return (m_keyboard->key_down(k_jump) && m_keyboard->key_down(k_down) && (m_state == STATIC || m_state == WALK)
				&& is_down_coll(static_data->down_collision_type(m_pos)));
}

void Babar::go_down(Static_data *static_data)
{
	m_pos.y += BOX_SIZE;
	while (is_down_coll(static_data->down_collision_type(m_pos))){
		if (static_data->double_collision(m_pos)) {
			m_pos.y -= BOX_SIZE;
			break;
		}
		else {
			m_pos.y += BOX_SIZE;
		}
	}
	m_keyboard->disable_key(k_jump);
	PRINT_TRACE(2, "Descente d'une plateforme")
}


/*********************************
**	Méthodes de Monster	**
**********************************/

Monster::Monster(Sound_manager *sound_manager)
{
	m_sound_manager = sound_manager;
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
    return m_pics[m_horizontal/2][(m_phase/ANIMATION_SPEED)%3]; /* Temp */
}


void Monster::update_speed()
{
	m_speed.y += GRAVITE;

	if (m_pos.x<m_area_begin) {
	    m_horizontal = RIGHT;
		m_speed.x = -m_speed.x;
	}
	if (m_pos.x>m_area_end) {
	    m_horizontal = LEFT;
	    m_speed.x = -m_speed.x;
	}
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

void Monster::set_pic(SDL_Surface * pic, uint32_t i, uint32_t j)
{
    m_pics[i][j] = pic;
    m_pos.h = pic->h;
    m_pos.w = pic->w;
}

void Monster::damage(uint32_t damage)
{
	PRINT_DEBUG(1, "YOOOOOOOOOOOO")
	m_sound_manager->play_monster_damage();
    m_life -= damage;
}



bool Monster::dead()
{
    return (m_life <= 0);
}

int32_t Monster::type()
{
    return m_type;
}


/**************************
**  Méthodes projectiles **
**************************/

Projectile::Projectile()
{
	PRINT_CONSTR(3, "Construction d'un projectile")
}

Projectile::Projectile(SDL_Rect pos, horizontal h, vertical v, uint32_t speedx, uint32_t speedy, uint32_t damage, SDL_Surface **pics)
{
	PRINT_CONSTR(3, "Construction d'un projectile")
    m_pos = pos;
    m_horizontal = h;
    m_vertical = v;
    m_damage = damage;

    /*** Remplissage des images des projectiles (voir static_data.ccp) ***/
    if(((h == LEFT)&&(v == UP))||((h == RIGHT)&&(v == DOWN))) {
        m_pic = pics[2];
    }
    if(((h == LEFT)&&(v == MIDDLE_v))||((h == RIGHT)&&(v == MIDDLE_v))) {
        m_pic = pics[0];
    }
    if(((h == LEFT)&&(v == DOWN))||((h == RIGHT)&&(v == UP))) {
        m_pic = pics[3];
    }
    if(((h == MIDDLE_h)&&(v == UP))||((h == MIDDLE_h)&&(v == DOWN))) {
        m_pic = pics[1];
    }

    m_pos.h = m_pic->h;
    m_pos.w = m_pic->w;

    m_speed.x = speedx;
    m_speed.y = speedy;
}

Projectile::~Projectile()
{
	PRINT_CONSTR(3, "Destruction d'un projectile")
}

SDL_Surface *Projectile::current_picture()
{
    return m_pic;
}

uint32_t Projectile::damage()
{
    return m_damage;
}

SDL_Rect Projectile::speed()
{
    return m_speed;
}


/*** Fonctions ***/

bool too_old(Projectile * p, Static_data *static_data)
{
    bool to_return = (p->phase()>PROJ_LIFE_SPAN);
    SDL_Rect speed = p->speed();
    if (speed.x>0)
        to_return |= static_data->right_collision(p->position());
    else
        to_return |= static_data->left_collision(p->position());

    if (speed.y>0)
        to_return |= static_data->down_collision(p->position());
    else
        to_return |= static_data->up_collision(p->position());
    return to_return;
}

