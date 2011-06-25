#ifndef ANIMATED_NOPHYSIC_SET_H_INCLUDED
#define ANIMATED_NOPHYSIC_SET_H_INCLUDED

#include "AnimatedSet.h"

/**
 *  @class AnimatedPhysicSet
 *  @brief D�cors ne subissants pas la gravit�
 */

class AnimatedNophysicSet : public AnimatedSet {
    private:


    public:
        /**
         *  @brief Constructeur pour une animation simple, cyclique etc...
         *  @param anim_name : nom de l'animation, � partir de /pic/animations/
         *  @param x : absisse
         *  @param y : on se demande bien ce que �a peut �tre !
         */
        AnimatedNophysicSet(std::string anim_name, int x, int y, bool ended=false, bool to_delete=false);

        /**
         *  @brief Destructeur
         */
        ~AnimatedNophysicSet();

        /**
         *  @brief Choisit l'image de d�part al�atoirement
         */
        void rand_pic();
};

#endif // ANIMATED_NOPHYSIC_SET_H_INCLUDED
