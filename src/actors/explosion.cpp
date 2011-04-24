
#include "explosion.h"
#include "../sprites/sprites_manager.h"

Explosion::Explosion(Rect pos, direction h, unsigned int damage)
{
    m_pos = pos;
    m_dir = h;
    m_damage = damage;
	m_life_span = EXPLOSION_LIFE_SPAN;
    std::string rep = PIC_PROJ_R;

    m_sprite = gGraphics->get_sprites_manager()->add_anim("animations/boom/boom", ENDED, MIDDLEGROUND, true);
    m_sprite->set_pos(m_pos);
	m_pos.h = m_sprite->h();
	m_pos.w = m_sprite->w();

    m_speed.x = 0;
    m_speed.y = 0;

	m_dead = false;
	m_phase = 0;
	m_invincible = true;
}

Explosion::~Explosion()
{
//    Sprite * smoke = gGraphics->get_sprites_manager()->add_anim("animations/end_boom/end_boom", ENDED, MIDDLEGROUND, true);
//    smoke->set_pos(m_pos);
}

void Explosion::update_state()
{
    if ( m_speed.x > 0 ) {
        m_dir = LEFT;
    } else {
        m_dir = RIGHT;
    }
    m_sprite->change_anim(NONE, m_dir);

    if ( m_phase == EXPLOSION_LIFE_SPAN-1) {
        Sprite * smoke = gGraphics->get_sprites_manager()->add_anim("animations/end_boom/end_boom", ENDED, MIDDLEGROUND, true);
        smoke->set_pos(m_pos);
    }
}
