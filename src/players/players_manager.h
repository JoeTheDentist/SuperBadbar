#ifndef PLAYERS_MANAGER_H_INCLUDED
#define PLAYERS_MANAGER_H_INCLUDED

#include "player.h"
#include "../video/surface.h"

class Analyser;
class Camera;

/**
 *  @class Player_manager
 *  @brief Classe organisant les différents joueurs
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
         *  @brief Initialisation du manager suivant des règles
         *  @param analyser : analyseur ouvert sur le fichier .lvl correstpondant
         *  TODO : Si on veut des modes de jeux, il faudrait changer ici.
         *  TODO : Par exemple on pourrait faire un joueur allié avec les
         *  TODO : monstres contre les autres etc etc...
         *  TODO : On pourra mettre les règles dans un fichier xml...
         */
        void init_players_manager(Analyser * analyser);

        /**
         *  @brief Mise à jour des joueurs
         *  Mise à jour des positions, vitesses et états !
         *  C'est ici que la partie réseau va avoir un point d'accès
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
		
		/**
		 *	@brief Cherche le joueur le plus proche d'une position (aggro!)
		 *	@param pos La position 
		 *	@return Le babar de distance minimale avec la position
		 *	@todo Pour l'instant renvoie local_player
		 */
		Babar *closer_babar(Rect pos);
};

#endif // PLAYERS_MANAGER_H_INCLUDED
