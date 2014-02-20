#ifndef PLAYERS_MANAGER_H_INCLUDED
#define PLAYERS_MANAGER_H_INCLUDED

#include "Player.h"
#include "video/Surface.h"

class Analyser;
class Camera;

/**
 *  @class Player_manager
 *  @brief Classe organisant les differents joueurs
 */
class PlayersManager
{
private :
    std::list<Player*> * m_players;
    Player * m_local_player;
    std::string m_name;
    std::string m_map;

public :
    static int last_peanuts;
    static int last_lifes;

    /**
     *  @brief Constructeur
     */
    PlayersManager();

    /**
     *  @brief Destructeur
     */
    ~PlayersManager();

    /**
     *  @brief Initialisation du manager suivant des regles
     *  @param analyser : analyseur ouvert sur le fichier .lvl correstpondant
     *  TODO : Si on veut des modes de jeux, il faudrait changer ici.
     *  TODO : Par exemple on pourrait faire un joueur allie avec les
     *  TODO : monstres contre les autres etc etc...
     *  TODO : On pourra mettre les regles dans un fichier xml...
     */
    void init_players_manager (Analyser * analyser);

    /**
     *  @brief Mise a jour des joueurs
     *  Mise a jour des positions, vitesses et etats !
     *  C'est ici que la partie reseau va avoir un point d'acces
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
    Babar *closer_babar (Rect pos);

    /**
     *  @brief Accesseur
     *  @return nom du joueur
     */
    std::string playerName();

    /**
     *  Mutateur
     *  @param map_name : nom de la map courante
     */
    void setMap (std::string map_name);

    /**
     *  Accesseur
     *  @return nom de la map courante
     */
    std::string getMap();
};

#endif // PLAYERS_MANAGER_H_INCLUDED
