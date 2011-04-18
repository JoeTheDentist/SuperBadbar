
#include "animated_physic_set.h"
#include "../sprites/sprites_manager.h"

Animated_physic_set::Animated_physic_set(std::string anim_name, Rect pos, Rect speed)
{
    m_pos = pos;
    m_speed = speed;
    m_sprite = gGraphics->get_sprites_manager()->add_anim(anim_name, CYCLE, MIDDLEGROUND);
    m_sprite->set_pos(m_pos);
	m_pos.h = m_sprite->h();
	m_pos.w = m_sprite->w();
}

Animated_physic_set::~Animated_physic_set()
{

}

void Animated_physic_set::update_pos()
{
    gCollision->get_matrix()->update_pos(m_pos, m_speed);

    m_sprite->set_pos(m_pos);
	m_pos.h = m_sprite->h();
	m_pos.w = m_sprite->w();
}

void Animated_physic_set::update_speed()
{
    /* gravite */
    m_speed.y += GRAVITE;
    /* continuité en x */
    m_speed.x = (9*m_speed.x)/10;
}
