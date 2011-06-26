
#include "Explosion.h"
#include "../sprites/SpritesManager.h"

Explosion::Explosion(Rect pos, direction h, unsigned int damage)
{
    PRINT_CONSTR(2, "Construction de Explosion");
    m_pos = pos;
    m_dir = h;
    m_damage = damage;
	m_life_span = EXPLOSION_LIFE_SPAN;
    std::string rep = PIC_PROJ_R;

    m_sprite = gGraphics->get_sprites_manager()->add_anim(PIC_ANIMATIONS_R+"boom/boom", ENDED, MIDDLEGROUND, true);
    m_sprite->set_pos(m_pos);
	m_pos.h = m_sprite->h();
	m_pos.w = m_sprite->w();

	m_dead = false;
	m_phase = 0;
	m_invincible = true;
}

Explosion::~Explosion()
{
    PRINT_CONSTR(2, "Destruction de Explosion");
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
        Sprite * smoke = gGraphics->get_sprites_manager()->add_anim(PIC_ANIMATIONS_R+"end_boom/end_boom", ENDED, MIDDLEGROUND, true);
        smoke->set_pos(m_pos);
    }
}
