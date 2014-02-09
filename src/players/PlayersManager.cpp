
#include "PlayersManager.h"
#include "actors/Babar.h"

PlayersManager::PlayersManager()
{
    m_players = new std::list<Player*>();
    m_local_player = NULL;
    m_name = "Peanut&Co Player";
    m_map = "";
}

PlayersManager::~PlayersManager()
{
    last_peanuts = m_local_player->get_actor()->peanuts();
    last_lifes = m_local_player->get_actor()->lifes();
    delete m_players;
    delete m_local_player;
}

void PlayersManager::init_players_manager (Analyser * analyser)
{
    /* creation du joueur local */
    delete m_local_player;
    m_local_player = new Player (/* TODO */ 0, analyser, true);
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

Babar *PlayersManager::closer_babar (Rect pos)
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

std::string PlayersManager::playerName()
{
    return m_name;
}

void PlayersManager::setMap (std::string map_name)
{
    m_map = map_name;
}

std::string PlayersManager::getMap()
{
    return m_map;
}
