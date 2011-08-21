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
 *  @brief Classe permettant de signaler et r�cuperer
 *          des �v�nements sur le r�seau
 *
 *  Doit �tre h�rit�e dans tous les objets ayant des informations
 *  que le r�seau doit connaitre.
 *  Cette classe enregistre les actions � transmettre sur le r�seau
 *  et confirme � la r�ponse du serveur (l'objet vas lire � l'update)
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
     *  @brief Mise � jour, active l'action donn�e par le serveur
     */
    void updateNetwork();

    /**
     *  @brief Remet le compteur des entites a zero
     */
    static void ResetCounter();

    /***************************************/
    /***********Actions G�n�rales***********/
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
