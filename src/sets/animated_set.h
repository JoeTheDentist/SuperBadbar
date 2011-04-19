#ifndef ANIMATED_SET_H_INCLUDED
#define ANIMATED_SET_H_INCLUDED

#include "../sprites/sprites.h"

class Sprite;

/**
 *  @class Classe
 *  @brief Classe des d�cors anim�s (plus ou moins, un gai lapin mort est moyennement anim�)
 */

class Animated_set {
    protected:
        Rect m_pos;
        Rect m_speed;
        Sprite * m_sprite;
        bool m_to_delete;
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
         *  @brief Mise � jour de la position
         */
        virtual void update_pos();

        /**
         *  @brief Mise � jour de la vitesse
         */
        virtual void update_speed();

        /**
         *  @brief Choisit l'image de d�part al�atoirement
         */
        void rand_pic();

        /**
         *  @brief Si on doit supprimer le set
         */
        bool to_delete();
};

#endif // ANIMATED_SET_H_INCLUDED
