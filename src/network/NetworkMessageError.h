/**
 * 	@file NetworkMessageError.h
 * 	@brief Header de la classe NetworkMessageError
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juillet 2011
 *
 */

#ifndef NETWORKMESSAGEERROR_H
#define NETWORKMESSAGEERROR_H

#include <QString>
#include <QVariant>

/**
 *  @class NetworkMessageError
 *  @brief Classe pour envoyer des messages d'erreurs
 */
class NetworkMessageError
{
public:
    /**
     *  @brief Constructeur
     */
    explicit NetworkMessageError() { errorMsg = ""; }

    /**
     *  @brief Constructeur
     *  @param msg : Message a transmettre
     */
    NetworkMessageError(QString msg) {
        errorMsg = msg; }

    /**
     *  @brief Constructeur de copie
     *  @param msg : objet a copier
     */
    NetworkMessageError(const NetworkMessageError &msg) {
        errorMsg = msg.errorMsg; }

    /**
     *  @brief Destructeur
     */
    virtual ~NetworkMessageError() {}

    /**
     *  @brief Abonnement du type
     *
     *  A faire une fois avant utilisation
     */
    static void init() {
        qRegisterMetaTypeStreamOperators<NetworkMessageError>("NetworkMessageError");
        qMetaTypeId<NetworkMessageError>(); }


public:
    QString errorMsg;

protected:
    /**
     *  @brief Def de l'operateur de flux
     *
     *  Pour QVariant et envoie par reseau
     */
    friend QDataStream &operator << (QDataStream &out,
                                     const NetworkMessageError &msg) {
        out << msg.errorMsg;
        return out; }

    /**
     *  @brief Def de l'operateur de flux
     *
     *  Pour QVariant et recevoir par reseau
     */
    friend QDataStream &operator >> (QDataStream &in,
                                     NetworkMessageError &msg) {
        in >> msg.errorMsg;
        return in; }
};

Q_DECLARE_METATYPE(NetworkMessageError);

#endif // NETWORKMESSAGEERROR_H
