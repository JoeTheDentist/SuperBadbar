/**
 * 	@file NetworkMessageAskFor.h
 * 	@brief Header de la classe NetworkMessageAskFor
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juillet 2011
 *
 */

#ifndef NETWORKMESSAGEASKFOR_H
#define NETWORKMESSAGEASKFOR_H

#include <QString>
#include <QVariant>

/**
 *  @class NetworkMessageAskFor
 *  @brief Classe pour demander des variables
 */
class NetworkMessageAskFor
{
public:
    /**
     *  @brief Constructeur
     */
    NetworkMessageAskFor() { varName = ""; }

    /**
     *  @brief Constructeur
     *  @param msg : Message a transmettre
     */
    NetworkMessageAskFor(QString msg) {
        varName = msg; }

    /**
     *  @brief Constructeur de copie
     *  @param msg : objet a copier
     */
    NetworkMessageAskFor(const NetworkMessageAskFor &msg) {
        varName = msg.varName; }

    /**
     *  @brief Destructeur
     */
    virtual ~NetworkMessageAskFor() {}

    /**
     *  @brief Abonnement du type
     *
     *  A faire une fois avant utilisation
     */
    static void init() {
        qRegisterMetaTypeStreamOperators<NetworkMessageAskFor>("NetworkMessageAskFor");
        qMetaTypeId<NetworkMessageAskFor>(); }

protected:
    /**
     *  @brief Def de l'operateur de flux
     *
     *  Pour QVariant et envoie par reseau
     */
    friend QDataStream &operator << (QDataStream &out,
                                     const NetworkMessageAskFor &msg) {
        out << msg.varName;
        return out; }

    /**
     *  @brief Def de l'operateur de flux
     *
     *  Pour QVariant et recevoir par reseau
     */
    friend QDataStream &operator >> (QDataStream &in,
                                     NetworkMessageAskFor &msg) {
        in >> msg.varName;
        return in; }

public:
    QString varName;
};

Q_DECLARE_METATYPE(NetworkMessageAskFor);

#endif // NETWORKMESSAGEASKFOR_H
