
#include "players_manager.h"
#include "../actors/babar.h"

Players_manager::Players_manager()
{
    m_players = new std::list<Player*>();
    m_local_player = NULL;
}

Players_manager::~Players_manager()
{
    delete m_players;
    delete m_local_player;
    delete gLocal_id;
}

void Players_manager::init_players_manager(Analyser * analyser)
{
    /* création du joueur local */
    delete m_local_player;
    gLocal_id = new int;
    *gLocal_id = 0;
    m_local_player = new Player(*gLocal_id, analyser, true);
}

void Players_manager::update()
{
    m_local_player->get_actor()->update_pos();
    m_local_player->get_actor()->update_speed();
    m_local_player->get_actor()->update_state();
}

Babar * Players_manager::local_player()
{
    return m_local_player->get_actor();
}

int Players_manager::nb_players()
{
    return m_players->size();
}
