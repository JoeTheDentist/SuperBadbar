
#include "AI.h"
#include "depth_active_nodes.h"
#include "../sprites/projectiles.h"

AI::AI(Sprite * target, Collisions_manager * context, Projectiles_manager * pm, Rect * pos)
{
    /* cr�ation du probl�me, et de la strat�gie de r�solution */
    m_l = new std::list<Rect*>;

    for (std::list<Projectile *>::iterator it = pm->proj_friend_begin();
				it != pm->proj_friend_end(); it++) {
        m_l->push_front(&((*it)->position()));
    }

    m_bb = new Branch_and_bound(new AI_node(target, context, m_l, 0, 4, pos, NULL),
                                new Depth_active_nodes());
    m_pos = pos;
}

AI::~AI()
{
    delete m_bb;
    delete m_l;
}

direction AI::dir()
{
    AI_node * sol = (AI_node*)m_bb->solve();

    /* r�cup�ration du premier �l�ment de la meilleure solution */
    while ( sol->daddy()->daddy() != NULL ) {
        sol = sol->daddy();
    }

    /* on regarde de quelle c�t� elle �tait */
    if ( m_pos->x < sol->dim().x ) {
        /*  */
        return LEFT;
    } else if ( m_pos->x > sol->dim().x ) {
        return RIGHT;
    } else if ( m_pos->y < sol->dim().y ) {
        return UP;
    } else {
        return DOWN;
    }
}
