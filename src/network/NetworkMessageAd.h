/**
 * 	@file NetworkMessageAd.h
 * 	@brief Header de la classe NetworkMessageAd
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juillet 2011
 *
 */

#ifndef NETWORKMESSAGEAD_H
#define NETWORKMESSAGEAD_H

#include <QString>
#include <QVariant>

/**
 *  @class NetworkMessageAd
 *  @brief Classe pour envoyer des messages de pub ! Chouette !
 *
 *  Signale la presence du serveur sur le reseau local
 */
class NetworkMessageAd
{
public:
    /**
     *  @brief Constructeur
     */
    explicit NetworkMessageAd() { adMsg = ""; }

    /**
     *  @brief Constructeur
     *  @param msg : Message a transmettre
     */
    NetworkMessageAd(QString msg) {
        adMsg = msg; }

    /**
     *  @brief Constructeur de copie
     *  @param msg : objet a copier
     */
    NetworkMessageAd(const NetworkMessageAd &msg) {
        adMsg = msg.adMsg; }

    /**
     *  @brief Destructeur
     */
    virtual ~NetworkMessageAd() {}

    /**
     *  @brief Abonnement du type
     *
     *  A faire une fois avant utilisation
     */
    static void init() {
        qRegisterMetaTypeStreamOperators<NetworkMessageAd>("NetworkMessageAd");
        qMetaTypeId<NetworkMessageAd>(); }


public:
    QString adMsg;

protected:
    /**
     *  @brief Def de l'operateur de flux
     *
     *  Pour QVariant et envoie par reseau
     */
    friend QDataStream &operator << (QDataStream &out,
                                     const NetworkMessageAd &msg) {
        out << msg.adMsg;
        return out; }

    /**
     *  @brief Def de l'operateur de flux
     *
     *  Pour QVariant et recevoir par reseau
     */
    friend QDataStream &operator >> (QDataStream &in,
                                     NetworkMessageAd &msg) {
        in >> msg.adMsg;
        return in; }
};

Q_DECLARE_METATYPE(NetworkMessageAd);
QDataStream &operator << (QDataStream &out, const NetworkMessageAd &msg);
QDataStream &operator >> (QDataStream &in, NetworkMessageAd &msg);

#endif // NETWORKMESSAGEAD_H
