
#include "AnimatedSet.h"


AnimatedSet::AnimatedSet()
{
	m_sprite = NULL;
}

AnimatedSet::~AnimatedSet()
{
    /* ne pas toucher à m_sprite, il peut être déjà détruit */
}

void AnimatedSet::update_pos()
{
    m_pos.x += m_speed.x;
    m_pos.y += m_speed.y;

    m_sprite->set_pos(m_pos);
	m_pos.h = m_sprite->h();
	m_pos.w = m_sprite->w();
}

void AnimatedSet::update_speed()
{
    /* rien à faire si non redéfinie */
}

void AnimatedSet::rand_pic()
{
    m_sprite->rand_pic();
}

bool AnimatedSet::to_delete()
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
