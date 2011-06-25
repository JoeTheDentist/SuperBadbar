
#include "PlayersManager.h"
#include "../actors/babar.h"

PlayersManager::PlayersManager()
{
    m_players = new std::list<Player*>();
    m_local_player = NULL;
}

PlayersManager::~PlayersManager()
{
    last_peanuts = m_local_player->get_actor()->peanuts();
    last_lifes = m_local_player->get_actor()->lifes();
    delete m_players;
    delete m_local_player;
    delete gLocal_id;
}

void PlayersManager::init_players_manager(Analyser * analyser)
{
    /* création du joueur local */
    delete m_local_player;
    gLocal_id = new int;
    *gLocal_id = 0;
    m_local_player = new Player(*gLocal_id, analyser, true);
}

void PlayersManager::update()
{
    m_local_player->get_actor()->update_pos();
    m_local_player->get_actor()->update_speed();
    m_local_player->get_actor()->update_state();
}

Babar * PlayersManager::local_player()
{
    return m_local_player->get_actor();
}

int PlayersManager::nb_players()
{
    return m_players->size();
}

Babar *PlayersManager::closer_babar(Rect pos)
{
	Babar * best_babar = local_player();
//~ 	Babar *best_babar = (*(m_players->begin()))->get_actor();
//~ 	int best_dist = norm_2(pos, best_babar->position());
//~ 	for (std::list<Player*>::iterator it = m_players->begin(); it != m_players->end(); ++it) {
//~ 		if (best_dist > norm_2(pos, (*it)->get_actor()->position())) {
//~ 			best_babar = (*it)->get_actor();
//~ 			best_dist = norm_2(pos, best_babar->position());
//~ 		}
//~ 	}
	return best_babar;
}
