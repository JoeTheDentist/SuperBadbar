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
 *  @brief Classe permettant de signaler des �v�nements sur le r�seau
 *
 *  Doit �tre contenue dans tous les objets ayant des informations
 *  que le r�seau doit connaitre
 */
class NetworkEntity
{
public:

    /**
     *  @brief Constructeur
     *  @param type : Type d'entit�
     */
    NetworkEntity(NetworkType type);

    /**
     *  @brief Destructeur
     */
    virtual ~NetworkEntity();

    /**
     *  @brief Remet le compteur des entit�s � z�ro
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
     *  @brief Signale la position, l'�tat et la direction
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
     *  @brief Signale qu'il a �t� pris par un joueur
     *  @param idPlayer : identifiant du joueur
     */
    void sigCaughtBy(unsigned int idPlayer);

    /***************************************/
    /****************Trigger****************/
    /***************************************/

    /**
     *  @brief Signale qu'il a �t� d�clanch�
     */
    void sigTriggered();

private:
    static unsigned int NetworkEntitiesCounter;
    unsigned int m_id;

};

#endif // NETWORKENTITY_H
