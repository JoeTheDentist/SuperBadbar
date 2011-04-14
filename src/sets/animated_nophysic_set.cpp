
#include "animated_nophysic_set.h"
#include "../sprites/sprites_manager.h"

Animated_nophysic_set::Animated_nophysic_set(std::string anim_name, int x, int y)
{
    m_pos.x = x;
    m_pos.y = y;
    m_sprite = gSprites->add_anim("animations/"+anim_name, CYCLE, MIDDLEGROUND);
    m_sprite->set_pos(m_pos);
	m_pos.h = m_sprite->h();
	m_pos.w = m_sprite->w();
}

Animated_nophysic_set::~Animated_nophysic_set()
{

}
