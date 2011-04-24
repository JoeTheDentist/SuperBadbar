#ifndef EXPLOSION_H_INCLUDED
#define EXPLOSION_H_INCLUDED

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
};

#endif // EXPLOSION_H_INCLUDED
