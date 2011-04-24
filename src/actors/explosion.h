#ifndef EXPLOSION_H_INCLUDED
#define EXPLOSION_H_INCLUDED

#define EXPLOSION_LIFE_SPAN 6

#include "projectiles.h"

class Explosion : public Projectile {
    private:

    public:
        /**
         *  @brief Constructeur
         */
        Explosion(Rect pos, direction h, unsigned int damage);

        /**
         *  @brief Destructeur
         */
        ~Explosion();

        /**
         *  @brief Mise � jour de l'�tat
         */
        void update_state();
};

#endif // EXPLOSION_H_INCLUDED
