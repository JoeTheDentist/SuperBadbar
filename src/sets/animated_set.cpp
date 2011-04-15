
#include "animated_set.h"


Animated_set::Animated_set()
{
	m_pos.x = 0;
	m_pos.y = 0;
	m_pos.h = 0;
	m_pos.w = 0;
	m_speed = m_pos;
	m_sprite = NULL;
}

Animated_set::~Animated_set()
{
    if ( m_sprite ) {
        m_sprite->set_to_delete();
    }
}

void Animated_set::update_pos()
{
    m_pos.x += m_speed.x;
    m_pos.y += m_speed.y;

    m_sprite->set_pos(m_pos);
	m_pos.h = m_sprite->h();
	m_pos.w = m_sprite->w();
}

void Animated_set::update_speed()
{
    /* rien à faire si non redéfinie */
}
