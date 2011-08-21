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
#include <QMap>

class NetworkEntity;
class NetworkCommunicator;

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
     *
     *  Attends que les clients se connectent
     *  Lance un message de pub cycliquement pour
     *  se decouvrir aux clients sur le reseau local
     */
    void startServer();

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
    void connectTo(const std::string &ip = "127.0.0.1");

    /**
     *  Nouveau serveur découvert
     *  @param ip : adresse ip de l'expediteur
     *  @param adMsg : message de pub
     */
    void addAd(const std::string &ip, const std::string &adMsg);


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
     *  @brief Accesseur
     *  @return si le jeu fait serveur
     */
    bool isServer();

    /**
     *  @brief Info de la map choisie
     *  @param mapName : nom de la map chemin depuis levels
     *
     *  TODO changer d'endroit
     *  Les champs sur le nombre de joueur ne sont pas remplis
     */
    MapInfo mapInfo(const std::string &mapName);

    /**
     *  @brief Retourne l'adresse IP
     *  @return adresse IP
     */
    std::string getIP();

private:
    /**
     *  @brief Mutateur
     *  @param Nouvelle valeur de l'id
     */
    void setId(int id);

public:
    /**
     *  Ajout d'une entite reseau
     *  @param ne : entity a ajouter
     */
    void addEntity(NetworkEntity *ne);

    /***************************************/
    /**************Attributs****************/
    /***************************************/
private :
    NetworkStep m_netStep;          //
    int m_idLocal;                  // identifiant sur le reseau
    NetworkCommunicator *m_netCom;  // partie communicante
    std::map<int, NetworkEntity*> m_entities;
    std::map<std::string, std::string> m_servers; //ip, nom a afficher
    bool m_server;                  // si le jeu fait serveur aussi
    int m_id_menu;  // identifiant du menu
};

#endif // NETWORKMANAGER_H_INCLUDED
