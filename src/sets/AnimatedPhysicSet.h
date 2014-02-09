#ifndef ANIMATED_PHYSIC_SET_H_INCLUDED
#define ANIMATED_PHYSIC_SET_H_INCLUDED

#include "AnimatedSet.h"

/**
 *  @class AnimatedPhysicSet
 *  @brief Decors subissants la gravite
 */

class AnimatedPhysicSet : public AnimatedSet
{
private:


public:
    /**
     *  @brief Constructeur
     *  @param anim_name, nom de l'animation : chemin a partir de /pic/
     *  @param pos : position de depart de l'animation
     *  @param speed : vitesse de depart
     */
    AnimatedPhysicSet (std::string anim_name, Rect pos, Rect speed);

    /**
     *  @brief Destructeur
     */
    ~AnimatedPhysicSet();

    /**
     *  @brief Mise a jour de la position
     */
    void update_pos();

    /**
     *  @brief Mise a jour de la vitesse
     */
    void update_speed();
};

#endif // ANIMATED_PHYSIC_SET_H_INCLUDED
