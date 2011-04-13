#ifndef ANIMATED_SET_H_INCLUDED
#define ANIMATED_SET_H_INCLUDED

#include "../sprites/sprites.h"

class Sprite;

/**
 *  @class Classe
 *  @brief Classe des décors animés (plus ou moins, un gai lapin mort est moyennement animé)
 */

class Animated_set {
    protected:
        Rect m_pos;
        Rect m_speed;
        Sprite * m_sprite;
    public:
        /**
         *  @brief Constructeur
         */
        Animated_set();

        /**
         *  @brief Destructeur
         */
        ~Animated_set();

        /**
         *  @brief Mise à jour de la position
         */
        void update_pos();

        /**
         *  @brief Mise à jour de la vitesse
         */
        virtual void update_speed();
};

#endif // ANIMATED_SET_H_INCLUDED
