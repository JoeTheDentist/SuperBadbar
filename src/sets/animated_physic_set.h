#ifndef ANIMATED_PHYSIC_SET_H_INCLUDED
#define ANIMATED_PHYSIC_SET_H_INCLUDED

#include "animated_set.h"

/**
 *  @class Animated_physic_set
 *  @brief D�cors subissants la gravit�
 */

class Animated_physic_set : public Animated_set {
    private:


    public:
        /**
         *  @brief Constructeur
         *  @param anim_name, nom de l'animation : chemin � partir de /pic/
         *  @param pos : position de d�part de l'animation
         *  @param speed : vitesse de d�part
         */
        Animated_physic_set(std::string anim_name, Rect pos, Rect speed);

        /**
         *  @brief Destructeur
         */
        ~Animated_physic_set();

        /**
         *  @brief Mise � jour de la position
         */
        void update_pos();

        /**
         *  @brief Mise � jour de la vitesse
         */
        void update_speed();
};

#endif // ANIMATED_PHYSIC_SET_H_INCLUDED
