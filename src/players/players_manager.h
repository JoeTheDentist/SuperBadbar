#ifndef PLAYERS_MANAGER_H_INCLUDED
#define PLAYERS_MANAGER_H_INCLUDED

#include "player.h"
#include "../video/camera.h"

/**
 *  @class Player_manager
 *  @brief Classe organisant les diff�rents joueurs
 */
class Players_manager {
    private :
        std::list<Player*> * m_players;
        Player * m_local_player;

    public :
        /**
         *  @brief Constructeur
         */
        Players_manager();

        /**
         *  @brief Destructeur
         */
        ~Players_manager();

        /**
         *  @brief Initialisation du manager suivant des r�gles
         *  TODO : Si on veut des modes de jeux, il faudrait changer ici.
         *  TODO : Par exemple on pourrait faire un joueur alli� avec les
         *  TODO : monstres contre les autres etc etc...
         *  TODO : On pourra mettre les r�gles dans un fichier xml...
         */
        void init_players_manager();

        /**
         *  @brief Mise � jour des joueurs
         *  Mise � jour des positions, vitesses et �tats !
         *  C'est ici que la partie r�seau va avoir un point d'acc�s
         */
        void update();

        /**
         *  @brief Joueur client
         */
        Babar * local_player();

        /**
         * @brief Nombre de joueurs
         */
        int nb_players();
};

#endif // PLAYERS_MANAGER_H_INCLUDED
