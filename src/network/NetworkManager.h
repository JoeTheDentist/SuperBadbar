/**
 * 	@file NetworkManager.h
 * 	@brief header de la classe NetworkManager
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juillet 2011
 *
 */

#ifndef NETWORKMANAGER_H_INCLUDED
#define NETWORKMANAGER_H_INCLUDED

#include <string>

#include "NetworkCommunicator.h"

enum NetworkState {
    NetState_HOST, NetState_CLIENT, NetState_NONE
};

enum NetworkMode {
    NetMode_LOCAL, NetMode_INTERNET, NetMode_NONE
};

enum NetworkStep {
    NetStep_WaitForServer, NetStep_WaitForClients,
    NetStep_WaitForConnexion, NetStep_Chat,
    NetStep_LaunchingGame, NetStep_Play,
    NetStepNONE
};

struct MapInfo {
    std::string name;
    unsigned int size;
    int hash;
    unsigned int nbPlayers;
    unsigned int nbMaxPlayers;
};

/**
 *  @class NetworkManager
 *  @brief Classe principale de la partie reseau
 *
 *  Classe singleton
 *
 *  Des traces de warning sont affichée si les méthodes
 *  ne sont pas utilisées dans les bonnes conditions
 */

class NetworkManager {
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
public :

    /**
     *  @brief Constructeur
     */
    NetworkManager();

    /**
     *  @brief Destructeur
     */
    ~NetworkManager();

    /**
     *  @brief Initialisation de la classe
     */
    void initNetworkManager();

    /**
     *  @brief Etat Client
     */
    void initClient();

    /**
     *  @brief Etat Server
     */
    void initServer();

    /***************************************/
    /********Partie Decouverte**************/
    /***************************************/

    /**
     *  @brief Lance un serveur en réseau local
     *  @param lvl_name : nom de la map host
     *
     *  Une fois le server lancé, il envoie en broadcast sur
     *  le réseau des messages avertissant de son état
     */
    void startLocalServer(std::string lvl_name = "test.lvl");

    /**
     *  @brief Lance un serveur sur internet
     *  @param lvl_name : nom de la map host
     *
     *  Attends que les clients se connectent
     */
    void startInternetServer(std::string lvl_name = "test.lvl");

    /**
     *  @brief Cherche les serveurs disponibles sur le reseau (local)
     */
    void searchServer();

    /**
     *  @brief
     *  @param ip : adresse ip
     */
    void tryConnectTo(std::string ip = "127.0.0.1");


    /***************************************/
    /*********Partie Connexion**************/
    /***************************************/

    /**
     *  @brief Recupère les infos sur la map
     *  @return Info de la map
     *
     *  Les infos :
     *      Nom
     *      Taille
     *      Hash du lvl (Sha-1 Qt)
     *      Nombre de joueurs
     *      Nombre max de joueurs
     */
    MapInfo getMapInfo();


    /***************************************/
    /************Partie Chat****************/
    /***************************************/

    /**
     *  @brief Envoie un message
     *  @param msg : message à envoyer
     */
    void sendMessage(std::string msg);




    /***************************************/
    /********Partie Lancement Jeu***********/
    /***************************************/

    /**
     *  @brief Recupère et fixe l'id du reseau
     */
    void getSetId();


    /***************************************/
    /**************Partie Jeu***************/
    /***************************************/

    /***************************************/
    /****************Autres*****************/
    /***************************************/

    /**
     *  @brief Accesseur de l'IP du joueur
     *  @return adresse IP
     */
    std::string getMyIP();

    /**
     *  @brief Accesseur id sur le reseau
     *  @return identifiant sur reseau
     */
    int getMyID();

    /**
     *  @brief Info de la map choisie
     *  @param mapName : nom de la map chemin depuis levels
     *
     *  Les champs sur le nombre de joueur ne sont pas remplis
     */
    MapInfo mapInfo(std::string mapName);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
private :
    NetworkState m_netState;        /* si le jeu fait aussi serveur */
    NetworkMode m_netMode;          /* */
    NetworkStep m_netStep;          /* */
    int m_idLocal;                  /* identifiant sur le reseau */
    NetworkCommunicator *m_netCom;  /* partie communicante,serveur ou client */



    /***************************************/
    /********Partie Decouverte**************/
    /***************************************/



    /***************************************/
    /*********Partie Connexion**************/
    /***************************************/

    /**
     *  @brief Demande au serveur les infos sur la map
     *
     *  Trace de warning si NetState_CLIENT
     */
    void AskForMapInfo();

    /**
     *  @brief Attends que le serveur donne les infos sur la map
     *  @return Info sur la map
     */
    MapInfo WaitForMapInfo();

    /**
     *  @brief Demande au serveur son identifiant
     */
    void AskForId();

    /**
     *  @brief Attends que le serveur donne l'identifiant
     *  @return Identifiant, -1 si erreur ou timeout
     */
    int WaitForId();


    /***************************************/
    /***************Autres******************/
    /***************************************/

    /**
     *  @brief Mutateur
     *  @param Nouvelle valeur de l'id
     */
    void SetId(int id);
};

#endif // NETWORKMANAGER_H_INCLUDED
