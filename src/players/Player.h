#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "../actors/ProjectilesManager.h"
class Analyser;
class Stats;
class Babar;

/**
 *  @class Player
 *  @brief Classe représentant un joueur
 */

class Player {
    private :
        Stats * m_stats;
        int m_id;
        /* acteur controlé par le joueur */
        Babar * m_actor;
        /* liste des dommages que le joueur peux se prendre */
        std::list<dmg_chan> * m_dmgs;

    public :
        /**
         *  @brief Coonstructeur
         *  @param id : numero du joueur
         *  @param local : si on crée le joueur local
         *  TODO : Quelque chose pour pouvoir choisir son skin... A faire
         *  TODO : descendre jusqu'à Babar sans doute...
         */
        Player(int id, Analyser * analyser, bool local=false);

        /**
         *  @brief Destructeur
         */
        ~Player();

        /**
         *  @brief Accesseur de m_actor
         */
        Babar * get_actor();

        /**
         *  @brief Accesseur identifiant
         */
        int get_id();

        /**
         *  @brief Accesseur affinités
         */
        std::list<dmg_chan> * get_dmgs();

        /**
         *  @brief Ajoute un nouveau type d'ennemi
         *  @param dmgs : nouvel ennemi
         */
        void set_dmgs(dmg_chan dmg);
};

#endif // PLAYER_H_INCLUDED
