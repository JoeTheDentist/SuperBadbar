
/**
 * 	@file NetworkMessageConnexion.h
 * 	@brief Header de la classe NetworkMessageConnexion
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juillet 2011
 *
 */

#ifndef NETWORKMESSAGECONNEXION_H
#define NETWORKMESSAGECONNEXION_H

#include <QString>
#include <QVariant>

/**
 *  @class NetworkMessageConnexion
 *  @brief Classe pour envoyer des messages d'erreurs
 */
class NetworkMessageConnexion
{
public:
    /**
     *  @brief Constructeur
     */
    explicit NetworkMessageConnexion() { name = ""; }

    /**
     *  @brief Constructeur
     *  @param msg : Message a transmettre
     */
    NetworkMessageConnexion(QString msg) {
        name = msg; }

    /**
     *  @brief Constructeur de copie
     *  @param msg : objet a copier
     */
    NetworkMessageConnexion(const NetworkMessageConnexion &msg) {
        name = msg.name; }

    /**
     *  @brief Destructeur
     */
    virtual ~NetworkMessageConnexion() {}

    /**
     *  @brief Abonnement du type
     *
     *  A faire une fois avant utilisation
     */
    static void init() {
        qRegisterMetaTypeStreamOperators<NetworkMessageConnexion>("NetworkMessageConnexion");
        qMetaTypeId<NetworkMessageConnexion>(); }


public:
    QString name;

protected:
    /**
     *  @brief Def de l'operateur de flux
     *
     *  Pour QVariant et envoie par reseau
     */
    friend QDataStream &operator << (QDataStream &out,
                                     const NetworkMessageConnexion &msg) {
        out << msg.name;
        return out; }

    /**
     *  @brief Def de l'operateur de flux
     *
     *  Pour QVariant et recevoir par reseau
     */
    friend QDataStream &operator >> (QDataStream &in,
                                     NetworkMessageConnexion &msg) {
        in >> msg.name;
        return in; }
};

Q_DECLARE_METATYPE(NetworkMessageConnexion);

#endif // NETWORKMESSAGECONNEXION_H
