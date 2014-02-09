#ifndef ANIMATED_SET_H_INCLUDED
#define ANIMATED_SET_H_INCLUDED

#include "sprites/Sprite.h"

class Sprite;

/**
 *  @class Classe
 *  @brief Classe des decors animes (plus ou moins, un gai lapin mort est moyennement anime)
 */

class AnimatedSet
{
protected:
    Rect m_pos;
    Rect m_speed;
    Sprite * m_sprite;
    bool m_to_delete;
public:
    /**
     *  @brief Constructeur
     */
    AnimatedSet();

    /**
     *  @brief Destructeur
     */
    ~AnimatedSet();

    /**
     *  @brief Mise a jour de la position
     */
    virtual void update_pos();

    /**
     *  @brief Mise a jour de la vitesse
     */
    virtual void update_speed();

    /**
     *  @brief Choisit l'image de depart aleatoirement
     */
    void rand_pic();

    /**
     *  @brief Si on doit supprimer le set
     */
    bool to_delete();
};

#endif // ANIMATED_SET_H_INCLUDED
