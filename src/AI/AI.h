/**
 * 	@file AI.h
 * 	@brief Header de la classe AI
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date janvier 2011
 *
 */

#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

#include "../actors/ProjectilesManager.h"
#include "../physic/CollisionsManager.h"
#include "../physic/CollisionsMatrix.h"
#include "../items/Weapon.h" /* pour enum */

#define ESTIM_SPEED 10
#define WEIGHT_PROJ 100
#define DIST_WEIGHT 100

/**
 *  @class AI
 *  @brief Classe �valuant le comportement intelligent de certains monstres
 *
 *  Cette classe est li�e � un monstre (ptr sur sa position)
 *  et cherche � se rapprocher de Badbar (todo, le joueur le plus proche)
 *  tout en �vitant les projectiles (todo, les projectiles ennemis)
 */
class AI {
    private:
        Rect * m_pos;

        /**
         *  @brief Evaluation de la direction consid�r�e
         *  @param d : direction � prendre en compte
         *  @return poids (sens AI, choix) de le direction
         */
        double eval(direction d);

        /**
         *  @brief V�rifie s'il y a collision
         *  @param A : Rectange 1
         *  @param B : Rectangle 2
         *  @return s'il y a collision ou non
         */
        bool check_collision(Rect A, Rect B);

        /**
         *  @brief Evaluation en haut
         *  @return poids (sens AI, choix) de le direction
         */
        double eval_up();

        /**
         *  @brief Evaluation en bas
         *  @return poids (sens AI, choix) de le direction
         */
        double eval_down();

        /**
         *  @brief Evaluation � gauche
         *  @return poids (sens AI, choix) de le direction
         */
        double eval_left();

        /**
         *  @brief Evaluation � droite
         *  @return poids (sens AI, choix) de le direction
         */
        double eval_right();

    public:
        /**
         *  @brief Construction
         *  @param Position du monstre qui a l'IA
         */
        AI(Rect * pos);

        /**
         *  @brief Destructeur
         */
        ~AI();

        /**
         * @brief donne la direction � suivre
         * @return direction
         */
        direction dir();
};

#endif // AI_H_INCLUDED
