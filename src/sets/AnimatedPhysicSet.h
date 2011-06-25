#ifndef ANIMATED_PHYSIC_SET_H_INCLUDED
#define ANIMATED_PHYSIC_SET_H_INCLUDED

#include "AnimatedSet.h"

/**
 *  @class AnimatedPhysicSet
 *  @brief Décors subissants la gravité
 */

class AnimatedPhysicSet : public AnimatedSet {
    private:


    public:
        /**
         *  @brief Constructeur
         *  @param anim_name, nom de l'animation : chemin à partir de /pic/
         *  @param pos : position de départ de l'animation
         *  @param speed : vitesse de départ
         */
        AnimatedPhysicSet(std::string anim_name, Rect pos, Rect speed);

        /**
         *  @brief Destructeur
         */
        ~AnimatedPhysicSet();

        /**
         *  @brief Mise à jour de la position
         */
        void update_pos();

        /**
         *  @brief Mise à jour de la vitesse
         */
        void update_speed();
};

#endif // ANIMATED_PHYSIC_SET_H_INCLUDED
