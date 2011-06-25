#ifndef ANIMATED_PHYSIC_SET_H_INCLUDED
#define ANIMATED_PHYSIC_SET_H_INCLUDED

#include "AnimatedSet.h"

/**
 *  @class AnimatedPhysicSet
 *  @brief D�cors subissants la gravit�
 */

class AnimatedPhysicSet : public AnimatedSet {
    private:


    public:
        /**
         *  @brief Constructeur
         *  @param anim_name, nom de l'animation : chemin � partir de /pic/
         *  @param pos : position de d�part de l'animation
         *  @param speed : vitesse de d�part
         */
        AnimatedPhysicSet(std::string anim_name, Rect pos, Rect speed);

        /**
         *  @brief Destructeur
         */
        ~AnimatedPhysicSet();

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
