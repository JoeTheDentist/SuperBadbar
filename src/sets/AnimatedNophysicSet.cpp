#include <iostream>
#include "AnimatedNophysicSet.h"
#include "sprites/SpritesManager.h"

AnimatedNophysicSet::AnimatedNophysicSet(std::string anim_name, int x, int y, bool ended, bool to_delete)
{
    m_pos.x = x;
    m_pos.y = y;
    m_sprite = NULL;
    m_to_delete = to_delete;
    if ( ended ) {
        m_sprite = gGraphics->get_sprites_manager()->add_anim(anim_name, ENDED, MIDDLEGROUND);
    } else {
        m_sprite = gGraphics->get_sprites_manager()->add_anim(anim_name, CYCLE, MIDDLEGROUND);
    }
    m_sprite->set_pos(m_pos);
	m_pos.h = m_sprite->h();
	m_pos.w = m_sprite->w();
}

AnimatedNophysicSet::~AnimatedNophysicSet()
{

}
