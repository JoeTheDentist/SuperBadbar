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
    std::string mapName;
    std::string hostName;
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
public :
    /**
     *  @brief Constructeur
     */
    NetworkManager();

    /**
     *  @brief Destructeur
     */
    virtual ~NetworkManager();

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
public:

    /**
     *  @brief Lance un serveur
     *  @param lvl_name : nom de la map host
     *
     *  Attends que les clients se connectent
     *  Lance un message de pub cycliquement pour
     *  se decouvrir aux clients sur le reseau local
     */
    void startServer(std::string lvl_name = "test.lvl");

    /**
     *  @brief Cherche les serveurs disponibles sur le reseau (local)
     *
     *  Regarde si il a reçu des messages
     */
    void searchServer();

    /**
     *  @brief Tentative de connection a l'adresse IP
     *  @param ip : adresse ip
     */
    void connectTo(std::string ip = "127.0.0.1");


    /***************************************/
    /*********Partie Connexion**************/
    /***************************************/
public:
    /**
     *  @brief Recupère les infos sur la map
     *  @return Info de la map
     *
     *  Les infos :
     *      Nom de la carte
     *      Nom du joueur creant la carte
     *      Taille
     *      Hash du lvl (Sha-1 Qt)
     *      Nombre de joueurs
     *      Nombre max de joueurs
     *
     *  Erreur : tous les champs sont vides
     */
    MapInfo getMapInfo();

private:
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
    /************Partie Chat****************/
    /***************************************/
public:
    /**
     *  @brief Envoie un message
     *  @param msg : message à envoyer
     */
    void sendMessage(std::string msg);


    /***************************************/
    /********Partie Lancement Jeu***********/
    /***************************************/
public:
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
public:
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

private:
    /**
     *  @brief Mutateur
     *  @param Nouvelle valeur de l'id
     */
    void SetId(int id);

    /***************************************/
    /**************Attributs****************/
    /***************************************/
private :
    NetworkState m_netState;        /* si le jeu fait aussi serveur */
    NetworkMode m_netMode;          /* */
    NetworkStep m_netStep;          /* */
    int m_idLocal;                  /* identifiant sur le reseau */
    NetworkCommunicator *m_netCom;  /* partie communicante */

    static bool Multi;              /* si le jeu se fait en solo ou multi */
};

#endif // NETWORKMANAGER_H_INCLUDED
