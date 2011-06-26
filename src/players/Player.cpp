
#include "Player.h"
#include "../actors/Babar.h"
#include "../events/Stats.h"


Player::Player(int id, Analyser * analyser, bool local)
{
    m_dmgs = new std::list<dmg_chan>();

    m_id = id;

    if ( local ) {
        m_actor = new Babar(analyser);
    } else {
        /*m_actor = new Another_Babar();*/
    }
}

Player::~Player()
{
    m_dmgs->clear();
    delete m_dmgs;
    delete m_actor;
}

Babar * Player::get_actor()
{
    return m_actor;
}

int Player::get_id()
{
    return m_id;
}

std::list<dmg_chan> * Player::get_dmgs()
{
    return m_dmgs;
}

void Player::set_dmgs(dmg_chan dmg)
{
    m_dmgs->push_front(dmg);
}
