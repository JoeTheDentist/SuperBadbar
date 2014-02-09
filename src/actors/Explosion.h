#ifndef EXPLOSION_H_INCLUDED
#define EXPLOSION_H_INCLUDED

#define EXPLOSION_LIFE_SPAN 6

#include "Projectile.h"

class Explosion : public Projectile
{
private:

public:
    /**
     *  @brief Constructeur
     */
    Explosion (Rect pos, Direction h, unsigned int damage);

    /**
     *  @brief Destructeur
     */
    ~Explosion();

    /**
     *  @brief Mise a jour de l'etat
     */
    void update_state();
};

#endif // EXPLOSION_H_INCLUDED
