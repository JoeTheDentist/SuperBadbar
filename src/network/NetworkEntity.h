/**
 * 	@file NetworkEntity.h
 * 	@brief header de la classe NetworkEntity
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juillet 2011
 *
 */

#ifndef NETWORKENTITY_H
#define NETWORKENTITY_H

/**
 *  @class NetworkEntity
 *  @brief Classe permettant de signaler et récuperer
 *          des évènements sur le réseau
 *
 *  Doit être héritée dans tous les objets ayant des informations
 *  que le réseau doit connaitre.
 *  Cette classe enregistre les actions à transmettre sur le réseau
 *  et confirme à la réponse du serveur (l'objet vas lire à l'update)
 *
 *  Lorsque le jeu est simple joueur cette classe est transparente
 */
class NetworkEntity
{
public:

    /**
     *  @brief Constructeur
     */
    NetworkEntity();

    /**
     *  @brief Destructeur
     */
    virtual ~NetworkEntity();

    /**
     *  Accesseur
     */
    int id();

public:
    /**
     *  @brief Mise à jour, active l'action donnée par le serveur
     */
    void updateNetwork();

    /**
     *  @brief Remet le compteur des entites a zero
     */
    static void ResetCounter();

    /***************************************/
    /***********Actions Générales***********/
    /***************************************/
protected:
    /**
     *  @brief Signaler la mort
     */
    void sigKilled();

    /***************************************/
    /**********Actions pour l'update********/
    /***************************************/
protected:
    /**
     *  @brief Demande suppression
     */
    void killed();

    /**
     *  Ne rien faire
     */
    void doNothing() {}

    /***************************************/
    /***************Variables***************/
    /***************************************/
protected:
    static unsigned int NetworkEntitiesCounter;
    unsigned int m_id;
    void (NetworkEntity::*actionToActivate)(); //ptr de methode


};

#endif // NETWORKENTITY_H
