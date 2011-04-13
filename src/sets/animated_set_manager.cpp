
#include <string>

#include "animated_set_manager.h"
#include "animated_nophysic_set.h"
#include "animated_physic_set.h"


Animated_set_manager::Animated_set_manager()
{
    m_sets = new std::list<Animated_set*>();
}

Animated_set_manager::~Animated_set_manager()
{
    delete m_sets;
}

void Animated_set_manager::add(Animated_set * set)
{
    m_sets->push_front(set);
}

void Animated_set_manager::add_set(std::string anim_name, int x, int y)
{
    Animated_set * set = new Animated_nophysic_set(anim_name, x, y);
    add(set);
}

void Animated_set_manager::add_set(std::string anim_name, Rect pos, Rect speed)
{
    Animated_set * set = new Animated_physic_set(anim_name, pos, speed);
    add(set);
}

void Animated_set_manager::update()
{
    for (std::list<Animated_set*>::iterator it=m_sets->begin(); it!=m_sets->end(); ++it) {
        (*it)->update_speed();
        (*it)->update_pos();
    }
}

void Animated_set_manager::clear()
{
    m_sets->clear();
}
