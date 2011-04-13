
#include "animated_set.h"


Animated_set::Animated_set()
{
    m_pos = {0,0,0,0};
    m_speed = {0,0,0,0};
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
}

void Animated_set::update_speed()
{
    /* rien à faire si non redéfinie */
}
