#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

#include "../sprites/sprites.h"
#include "../sprites/projectiles_manager.h"
#include "../game/collisions_manager.h"
#include "../items/weapons.h" /* pour enum */


class AI {
    private:
        Rect * m_pos;
        Projectiles_manager * m_proj;
        Collisions_manager * m_context;
        Sprite * m_target;


        double eval(direction d);
        double dist(Rect A, Rect B);
        bool check_collision(Rect A, Rect B);

    public:
        AI(Sprite * target, Collisions_manager * context, Projectiles_manager * pm, Rect * pos);
        ~AI();

        /**
         * @brief donne la direction à suivre
         * @return direction
         */
        direction dir();
};

#endif // AI_H_INCLUDED
