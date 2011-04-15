#ifndef ANIMATED_PHYSIC_SET_H_INCLUDED
#define ANIMATED_PHYSIC_SET_H_INCLUDED

#include "animated_set.h"

/**
 *  @class Animated_physic_set
 *  @brief Décors subissants la gravité
 */

class Animated_physic_set : public Animated_set {
    private:


    public:
        /**
         *  @brief Constructeur
         *  @param anim_name, nom de l'animation : chemin à partir de /pic/
         *  @param pos : position de départ de l'animation
         *  @param speed : vitesse de départ
         */
        Animated_physic_set(std::string anim_name, Rect pos, Rect speed);

        /**
         *  @brief Destructeur
         */
        ~Animated_physic_set();

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
