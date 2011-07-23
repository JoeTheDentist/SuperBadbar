/**
 * 	@file NetworkMessageResponse.h
 * 	@brief Header de la classe NetworkMessageResponse
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juillet 2011
 *
 */

#ifndef NETWORKMESSAGERESPONSE_H
#define NETWORKMESSAGERESPONSE_H

#include <QVariant>

/**
 *  @class NetworkMessageResponse
 *  @brief Classe pour envoyer des messages a la suite d'une demande
 */
class NetworkMessageResponse
{
public:
    /**
     *  @brief Constructeur
     */
    explicit NetworkMessageResponse() {}

    /**
     *  @brief Constructeur
     *  @param msg : Message a transmettre
     */
    NetworkMessageResponse(QString var) {
        respVar = var; }

    /**
     *  @brief Constructeur de copie
     *  @param msg : objet a copier
     */
    NetworkMessageResponse(const NetworkMessageResponse &msg) {
        respVar = msg.respVar; }

    /**
     *  @brief Destructeur
     */
    virtual ~NetworkMessageResponse() {}

    /**
     *  @brief Abonnement du type
     *
     *  A faire une fois avant utilisation
     */
    static void init() {
        qRegisterMetaTypeStreamOperators<NetworkMessageResponse>("NetworkMessageResponse");
        qMetaTypeId<NetworkMessageResponse>(); }


public:
    QVariant respVar;

protected:
    /**
     *  @brief Def de l'operateur de flux
     *
     *  Pour QVariant et envoie par reseau
     */
    friend QDataStream &operator << (QDataStream &out,
                                     const NetworkMessageResponse &msg) {
        out << msg.respVar;
        return out; }

    /**
     *  @brief Def de l'operateur de flux
     *
     *  Pour QVariant et recevoir par reseau
     */
    friend QDataStream &operator >> (QDataStream &in,
                                     NetworkMessageResponse &msg) {
        in >> msg.respVar;
        return in; }
};

Q_DECLARE_METATYPE(NetworkMessageResponse);

#endif // NETWORKMESSAGERESPONSE_H
