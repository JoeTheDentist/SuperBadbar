
#include <cmath>

#include "AI.h"
#include "../actors/Projectile.h"
#include "../actors/Babar.h"
#include "../players/PlayersManager.h"
#include "../util/Rect.h"

AI::AI(Rect * pos)
{
    m_pos = pos;
}

AI::~AI()
{

}

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
            weight += eval_left();
            break;
        case RIGHT :
            weight += eval_right();
            break;
        case UP :
            weight += eval_up();
            break;
        case DOWN :
            weight += eval_down();
            break;
		default:
			break;
    }

    return weight;
}

double AI::eval_up()
{
    if ( !CollisionsManager::is_down_coll(gCollision->get_matrix()->down_collision_type(*m_pos)) ) {
        return -1000000;
    }

    double weight = 0;
    Rect zone = *m_pos;
    zone.y -= m_pos->h;


    for (std::list<Projectile *>::iterator it = gProj->proj_begin(PLAYER1);
				it != gProj->proj_end(PLAYER1); it++) {
        if ( check_collision( (*it)->position(),zone ) ) {
            weight -= WEIGHT_PROJ;
        }
    }

    weight += DIST_WEIGHT/dist(gPlayers->local_player()->position(), zone);

    return weight;
}

double AI::eval_down()
{
    if ( CollisionsManager::is_down_coll(gCollision->get_matrix()->down_collision_type(*m_pos))
				&& !gCollision->get_matrix()->double_collision(*m_pos) ) {
        return -1000000;
    }

    double weight = 0;
    Rect zone = *m_pos;
    zone.y += m_pos->h;

    for (std::list<Projectile *>::iterator it = gProj->proj_begin(PLAYER1);
				it != gProj->proj_end(PLAYER1); it++) {
        if ( check_collision( (*it)->position(),zone ) ) {
            weight -= WEIGHT_PROJ;
        }
    }

    // 2/3 pour favoriser sauter /r descendre
    weight += DIST_WEIGHT/dist(gPlayers->local_player()->position(), zone) ;

    return weight;
}

double AI::eval_left()
{
    double weight = 0;

    Rect zone=*m_pos;
    zone.x-=m_pos->w;
    weight += DIST_WEIGHT/dist(gPlayers->local_player()->position(), zone);

    for (std::list<Projectile *>::iterator it = gProj->proj_begin(PLAYER1);
				it != gProj->proj_begin(PLAYER1); it++) {
        Rect zone = *m_pos;
		double dimx = (m_pos->h/ESTIM_SPEED)*((*it)->speed().x);
		zone.x -= dimx;
		zone.w = dimx;

        if ( check_collision( (*it)->position(),zone ) ) {
            weight -= WEIGHT_PROJ;
        }
    }
    return weight;
}

double AI::eval_right()
{
    double weight = 0;

    Rect zone=*m_pos;
    zone.x+=m_pos->w;
    weight += DIST_WEIGHT/dist(gPlayers->local_player()->position(), zone);

    for (std::list<Projectile *>::iterator it = gProj->proj_begin(PLAYER1);
				it != gProj->proj_end(PLAYER1); it++) {
        Rect zone = *m_pos;
		double dimx = (-m_pos->h/ESTIM_SPEED)*((*it)->speed().x);
		zone.x += m_pos->w;
		zone.w = dimx;


        if ( check_collision( (*it)->position(),zone ) ) {
            weight -= WEIGHT_PROJ;
        }
    }
    return weight;
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
