#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "babar.h"
#include "../util/debug.h"
#include "../game/game.h"
#include "../util/collisions.h"
#include "../util/globals.h"
#include "../control/keyboard.h"
#include "../game/static_data.h"
#include "../game/dynamic_data.h"


/*********************************
**	Méthodes de Babar 	**
**********************************/
Babar::Babar(List<Projectile*> *projectiles_friend, Keyboard *keyboard, Static_data *static_data, Sound_manager *sound_manager) : m_keyboard(keyboard), m_weapon(MACHINEGUN, projectiles_friend, static_data->proj_pics(), sound_manager)
{
	std:string rac = RAC;
	PRINT_CONSTR(1, "Construction de Babar")
	m_pos.x = 0;
	m_pos.y = 1600;
	m_invincible = 0;
	m_lifes = 5;
	m_last_dir = LEFT;
	m_fire_phase = 0;
	m_double_jump = false;
	m_sound_manager = sound_manager;
	m_fly = false;

    /*** Stockage et chargement dans le tableau des images ***/

    load(1);
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

void Babar::load(char age)
{
    char age_c = '0', i_c = '0';
    age_c += age;
    std:string rac = RAC;

    /** Charge static **/
    for(int i = 0;i<3;i++) {
        for(int j = 0;j<4;j++) {
            m_pics[STATIC][LEFT][i][j] = SDL_LoadBMP((rac+"/pic/babar_"+age_c+"_walk_left_1.bmp").c_str());
        }
    }
    string test = (rac+"/pic/babar_"+age_c+"_walk_left_2.bmp").c_str();

    for(int i = 0;i<3;i++) {
        for(int j = 0;j<4;j++) {
            m_pics[STATIC][RIGHT][i][j] = SDL_LoadBMP((rac+"/pic/babar_"+age_c+"_walk_right_1.bmp").c_str());
        }
    }
    for(int i = 0;i<3;i++) {    /* don't care */
        for(int j = 0;j<4;j++) {
            m_pics[STATIC][MIDDLE_h][i][j] = SDL_LoadBMP((rac+"/pic/babar_"+age_c+"_walk_left_1.bmp").c_str());
        }
    }

    /** Charge walk **/
    for(int i = 0;i<3;i++) {
        for(int j = 0;j<4;j++) {
            char num = i_c+j+1;
            m_pics[WALK][LEFT][i][j] = SDL_LoadBMP((rac+"/pic/babar_"+age_c+"_walk_left_"+num+".bmp").c_str());
        }
    }
    for(int i = 0;i<3;i++) {
        for(int j = 0;j<4;j++) {
            char num = i_c+j+1;
            m_pics[WALK][RIGHT][i][j] = SDL_LoadBMP((rac+"/pic/babar_"+age_c+"_walk_right_"+num+".bmp").c_str());
        }
    }
    for(int i = 0;i<3;i++) {    /* don't care */
        for(int j = 0;j<4;j++) {
            m_pics[WALK][MIDDLE_h][i][j] = SDL_LoadBMP((rac+"/pic/babar_"+age_c+"_walk_left_1.bmp").c_str());
        }
    }

    /** Charge jump **/
    for(int i = 0;i<3;i++) {
        for(int j = 0;j<4;j++) {
            m_pics[JUMP][LEFT][i][j] = SDL_LoadBMP((rac+"/pic/babar_"+age_c+"_walk_left_2.bmp").c_str());
        }
    }
    for(int i = 0;i<3;i++) {
        for(int j = 0;j<4;j++) {
            m_pics[JUMP][RIGHT][i][j] = SDL_LoadBMP((rac+"/pic/babar_"+age_c+"_walk_right_2.bmp").c_str());
        }
    }
    for(int i = 0;i<3;i++) {    /* don't care */
        for(int j = 0;j<4;j++) {
            m_pics[JUMP][MIDDLE_h][i][j] = SDL_LoadBMP((rac+"/pic/babar_"+age_c+"_walk_left_2.bmp").c_str());
        }
    }

    m_pos.w = m_pics[0][0][0][0]->w;
	m_pos.h = m_pics[0][0][0][0]->h;

    /* Transparence */
    for(int i = 0;i<3;i++) {
	    for(int j = 0;j<3;j++) {
	        for(int k = 0;k<3;k++) {
	            for(int l = 0;l<4;l++) {
	                SDL_SetColorKey(m_pics[i][j][k][l], SDL_SRCCOLORKEY, SDL_MapRGB(m_pics[i][j][k][l]->format, 0, 0, 255));
	            }
	        }
	    }
	}
}

SDL_Surface *Babar::current_picture()
{
	if ((m_invincible <= 0 || m_invincible%2 == 0))
		return m_pics[m_state][m_last_dir][m_vertical][(m_phase/ANIMATION_SPEED)%4];
	else
		return NULL;
}

void Babar::update_speed()
{
	if (m_fly)
		m_speed.y = GRAVITE/5;
	else
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
		m_fly = false;
    }
	if (m_fly && m_keyboard->key_down(k_jump)) {
		m_keyboard->disable_key(k_jump);
		m_fly = false;
	}
   	//~ if (m_keyboard->key_down(k_action)) {
		//~ talks.load_and_display_text("test.dial");
	//~ }

	update_direction();
	
	if(can_fly()) {
		fly();
	} 
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
	if (m_invincible > 0)
		m_invincible --;
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
	m_keyboard->disable_key(k_jump);

}

bool Babar::can_jump()
{
	return m_keyboard->key_down(k_jump) && (m_state!=JUMP) && !m_keyboard->key_down(k_down);
}

void Babar::fly() 
{
	m_keyboard->disable_key(k_jump);
	PRINT_DEBUG(1, "yooo");
	m_fly = true;
}

bool Babar::can_fly()
{
	return m_double_jump && m_keyboard->key_down(k_jump);
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

void Babar::damage(int damages)
{
	PRINT_TRACE(2, "Babar bobo")
	if (!is_invincible()) {
		m_sound_manager->play_babar_rugissement();
		m_lifes -= damages;
		m_invincible = 20;

	}
}

bool Babar::is_invincible()
{
	return m_invincible > 0;
}

int Babar::lifes()
{
	return m_lifes;
}

int Babar::munitions()
{
	return m_weapon.munitions();
}

weapon_type Babar::type_of_weapon()
{
	return m_weapon.type_of_weapon();
}


