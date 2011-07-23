/**
 * 	@file NetworkTypes.h
 * 	@brief Differents types de données passant par le reseau
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juillet 2011
 *
 */

#ifndef NETWORKTYPES_H
#define NETWORKTYPES_H

#include "NetworkMessageError.h"
#include "NetworkMessageAd.h"
#include "NetworkMessageAskFor.h"
#include "NetworkMessageResponse.h"

/**
 *  @class NetworkTypes
 *  @brief Classe pour initaliser les classes "reseau"
 */
class NetworkTypes {
public:
    /**
     *  @brief Initialisation des classes qui passent par le réseau
     *
     *  Tous les types "reseau" doivent y etre
     */
    static void initNetTypes() {
        NetworkMessageError::init();
        NetworkMessageAd::init();
        NetworkMessageAskFor::init();
        NetworkMessageResponse::init();
    }
};


#endif // NETWORKTYPES_H
