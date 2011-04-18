#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

#include "../actors/projectiles_manager.h"
#include "../physic/collisions_manager.h"
#include "../physic/collisions_matrix.h"
#include "../items/weapons.h" /* pour enum */

#define ESTIM_SPEED 10
#define WEIGHT_PROJ 100
#define DIST_WEIGHT 100


class AI {
    private:
        Rect * m_pos;

        double eval(direction d);
        bool check_collision(Rect A, Rect B);
        double eval_up();
        double eval_down();
        double eval_left();
        double eval_right();

    public:
        AI(Rect * pos);
        ~AI();

        /**
         * @brief donne la direction à suivre
         * @return direction
         */
        direction dir();
};

#endif // AI_H_INCLUDED
