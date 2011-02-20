#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

#include "branch_and_bound.h"
#include "AI_node.h"

#include "../sprites/sprites.h"
#include "../sprites/projectiles_manager.h"
#include "../game/collisions_matrix.h"
#include "../items/weapons.h" /* pour enum */


class AI {
    private:
        Branch_and_bound * m_bb;
        Rect * m_pos;
        std::list<Rect*> * m_l;

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
