
#include "animated_set.h"


Animated_set::Animated_set()
{
	m_sprite = NULL;
}

Animated_set::~Animated_set()
{
    /* ne pas toucher � m_sprite, il peut �tre d�j� d�truit */
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
    /* rien � faire si non red�finie */
}

void Animated_set::rand_pic()
{
    m_sprite->rand_pic();
}

bool Animated_set::to_delete()
{
    /*if ( m_sprite ) {
        if ( m_sprite->to_delete() ) {
            m_sprite = NULL;
            return true;
        } else {
            return false;
        }
    } else {
        return true;
    }*/
    return m_to_delete;
}
