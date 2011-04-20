
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
    clear();
    delete m_sets;
}

void Animated_set_manager::add(Animated_set * set)
{
    m_sets->push_front(set);
}

void Animated_set_manager::add_set(std::string anim_name, int x, int y, bool rand_pic, bool ended)
{
    Animated_set * set = new Animated_nophysic_set(anim_name, x, y, ended);
    if ( rand_pic ) {
        set->rand_pic();
    }
    add(set);
}

void Animated_set_manager::add_set(std::string anim_name, Rect pos, Rect speed)
{
    Animated_set * set = new Animated_physic_set(anim_name, pos, speed);
    add(set);
}

void Animated_set_manager::update()
{
    for (std::list<Animated_set*>::iterator it=m_sets->begin(); it!=m_sets->end(); ) {
        if ( (*it)->to_delete() ) {
            delete (*it);
            (*it) = NULL;
            it = m_sets->erase(it);
        } else {
            (*it)->update_speed();
            (*it)->update_pos();
            ++it;
        }
    }
}

void Animated_set_manager::clear()
{
    for (std::list<Animated_set*>::iterator it=m_sets->begin(); it!=m_sets->end(); ) {
        delete (*it);
        (*it) = NULL;
        it = m_sets->erase(it);
    }
}

void Animated_set_manager::load_sets(Analyser * a)
{
    a->find_string("#Sets#");
    int nb_sets = a->read_int();
	for (int i = 0; i < nb_sets; i++) {
		std::string name = a->read_string();
		int x = a->read_int();
		int y = a->read_int();
		add_set(name, x, y, true);
	}
}
