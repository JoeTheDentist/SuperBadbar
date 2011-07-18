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

#include "../items/Weapon.h"

enum NetworkType {
    NetType_MONSTER, NetType_PLAYER, NetType_EVENT,
    NetType_TRIGGER
};

/**
 *  @class NetworkEntity
 *  @brief Classe permettant de signaler des évènements sur le réseau
 *
 *  Doit être contenue dans tous les objets ayant des informations
 *  que le réseau doit connaitre
 */
class NetworkEntity
{
public:

    /**
     *  @brief Constructeur
     *  @param type : Type d'entité
     */
    NetworkEntity(NetworkType type);

    /**
     *  @brief Destructeur
     */
    virtual ~NetworkEntity();

    /**
     *  @brief Remet le compteur des entités à zéro
     */
    static void ResetCounter();


    /***************************************/
    /****************Actors*****************/
    /***************************************/

    /**
     *  @brief Signale un saut
     */
    void sigJump();

    /**
     *  @brief Signale un tir
     */
    void sigFire();

    /**
     *  @brief Signale l'accroupissement
     */
    void sigCrouch();

    /**
     *  @brief Signale un changement d'arme
     *  @param weapon : nouvelle arme
     */
    void sigChangeWeaponTo(weapon_type weapon);

    /**
     *  @brief Signale la capture d'un objet
     *  @param idItem : identifiant de l'item pris
     */
    void sigItemCaught(unsigned int idItem);

    /**
     *  @brief Signale la position, l'état et la direction
     */
    void sigState(Rect pos, int state, direction dir);

    /**
     *  @brief Signale la mort de l'acteur
     */
    void sigDeath();


    /***************************************/
    /*****************Event*****************/
    /***************************************/

    /**
     *  @brief Signale qu'il a été pris par un joueur
     *  @param idPlayer : identifiant du joueur
     */
    void sigCaughtBy(unsigned int idPlayer);

    /***************************************/
    /****************Trigger****************/
    /***************************************/

    /**
     *  @brief Signale qu'il a été déclanché
     */
    void sigTriggered();

private:
    static unsigned int NetworkEntitiesCounter;
    unsigned int m_id;

};

#endif // NETWORKENTITY_H
