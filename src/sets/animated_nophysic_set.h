#ifndef ANIMATED_NOPHYSIC_SET_H_INCLUDED
#define ANIMATED_NOPHYSIC_SET_H_INCLUDED

#include "animated_set.h"

class Animated_set;

/**
 *  @class Animated_physic_set
 *  @brief D�cors ne subissants pas la gravit�
 */

class Animated_nophysic_set : public Animated_set {
    private:


    public:
        /**
         *  @brief Constructeur pour une animation simple, cyclique etc...
         *  @param anim_name : nom de l'animation, � partir de /pic/animations/
         *  @param x : absisse
         *  @param y : on se demande bien ce que �a peut �tre !
         */
        Animated_nophysic_set(std::string anim_name, int x, int y);

        /**
         *  @brief Destructeur
         */
        ~Animated_nophysic_set();

        /**
         *  @brief Choisit l'image de d�part al�atoirement
         */
        void rand_pic();
};

#endif // ANIMATED_NOPHYSIC_SET_H_INCLUDED
