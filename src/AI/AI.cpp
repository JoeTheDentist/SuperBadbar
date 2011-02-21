
#include <cmath>

#include "AI.h"
#include "../sprites/projectiles.h"

AI::AI(Sprite * target, Collisions_manager * context, Projectiles_manager * pm, Rect * pos)
{
    m_target = target;
    m_context = context;
    m_proj = pm;
    m_pos = pos;
}

AI::~AI()
{

}

/* algo naif mais bien plus efficace */
direction AI::dir()
{
    direction best_dir = LEFT;
    double max = eval(best_dir);
    for (int i = 1; i < 4; i++) {
        double cur = eval((direction)i);
        if ( cur > max ) {
            best_dir = (direction)i;
            max = cur;
        }
    }
    return best_dir;
}

double AI::eval(direction d) {
    Rect zone = *m_pos;
    // ici faire en fonction de la vitesse des projectiles TODO

    double weight = 0;
    switch ( d ) {
        case LEFT :
            zone.x -= m_pos->w;
            break;
        case RIGHT :
            zone.x += m_pos->w;
            break;
        case UP :
            // moche TODO + verif que la zone est bien dans la map
            if ( !Collisions_manager::is_down_coll(m_context->down_collision_type(*m_pos)) ) {
                return -1000000;
            }
            zone.y -= m_pos->h;
            break;
        case DOWN :
            // idem TODO
            if ( m_context->double_collision(*m_pos) ) {
                return -1000000;
            }
            zone.y += m_pos->h;
            break;
    }

    weight += 1000/dist(m_target->position(), zone);

    for (std::list<Projectile *>::iterator it = m_proj->proj_friend_begin();
				it != m_proj->proj_friend_end(); it++) {
        if ( check_collision( (*it)->position(),zone ) ) {
            weight -= 100;
        }
    }
    return weight;
}

double AI::dist(Rect A, Rect B)
{
    return sqrt( (A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y) );
}

bool AI::check_collision(Rect A, Rect B)
{
	uint16_t A_right = A.x + A.w;
	uint16_t B_right = B.x + B.w;
	uint16_t A_bottom = A.y + A.h;
	uint16_t B_bottom = B.y + B.h;
	bool A_in_B = ((B.x < A.x && A.x < B_right) || (B.x < A_right && A_right < B_right )) && ((B.y < A.y && A.y < B_bottom) || (B.y < A_bottom && A_bottom < B_bottom ));
	bool B_in_A = ((A.x < B.x && B.x < A_right) || (A.x < B_right && B_right < A_right )) && ((A.y < B.y && B.y < A_bottom) || (A.y < B_bottom && B_bottom < A_bottom ));
	return A_in_B || B_in_A;
}
