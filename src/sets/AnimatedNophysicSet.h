#ifndef ANIMATED_NOPHYSIC_SET_H_INCLUDED
#define ANIMATED_NOPHYSIC_SET_H_INCLUDED

#include "AnimatedSet.h"

/**
 *  @class AnimatedPhysicSet
 *  @brief Décors ne subissants pas la gravité
 */

class AnimatedNophysicSet : public AnimatedSet {
    private:


    public:
        /**
         *  @brief Constructeur pour une animation simple, cyclique etc...
         *  @param anim_name : nom de l'animation, à partir de /pic/animations/
         *  @param x : absisse
         *  @param y : on se demande bien ce que ça peut être !
         */
        AnimatedNophysicSet(std::string anim_name, int x, int y, bool ended=false, bool to_delete=false);

        /**
         *  @brief Destructeur
         */
        ~AnimatedNophysicSet();

        /**
         *  @brief Choisit l'image de départ aléatoirement
         */
        void rand_pic();
};

#endif // ANIMATED_NOPHYSIC_SET_H_INCLUDED
