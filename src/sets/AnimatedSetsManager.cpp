
#include <string>

#include "AnimatedSetsManager.h"
#include "AnimatedNophysicSet.h"
#include "AnimatedPhysicSet.h"


AnimatedSetManager::AnimatedSetManager()
{
    m_sets = new std::list<AnimatedSet*>();
}

AnimatedSetManager::~AnimatedSetManager()
{
    clear();
    delete m_sets;
}

void AnimatedSetManager::add(AnimatedSet * set)
{
    m_sets->push_front(set);
}

void AnimatedSetManager::add_set(std::string anim_name, int x, int y, bool rand_pic, bool ended, bool to_delete)
{
    AnimatedSet * set = new AnimatedNophysicSet(anim_name, x, y, ended, to_delete);
    if ( rand_pic ) {
        set->rand_pic();
    }
    add(set);
}

void AnimatedSetManager::add_set(std::string anim_name, Rect pos, Rect speed)
{
    AnimatedSet * set = new AnimatedPhysicSet(anim_name, pos, speed);
    add(set);
}

void AnimatedSetManager::update()
{
    for (std::list<AnimatedSet*>::iterator it=m_sets->begin(); it!=m_sets->end(); ) {
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

void AnimatedSetManager::clear()
{
    for (std::list<AnimatedSet*>::iterator it=m_sets->begin(); it!=m_sets->end(); ) {
        delete (*it);
        (*it) = NULL;
        it = m_sets->erase(it);
    }
}

void AnimatedSetManager::load_sets(Analyser * a)
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
